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

namespace GEP {
namespace Scope {

class MainWindowContent;
class LogSelectionDisplay;
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

private slots:
  void slotRun ();
  void slotStep ();
  void slotQuit ();

  void slotUpdateOutput ();

private:
  void startup ();
  void cleanup ();
  bool executeStep ();

private:
  System::Controller* _controller;
  bool _running;

  MainWindowContent* _content;
  WorldDisplay* _world_display;
  SequentialDiagram* _fitness_diagram;

  LogSelectionDisplay* _log_selection_display;

  QAction* _run_action;
  QAction* _step_action;
  QAction* _quit_action;
};

}
}

#endif
