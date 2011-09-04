/*
 * gep_scope_main_window.cpp - Main window of the GenePool scope library
 *
 * Frank Cieslok, Aug. 2011
 */

#include "GEPScopeMainWindow.h"
#include "GEPScopeSequentialDiagram.h"
#include "GEPScopeTools.h"

#include <iostream>

#include <QDebug>

#include <QtCore/QTime>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>

#include "ui_gep_scope_main_window.h"

namespace GEP {
namespace Scope {

//#**************************************************************************
// CLASS GEP::Scope::MainWindowContent
//#**************************************************************************

class MainWindowContent : public QWidget, public Ui::GEPScopeMainWindowUi
{
public:
  MainWindowContent (QWidget* parent);
  virtual ~MainWindowContent ();
};

/* Constructor */
MainWindowContent::MainWindowContent (QWidget* parent)
  : QWidget (parent)
{
  setupUi (this);
}

/* Destructor */
MainWindowContent::~MainWindowContent ()
{
}


//#**************************************************************************
// CLASS GEP::Scope::MainWindow
//#**************************************************************************

/* Constructor */
MainWindow::MainWindow (System::Controller* controller)
: QMainWindow (),
  _controller  (controller),
  _content     (0),
  _run_action  (0),
  _quit_action (0)
{
  QMenu* file_menu = menuBar ()->addMenu ("&File");

  _quit_action = new QAction ("&Quit", file_menu);
  connect (_quit_action, SIGNAL (triggered ()), SLOT (slotQuit ()));
  file_menu->addAction (_quit_action);

  QMenu* execute_menu = menuBar ()->addMenu ("&Execute");

  _run_action = new QAction ("&Run", execute_menu);
  connect (_run_action, SIGNAL (triggered ()), SLOT (slotRun ()));
  execute_menu->addAction (_run_action);

  _content = new MainWindowContent (this);
  setCentralWidget (_content);

  _fitness_diagram = Tools::addWidgetToParent (new SequentialDiagram (_content->_diagram_frame));
}

/* Destructor */
MainWindow::~MainWindow ()
{
}

/*
 * Slot: Algorithm execution
 */
void MainWindow::slotRun ()
{
  _fitness_diagram->clear ();
  _controller->initialize ();

  QTime time = QTime::currentTime ();
  statusBar ()->showMessage ("Starting...");

  for (uint i=0; !_controller->executeStep  (); ++i)
    {
      _fitness_diagram->addPoint (0, QPointF (i, _controller->getCurrentFitness (GEP::System::Controller::FitnessType::MINIMUM)));
      _fitness_diagram->addPoint (1, QPointF (i, _controller->getCurrentFitness (GEP::System::Controller::FitnessType::MINIMUM)));
      _fitness_diagram->addPoint (2, QPointF (i, _controller->getCurrentFitness (GEP::System::Controller::FitnessType::MINIMUM)));

      if (time.elapsed () >= 100)
        {
          statusBar ()->showMessage (QString ("Executing step %1").arg (_controller->getCurrentStep ()));

          _content->_step->setText (QString::number (_controller->getCurrentStep ()));
          _content->_minimum_fitness->setText (QString::number (_controller->getCurrentFitness (GEP::System::Controller::FitnessType::MINIMUM), 'f', 2));
          _content->_average_fitness->setText (QString::number (_controller->getCurrentFitness (GEP::System::Controller::FitnessType::AVERAGE), 'f', 2));
          _content->_maximum_fitness->setText (QString::number (_controller->getCurrentFitness (GEP::System::Controller::FitnessType::MAXIMUM), 'f', 2));

          _fitness_diagram->repaint ();

          QApplication::processEvents ();
          time.restart ();
        }
    }

  statusBar ()->clearMessage ();
}

/*
 * Slot: Application termination
 */
void MainWindow::slotQuit ()
{
  close ();
}

}
}
