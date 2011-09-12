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
  emit signalControllerStep ();
}

/* Notify individual selection */
void Notifier::notifySelection (const Object::Id& before, const Object::Id& after)
{
  emit signalSelection (before, after);
}

/* Notify that a crossover operation is going to be performed */
void Notifier::notifyPreCrossover (const Object::Id& object1, const Object::Id& object2)
{
  emit signalPreCrossover (object1, object2);
}

/* Notify that a crossover operation has been performed */
void Notifier::notifyCrossover (const Object::Id& object1, const Object::Id& object2)
{
  emit signalCrossover (object1, object2);
}

/* Notify that a mutation operation is going to be performed */
void Notifier::notifyPreMutation (const Object::Id& id)
{
  emit signalPreMutation (id);
}

/* Notify that a mutation operation has been performed */
void Notifier::notifyMutation (const Object::Id& id)
{
  emit signalMutation (id);
}

}
}

