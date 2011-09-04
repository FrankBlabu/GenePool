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
class SequentialDiagram;

/*
 * Main window of the GenePool scope library
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
  MainWindow (System::Controller* controller);
  virtual ~MainWindow ();

private slots:
  void slotRun ();
  void slotQuit ();

private:
  System::Controller* _controller;

  MainWindowContent* _content;
  SequentialDiagram* _fitness_diagram;

  QAction* _run_action;
  QAction* _quit_action;
};

}
}

#endif
