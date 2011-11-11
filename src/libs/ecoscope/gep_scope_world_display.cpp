/*
 * gep_scope_world_display.cpp - Base class for displaying the worlds current content
 *
 * Frank Cieslok, Sep. 2011
 */

#define GEP_DEBUG

#include <GEPSystemDebug.h>
#include <GEPSystemNotifier.h>
#include <GEPSystemWorld.h>

#include "GEPScopeWorldDisplay.h"

namespace GEP {
namespace Scope {

//#**************************************************************************
// CLASS GEP::Scope::WorldDisplay
//#**************************************************************************

/* Constructor */
WorldDisplay::WorldDisplay(const System::World* world, QWidget* parent)
  : QWidget (parent),
    _world       (world),
    _selected_id (System::Object::INVALID)
{
  connect (System::Notifier::getNotifier (), SIGNAL (signalIndividualFocusChanged (const GEP::System::Object::Id&)),
           SLOT (slotIndividualFocusChanged (const GEP::System::Object::Id&)));
}

/* Destructor */
WorldDisplay::~WorldDisplay()
{
}

/* Return currently selected id */
const System::Object::Id& WorldDisplay::getSelectedId () const
{
  return _selected_id;
}

/* Called when the currently selected individual changed */
void WorldDisplay::slotIndividualFocusChanged (const System::Object::Id& id)
{
  _selected_id = id;
  emit signalUpdate ();
}

}
}


