/*
 * GEPScopeMainWindow.h - Main window of the GenePool scope library
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SCOPE_MAIN_WINDOW_H__
#define __GEP_SCOPE_MAIN_WINDOW_H__

#include <QtGui/QAction>
#include <QtGui/QMainWindow>

#include <GEPSystemController.h>

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

protected:
  virtual void keyPressEvent (QKeyEvent* event);
  virtual void closeEvent (QCloseEvent* event);

private slots:
  void slotRun ();
  void slotStep ();
  void slotReset ();
  void slotQuit ();
  void slotFitnessStatistics ();

  void slotUpdateOutput ();
  void slotActiveOperatorDisplayChanged ();


private:
  void startup ();
  void cleanup ();
  bool executeStep ();

  void updateEnabledState ();

private:
  System::Controller* _controller;

  struct RunningMode { enum Type_t { STOPPED, RUNNING, SINGLE_STEP }; };
  typedef RunningMode::Type_t RunningMode_t;

  RunningMode_t _running_mode;

  MainWindowContent* _content;
  WorldDisplay* _world_display;
  SequentialDiagram* _fitness_diagram;

  QTabWidget* _operator_display_tab;

  QAction* _run_action;
  QAction* _step_action;
  QAction* _reset_action;
  QAction* _quit_action;

  QAction* _fitness_statistics_action;
};

}
}

#endif
