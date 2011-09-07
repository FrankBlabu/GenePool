/*
 * gep_log_selection_display.cpp - Log display for selection steps
 *
 * Frank Cieslok, Sep. 2011
 */

#include "GEPScopeLogSelectionDisplay.h"
#include "GEPScopeTools.h"
#include "GEPSystemWorld.h"

#include "ui_gep_scope_log_display_tree.h"

namespace GEP {
namespace Scope {

//#**************************************************************************
// CLASS GEP::Scope::LogSelectionDisplayImpl
//#**************************************************************************

/*
 * Widget implementing class
 */
class LogSelectionDisplayImpl : public QWidget, private Ui::LogDisplayTree
{
public:
  LogSelectionDisplayImpl (QWidget* parent);
  virtual ~LogSelectionDisplayImpl ();
};

/* Constructor */
LogSelectionDisplayImpl::LogSelectionDisplayImpl (QWidget* parent)
  : QWidget(parent)
{
    setupUi(this);
}

/* Destructor */
LogSelectionDisplayImpl::~LogSelectionDisplayImpl ()
{
}


//#**************************************************************************
// CLASS GEP::Scope::LogSelectionDisplay
//#**************************************************************************

/* Constructor Ü*/
LogSelectionDisplay::LogSelectionDisplay (System::World* world, QWidget* parent)
  : QWidget (parent),
    _content (0)
{
  Q_UNUSED (world);

  _content = Tools::addWidgetToParent (new LogSelectionDisplayImpl (this));
}

/* Destructor */
LogSelectionDisplay::~LogSelectionDisplay ()
{
}

}
}
