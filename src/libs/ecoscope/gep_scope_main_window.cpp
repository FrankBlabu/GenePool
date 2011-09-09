/*
 * gep_scope_main_window.cpp - Main window of the GenePool scope library
 *
 * Frank Cieslok, Aug. 2011
 */

#include "GEPScopeMainWindow.h"
#include "GEPScopeSequentialDiagram.h"
#include "GEPScopeSelectionDisplay.h"
#include "GEPScopeWorldDisplay.h"
#include "GEPScopeTools.h"

#include <iostream>

#include <QDebug>

#include <QtCore/QTime>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBar>
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
  _controller      (controller),
  _running         (false),
  _content         (0),
  _world_display   (0),
  _fitness_diagram (0),
  _run_action      (0),
  _quit_action     (0)
{
  //
  // Menu setup
  //
  QMenu* file_menu = menuBar ()->addMenu ("&File");

  _quit_action = new QAction ("&Quit", file_menu);
  connect (_quit_action, SIGNAL (triggered ()), SLOT (slotQuit ()));
  file_menu->addAction (_quit_action);

  QMenu* execute_menu = menuBar ()->addMenu ("&Execute");

  _run_action = new QAction ("&Run", execute_menu);
  connect (_run_action, SIGNAL (triggered ()), SLOT (slotRun ()));
  execute_menu->addAction (_run_action);

  _step_action = new QAction ("&Step", execute_menu);
  connect (_step_action, SIGNAL (triggered ()), SLOT (slotStep ()));
  execute_menu->addAction (_step_action);

  //
  // Toolbar setup
  //
  QToolBar* execute_toolbar = addToolBar ("execute");
  execute_toolbar->addAction (_run_action);
  execute_toolbar->addAction (_step_action);

  //
  // Widget setup
  //
  _content = new MainWindowContent (this);
  setCentralWidget (_content);

  _fitness_diagram = Tools::addWidgetToParent (new SequentialDiagram (_content->_diagram_frame));

  _content->_display_content->addItem ("Best", WorldDisplay::DisplayMode::BEST);
  _content->_display_content->addItem ("Worst", WorldDisplay::DisplayMode::WORST);
  _content->_display_content->addItem ("All", WorldDisplay::DisplayMode::ALL);

  QTabWidget* tab_widget = Tools::addWidgetToParent (new QTabWidget (_content->_population_frame));
  tab_widget->addTab (new SelectionDisplay (controller, tab_widget), "Selection");

  //
  // Signal/slot setup
  //
  connect (_content->_display_content, SIGNAL (activated (int)), SLOT (slotUpdateOutput ()));

  slotUpdateOutput ();
}

/* Destructor */
MainWindow::~MainWindow ()
{
}

/*
 * Add widget for displaying the worlds content
 */
void MainWindow::setWorldDisplay (WorldDisplay* world_display)
{
  Q_ASSERT (_world_display == 0);

  world_display->setParent (_content->_world_display_frame);
  _world_display = Tools::addWidgetToParent (world_display);
}

/*
 * Slot: Algorithm execution
 */
void MainWindow::slotRun ()
{
  if (!_running)
    startup ();

  QTime time = QTime::currentTime ();

  while (!executeStep ())
    {
      if (time.elapsed () >= 100)
        {
          slotUpdateOutput ();
          QApplication::processEvents ();
          time.restart ();
        }
    }

  cleanup ();
}

/*
 * Slot: Execute single step
 */
void MainWindow::slotStep ()
{
  if (!_running)
    startup ();

  if (executeStep ())
    cleanup ();

  slotUpdateOutput ();
}

/*
 * Startup new algorithm execution
 */
void MainWindow::startup ()
{
  Q_ASSERT (!_running);

  _fitness_diagram->clear ();
  _controller->initialize ();
  _running = true;

  statusBar ()->showMessage ("Starting...");
  slotUpdateOutput ();
}

/*
 * Cleanup after algorithm execution
 */
void MainWindow::cleanup ()
{
  _running = false;

  statusBar ()->clearMessage ();
  slotUpdateOutput ();
}

/*
 * Execute single algorithm step
 *
 * \return 'true' when this was the last step
 */
bool MainWindow::executeStep ()
{
  int step = _controller->getCurrentStep ();

  bool done = _controller->executeStep  ();

  _fitness_diagram->addPoint (0, QPointF (step, _controller->getCurrentFitness (GEP::System::Controller::FitnessType::MINIMUM)));
  _fitness_diagram->addPoint (1, QPointF (step, _controller->getCurrentFitness (GEP::System::Controller::FitnessType::AVERAGE)));
  _fitness_diagram->addPoint (2, QPointF (step, _controller->getCurrentFitness (GEP::System::Controller::FitnessType::MAXIMUM)));

  return done;
}

/*
 * Slot: Application termination
 */
void MainWindow::slotQuit ()
{
  close ();
}

/*
 * Update output
 */
void MainWindow::slotUpdateOutput ()
{
  _content->_step->setText (QString::number (_controller->getCurrentStep ()));
  _content->_minimum_fitness->setText (QString::number (_controller->getCurrentFitness (GEP::System::Controller::FitnessType::MINIMUM), 'f', 2));
  _content->_average_fitness->setText (QString::number (_controller->getCurrentFitness (GEP::System::Controller::FitnessType::AVERAGE), 'f', 2));
  _content->_maximum_fitness->setText (QString::number (_controller->getCurrentFitness (GEP::System::Controller::FitnessType::MAXIMUM), 'f', 2));

  _fitness_diagram->repaint ();
  statusBar ()->showMessage ("Executing step " + QString::number (_controller->getCurrentStep ()));

  if (_world_display != 0)
    _world_display->updateDisplay (_controller, static_cast<WorldDisplay::DisplayMode_t> (_content->_display_content->itemData (_content->_display_content->currentIndex ()).toInt ()));
}

}
}
