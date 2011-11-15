/*
 * gep_scope_main_window.cpp - Main window of the GenePool scope library
 *
 * Frank Cieslok, Aug. 2011
 */

#define GEP_DEBUG

#include "GEPScopeMainWindow.h"
#include "GEPScopeFitnessStatisticsDialog.h"
#include "GEPScopeSequentialDiagram.h"
#include "GEPScopeCrossoverOperatorDisplay.h"
#include "GEPScopeMutationOperatorDisplay.h"
#include "GEPScopeSelectionOperatorDisplay.h"
#include "GEPScopeWorldDisplay.h"
#include "GEPScopeTools.h"

#include <GEPSystemController.h>
#include <GEPSystemControllerThread.h>
#include <GEPSystemNotifier.h>
#include <GEPSystemWorld.h>

#include <GEPSystemDebug.h>

#include <iostream>

#include <QtCore/QTime>
#include <QtGui/QKeyEvent>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QProgressDialog>
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
  _controller         (controller),
  _content            (0),
  _world_display      (0),
  _fitness_diagram    (0),
  _action_initialize  (0),
  _action_run         (0),
  _action_single_step (0),
  _action_reset       (0),
  _action_quit        (0),
  _state_machine      (),
  _state_initialized  (),
  _state_running      (),
  _state_step         (),
  _state_finished     ()
{
  System::Notifier* notifier = System::Notifier::getNotifier ();

  //
  // Menu setup
  //
  QMenu* file_menu = menuBar ()->addMenu ("&File");

  _action_quit = new QAction ("&Quit", file_menu);
  connect (_action_quit, SIGNAL (triggered ()), SLOT (slotQuit ()));
  file_menu->addAction (_action_quit);

  QMenu* execute_menu = menuBar ()->addMenu ("&Execute");

  _action_initialize = new QAction ("&Initialize", execute_menu);
  execute_menu->addAction (_action_initialize);

  _action_run = new QAction ("&Run", execute_menu);
  execute_menu->addAction (_action_run);

  _action_single_step = new QAction ("&Step", execute_menu);
  execute_menu->addAction (_action_single_step);

  _action_reset = new QAction ("Reset", execute_menu);
  execute_menu->addAction (_action_reset);

  QMenu* tools_menu = menuBar ()->addMenu ("&Tools");

  _action_fitness_statistics = new QAction ("&Fitness statistics", tools_menu);
  connect (_action_fitness_statistics, SIGNAL (triggered ()), SLOT (slotFitnessStatistics ()));
  tools_menu->addAction (_action_fitness_statistics);

  //
  // Toolbar setup
  //
  QToolBar* execute_toolbar = addToolBar ("execute");
  execute_toolbar->addAction (_action_initialize);
  execute_toolbar->addAction (_action_run);
  execute_toolbar->addAction (_action_single_step);
  execute_toolbar->addAction (_action_reset);

  //
  // Widget setup
  //
  _content = new MainWindowContent (this);
  setCentralWidget (_content);

  _fitness_diagram = Tools::addWidgetToParent (new SequentialDiagram (_content->_diagram_frame));

  //_content->_display_content->addItem ("Selected", WorldDisplay::DisplayMode::SELECTED);
  _content->_display_content->addItem ("Best", WorldDisplay::DisplayMode::BEST);
  _content->_display_content->addItem ("Worst", WorldDisplay::DisplayMode::WORST);
  _content->_display_content->addItem ("All", WorldDisplay::DisplayMode::ALL);

  _operator_display_tab = Tools::addWidgetToParent (new QTabWidget (_content->_population_frame));
  _operator_display_tab->addTab (new SelectionOperatorDisplay (controller, _operator_display_tab), "Selection");
  _operator_display_tab->addTab (new CrossoverOperatorDisplay (controller, _operator_display_tab), "Crossover");
  _operator_display_tab->addTab (new MutationOperatorDisplay (controller, _operator_display_tab), "Mutation");

  //
  // State machine setup
  //
  _state_machine.addState (&_state_initialized);
  _state_machine.addState (&_state_running);
  _state_machine.addState (&_state_step);
  _state_machine.addState (&_state_finished);

  _state_initialized.addTransition (_action_run, SIGNAL (triggered ()), &_state_running);
  _state_initialized.addTransition (_action_single_step, SIGNAL (triggered ()), &_state_step);
  _state_initialized.addTransition (_action_reset, SIGNAL (triggered ()), &_state_initialized);

  _state_running.addTransition (this, SIGNAL (signalFinished ()), &_state_finished);

  _state_step.addTransition (_action_single_step, SIGNAL (triggered ()), &_state_step);
  _state_step.addTransition (_action_run, SIGNAL (triggered ()), &_state_running);
  _state_step.addTransition (_action_reset, SIGNAL (triggered ()), &_state_initialized);
  _state_step.addTransition (this, SIGNAL (signalFinished ()), &_state_finished);

  _state_finished.addTransition (_action_reset, SIGNAL (triggered ()), &_state_initialized);

  _state_machine.setInitialState (&_state_initialized);

  connect (&_state_initialized, SIGNAL (entered ()), SLOT (slotStateInitialized ()));
  connect (&_state_running, SIGNAL (entered ()), SLOT (slotStateRunning ()));
  connect (&_state_step, SIGNAL (entered ()), SLOT (slotStateStep ()));
  connect (&_state_finished, SIGNAL (entered ()), SLOT (slotStateFinished ()));

  //
  // Signal/slot setup
  //
  connect (_content->_display_content, SIGNAL (activated (int)), SLOT (slotUpdateOutput ()));
  connect (_operator_display_tab, SIGNAL (currentChanged (int)), SLOT (slotActiveOperatorDisplayChanged ()));
  connect (_action_initialize, SIGNAL (triggered ()), SLOT (slotInitialize ()));
  connect (notifier, SIGNAL (signalControllerStep (GEP::System::ControllerStepNotification)),
           SLOT (slotControllerStep (const GEP::System::ControllerStepNotification&)));

  slotUpdateOutput ();
  slotActiveOperatorDisplayChanged ();

  _state_machine.start ();
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

  connect (_world_display, SIGNAL (signalUpdate ()), SLOT (slotUpdateOutput ()));
}

/*
 * Handler for keyboard events
 */
void MainWindow::keyPressEvent (QKeyEvent* event)
{
  if ( event->modifiers () == Qt::NoModifier &&
       event->key () == Qt::Key_Escape )
    emit signalAbort ();
}

/*
 * Close main window
 */
void MainWindow::closeEvent (QCloseEvent* event)
{
  emit signalAbort ();
  emit signalFinished ();
  QMainWindow::closeEvent (event);
}

/*
 * Slot: Initialized state entered
 */
void MainWindow::slotStateInitialized ()
{
  _action_initialize->setEnabled (true);
  _action_run->setEnabled (true);
  _action_single_step->setEnabled (true);
  _action_reset->setEnabled (true);

  _fitness_diagram->clear ();
  _controller->initialize ();

  statusBar ()->showMessage ("Ready");
  slotUpdateOutput ();
}

/*
 * Slot: Running state entered
 */
void MainWindow::slotStateRunning ()
{
  _action_initialize->setEnabled (false);
  _action_run->setEnabled (false);
  _action_single_step->setEnabled (false);
  _action_reset->setEnabled (false);

  QProgressDialog progress_dialog (this);
  progress_dialog.setLabelText ("Computing...");
  progress_dialog.setRange (0, _controller->getNumberOfSteps ());

  System::ControllerThread thread (_controller);

  QObject::connect (&thread, SIGNAL (signalDone ()), &progress_dialog, SLOT (cancel ()));
  QObject::connect (&thread, SIGNAL (signalStep (int)), &progress_dialog, SLOT (setValue (int)));
  QObject::connect (&progress_dialog, SIGNAL (canceled ()), &thread, SLOT (slotAbort ()));
  QObject::connect (this, SIGNAL (signalAbort ()), &thread, SLOT (slotAbort ()));

  thread.start ();
  progress_dialog.exec ();
  thread.wait ();

  slotUpdateOutput ();
  emit signalFinished ();
}

/*
 * Slot: Step state entered
 */
void MainWindow::slotStateStep ()
{
  _action_initialize->setEnabled (false);
  _action_run->setEnabled (true);
  _action_single_step->setEnabled (true);
  _action_reset->setEnabled (true);

  if (!_controller->executeNextStep ())
    {
      statusBar ()->showMessage ("Executing step " + QString::number (_controller->getCurrentStep ()));
      slotUpdateOutput ();
    }
  else
    emit signalFinished ();
}

/*
 * Slot: Finished state entered
 */
void MainWindow::slotStateFinished ()
{
  _action_initialize->setEnabled (false);
  _action_run->setEnabled (false);
  _action_single_step->setEnabled (false);
  _action_reset->setEnabled (true);

  statusBar ()->showMessage ("Finished");
  slotUpdateOutput ();
}

/*
 * Slot (Re)initialize world
 */
void MainWindow::slotInitialize ()
{
  _controller->getWorld ()->generateWorld ();
  _controller->initialize ();

  slotUpdateOutput ();
}

/*
 * Slot: Application termination
 */
void MainWindow::slotQuit ()
{
  emit signalFinished ();
  close ();
}

/*
 * Slot: Display fitness statistics
 */
void MainWindow::slotFitnessStatistics ()
{
  FitnessStatisticsDialog dialog (_controller, this);
  dialog.exec ();
}

/*
 * Update output
 */
void MainWindow::slotUpdateOutput ()
{
  _content->_step->setText (QString::number (_controller->getCurrentStep ()));
  _content->_average_fitness->setText (QString::number (_controller->getCurrentAverageFitness (), 'f', 8));

  _fitness_diagram->repaint ();

  if (_world_display != 0)
    _world_display->updateDisplay (_controller, static_cast<WorldDisplay::DisplayMode_t> (_content->_display_content->itemData (_content->_display_content->currentIndex ()).toInt ()));
}

/*
 * Called if the active operator display changed
 */
void MainWindow::slotActiveOperatorDisplayChanged ()
{
  for (int i=0; i < _operator_display_tab->count (); ++i)
    {
      OperatorDisplay* display = dynamic_cast<OperatorDisplay*> (_operator_display_tab->widget (i));
      Q_ASSERT (display != 0);
      display->setActive (i == _operator_display_tab->currentIndex ());
    }
}

/*
 * Update after each controller step
 */
void MainWindow::slotControllerStep (const GEP::System::ControllerStepNotification& notification)
{
  _fitness_diagram->addPoint (0, QPointF (notification.getStep (), notification.getAverageFitness ()));
}

}
}
