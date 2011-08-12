/*
 * GEPScopeMainWindow.h - Main window of the GenePool scope library
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SCOPE_MAIN_WINDOW_H__
#define __GEP_SCOPE_MAIN_WINDOW_H__

#include <QtGui/QAction>
#include <QtGui/QMainWindow>

namespace GEP {
namespace Scope {

class MainWindowContent;

/*
 * Main window of the GenePool scope library
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
  MainWindow ();
  virtual ~MainWindow ();

private slots:
  void slotRun ();
  void slotQuit ();

private:
  MainWindowContent* _content;

  QAction* _run_action;
  QAction* _quit_action;
};

}
}

#endif
