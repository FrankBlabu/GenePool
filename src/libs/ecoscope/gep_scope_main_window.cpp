/*
 * gep_scope_main_window.cpp - Main window of the GenePool scope library
 *
 * Frank Cieslok, Aug. 2011
 */

#include "GEPScopeMainWindow.h"
#include "GEPScopeTools.h"

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
  _content (0)
{
  _content = Tools::addWidgetToParent (new MainWindowContent (centralWidget ()));
}

/* Destructor */
MainWindow::~MainWindow ()
{
}

}
}
