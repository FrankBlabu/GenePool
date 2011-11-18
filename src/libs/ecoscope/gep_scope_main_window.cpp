/* * gep_scope_main_window.cpp - Main window of the GenePool scope library
 *
 * Frank Cieslok, Aug. 2011
 */

#define GEP_DEBUG

#include "GEPScopeMainWindow.h"
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
  _action_initialize  (new QAction (tr ("&Initialize"), this)),
  _action_run         (new QAction (tr ("&Run"), this)),
  _action_single_step (new QAction (tr ("&Step"), this)),
  _action_reset       (new QAction (tr ("Reset"), this)),
  _action_quit        (new QAction (tr ("&Quit"), this)),
  _state_machine      (),
  _state_initialized  (),
  _state_running      (),
  _state_step         (),
  _state_finished     (),
  _initial_fitness    (0.0)
{
  System::Notifier* notifier = System::Notifier::getNotifier ();

  //
  // Menu setup
  //
  QMenu* file_menu = menuBar ()->addMenu (tr ("&File"));
  file_menu->addAction (_action_quit);

  QMenu* execute_menu = menuBar ()->addMenu (tr ("&Execute"));
  execute_menu->addAction (_action_initialize);
  execute_menu->addAction (_action_run);
  execute_menu->addAction (_action_single_step);
  execute_menu->addAction (_action_reset);

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

  _content->_display_content->addItem (tr ("Best"), WorldDisplay::DisplayMode::BEST);
  _content->_display_content->addItem (tr ("Worst"), WorldDisplay::DisplayMode::WORST);
  _content->_display_content->addItem (tr ("All"), WorldDisplay::DisplayMode::ALL);

  _operator_display_tab = Tools::addWidgetToParent (new QTabWidget (_content->_population_frame));
  _operator_display_tab->addTab (new SelectionOperatorDisplay (controller, _operator_display_tab), tr ("Selection"));
  _operator_display_tab->addTab (new CrossoverOperatorDisplay (controller, _operator_display_tab), tr ("Crossover"));
  _operator_display_tab->addTab (new MutationOperatorDisplay (controller, _operator_display_tab), tr ("Mutation"));

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
  connect (_action_initialize, SIGNAL (triggered ()), SLOT (slotInitialize ()));
  connect (_action_reset, SIGNAL (triggered ()), SLOT (slotReset ()));
  connect (_action_quit, SIGNAL (triggered ()), SLOT (slotQuit ()));

  connect (_content->_display_content, SIGNAL (activated (int)), SLOT (slotUpdateOutput ()));
  connect (_operator_display_tab, SIGNAL (currentChanged (int)), SLOT (slotActiveOperatorDisplayChanged ()));
  connect (notifier, SIGNAL (signalControllerStepEnd (GEP::System::ControllerStepNotification)),
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

  statusBar ()->showMessage (tr ("Ready"));
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
  progress_dialog.setLabelText (tr ("Computing..."));
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
      statusBar ()->showMessage (tr ("Executing step %1").arg (_controller->getCurrentStep ()));
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

  statusBar ()->showMessage (tr ("Finished"));
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
 * Slot: Reset world
 */
void MainWindow::slotReset ()
{
  System::Notifier::getNotifier ()->notifyReset ();

  _initial_fitness = 0.0;

  _content->_step->clear ();
  _content->_initial_fitness->clear ();
  _content->_average_fitness->clear ();
  _content->_fitness_gain->clear ();

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

  if (notification.getStep () == 0)
    {
      _initial_fitness = notification.getAverageFitness ();
      _content->_initial_fitness->setText (QString::number (_initial_fitness, 'f', 8));
    }

  _content->_step->setText (QString::number (notification.getStep ()));

  double fitness = notification.getAverageFitness ();
  _content->_average_fitness->setText (QString::number (fitness, 'f', 8));
  _content->_fitness_gain->setText (QString::number (qRound ((fitness / _initial_fitness) * 100.0 - 100.0)) + QString (" %"));
}

/*
 * Update output
 */
void MainWindow::slotUpdateOutput ()
{
  _fitness_diagram->repaint ();

  if (_world_display != 0)
    _world_display->updateDisplay (_controller, static_cast<WorldDisplay::DisplayMode_t> (_content->_display_content->itemData (_content->_display_content->currentIndex ()).toInt ()));
}

}
}
