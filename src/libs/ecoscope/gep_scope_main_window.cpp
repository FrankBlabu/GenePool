/*
 * gep_scope_main_window.cpp - Main window of the GenePool scope library
 *
 * Frank Cieslok, Aug. 2011
 */

#include "GEPScopeMainWindow.h"
#include "GEPScopeTools.h"

#include <QtGui/QMenu>
#include <QtGui/QMenuBar>

#include "ui_gep_scope_main_window.h"

namespace GEP {
namespace Scope {

//#**************************************************************************
// CLASS GEP::Scope::MainWindowContent
//#**************************************************************************

class MainWindowContent : public QWidget, private Ui::GEPScopeMainWindowUi
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
MainWindow::MainWindow ()
: QMainWindow (),
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

  _content = Tools::addWidgetToParent (new MainWindowContent (centralWidget ()));
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
