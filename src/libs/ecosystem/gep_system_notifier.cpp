/*
 * gep_system_notifier.cpp - Notifier for algorithm events
 *
 * Frank Cieslok, Sep. 2011
 */

#define GEP_DEBUG

#include "GEPSystemNotifier.h"
#include "GEPSystemDebug.h"

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

/* Return singleton instance [STATIC] */
Notifier* Notifier::getNotifier ()
{
  static Notifier notifier;
  return &notifier;
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

/* Notify individual creation */
void Notifier::notifyIndividualCreated (const Object::Id& id)
{
  if (_enabled)
    emit signalIndividualCreated (id);
}

/* Notify new controller step */
void Notifier::notifyControllerStep ()
{
  if (_enabled)
    emit signalControllerStep ();
}

/* Notify individual selection */
void Notifier::notifySelection (const Object::Id& before, const Object::Id& after)
{
  if (_enabled)
    emit signalSelection (before, after);
}

/* Notify that a crossover operation is going to be performed */
void Notifier::notifyPreCrossover (const Object::Id& object1, const Object::Id& object2)
{
  if (_enabled)
    emit signalPreCrossover (object1, object2);
}

/* Notify that a crossover operation has been performed */
void Notifier::notifyCrossover (const Object::Id& object1, const Object::Id& object2)
{
  if (_enabled)
    emit signalCrossover (object1, object2);
}

/* Notify that a mutation operation is going to be performed */
void Notifier::notifyPreMutation (const Object::Id& id)
{
  if (_enabled)
    emit signalPreMutation (id);
}

/* Notify that a mutation operation has been performed */
void Notifier::notifyMutation (const Object::Id& id)
{
  if (_enabled)
    emit signalMutation (id);
}

/* Notify that the individual focus changed */
void Notifier::notifyIndividualFocusChanged (const Object::Id& id)
{
  if (_enabled)
    emit signalIndividualFocusChanged (id);
}

}
}

