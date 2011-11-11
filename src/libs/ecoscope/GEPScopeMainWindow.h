/*
 * GEPScopeMainWindow.h - Main window of the GenePool scope library
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SCOPE_MAIN_WINDOW_H__
#define __GEP_SCOPE_MAIN_WINDOW_H__

#include <QtCore/QStateMachine>
#include <QtCore/QState>
#include <QtGui/QAction>
#include <QtGui/QMainWindow>

#include <GEPSystemController.h>

class QState;
class QStateMachine;
class QTabWidget;

namespace GEP {
namespace Scope {

class MainWindowContent;
class SequentialDiagram;
class WorldDisplay;

/*
 * Main window of the GenePool scope library
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
  MainWindow (System::Controller* controller);
  virtual ~MainWindow ();

  void setWorldDisplay (WorldDisplay* world_display);

signals:
  void signalFinished ();

protected:
  virtual void keyPressEvent (QKeyEvent* event);
  virtual void closeEvent (QCloseEvent* event);

private slots:
  void slotStateInitialized ();
  void slotStateRunning ();
  void slotStateStep ();
  void slotStateFinished ();

  void slotQuit ();
  void slotFitnessStatistics ();

  void slotUpdateOutput ();
  void slotActiveOperatorDisplayChanged ();

private:
  void startup ();
  void cleanup ();
  bool executeStep ();

private:
  System::Controller* _controller;

  MainWindowContent* _content;
  WorldDisplay* _world_display;
  SequentialDiagram* _fitness_diagram;

  QTabWidget* _operator_display_tab;

  QAction* _action_run;
  QAction* _action_single_step;
  QAction* _action_reset;
  QAction* _action_quit;

  QAction* _action_fitness_statistics;

  QStateMachine _state_machine;
  QState _state_initialized;
  QState _state_running;
  QState _state_step;
  QState _state_finished;

  bool _aborted;
};

}
}

#endif
