/*
 * gep_system_notifier.cpp - Notifier for algorithm events
 *
 * Frank Cieslok, Sep. 2011
 */

#include "GEPSystemNotifier.h"

namespace GEP {
namespace System {


//#**************************************************************************
// CLASS GEP::System::Notifier
//#**************************************************************************

/* Constructor */
Notifier::Notifier ()
  : _enabled (true)
{
}

/* Reads if notifying is currently enabled */
bool Notifier::getEnabled () const
{
  return _enabled;
}

/* Sets if notifying is currently enabled */
void Notifier::setEnabled (bool enabled)
{
  _enabled = enabled;
}

/* Notify new controller step */
void Notifier::notifyControllerStep ()
{
}

/* Notify individual selection */
void Notifier::notifyIndividualSelection (const Object::Id& before, const Object::Id& after)
{
  Q_UNUSED (before);
  Q_UNUSED (after);
}

}
}

