/*
 * gep_scope_operator_display.cpp - Base class for alle operator displays
 *
 * Frank Cieslok, Sep. 2011
 */

#define GEP_DEBUG

#include "GEPScopeOperatorDisplay.h"
#include "GEPScopeTools.h"

#include <GEPSystemController.h>
#include <GEPSystemNotifier.h>
#include <GEPSystemDebug.h>

#include <QtGui/QHeaderView>

namespace GEP {
namespace Scope {

//#**************************************************************************
// CLASS GEP::Scope::OperatorDisplayItem
//#**************************************************************************

/* Constructor */
OperatorDisplayItem::OperatorDisplayItem (const System::Object::Id& id, QTreeWidget* widget)
  : QTreeWidgetItem (widget),
    _id (id)
{
}

/* Destructor */
OperatorDisplayItem::~OperatorDisplayItem ()
{
}

/* Get object id this item represents */
const System::Object::Id& OperatorDisplayItem::getId () const
{
  return _id;
}


//#**************************************************************************
// CLASS GEP::Scope::OperatorDisplay
//#**************************************************************************

/* Constructor */
OperatorDisplay::OperatorDisplay (System::Controller* controller, QWidget* parent)
  : QTreeWidget (parent),
    _controller (controller),
    _active (false)
{
  setAllColumnsShowFocus (true);
  setRootIsDecorated (false);
  setSortingEnabled (true);
  setSelectionMode (SingleSelection);

  connect (this, SIGNAL (itemSelectionChanged ()), SLOT (slotSelectionChanged ()));
}

/* Destructor */
OperatorDisplay::~OperatorDisplay ()
{
}

/* Get if this display is currently active */
bool OperatorDisplay::getActive () const
{
  return _active;
}

/* Set if this display is currently active */
void OperatorDisplay::setActive (bool active)
{
  _active = active;

  if (_active)
    slotSelectionChanged ();
}

/* Returns the controller instance belonging to this display */
System::Controller* OperatorDisplay::getController () const
{
  return _controller;
}

/* Create representation for an individuals fitness value */
QString OperatorDisplay::getFitnessRepresentation (const System::IndividualInfo& info) const
{
  return info.getFitness () != System::IndividualInfo::UNKNOWN_FITNESS ?
        QString::number (info.getFitness (), 'g', 8) : QString ("-");
}

/* Called if the item selection changed */
void OperatorDisplay::slotSelectionChanged ()
{
  System::Notifier* notifier = System::Notifier::getNotifier ();

  if (_active)
    {
      if (selectedItems ().size () == 1)
        {
          OperatorDisplayItem* item = dynamic_cast<OperatorDisplayItem*> (selectedItems ().front ());
          Q_ASSERT (item != 0);

          notifier->notifyIndividualFocusChanged (item->getId ());
        }
      else
        notifier->notifyIndividualFocusChanged (System::Object::INVALID);
    }
}



}
}
