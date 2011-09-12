/*
 * gep_scope_operator_display.cpp - Base class for alle operator displays
 *
 * Frank Cieslok, Sep. 2011
 */

#include "GEPScopeOperatorDisplay.h"
#include "GEPScopeTools.h"

#include <QtGui/QHeaderView>

namespace GEP {
namespace Scope {

//#**************************************************************************
// CLASS GEP::Scope::OperatorDisplay
//#**************************************************************************

/* Constructor */
OperatorDisplay::OperatorDisplay (QWidget* parent)
  : QTreeWidget (parent)
{
  setAllColumnsShowFocus (true);
  setRootIsDecorated (false);
  setSortingEnabled (true);
}

/* Destructor */
OperatorDisplay::~OperatorDisplay ()
{
}

}
}
