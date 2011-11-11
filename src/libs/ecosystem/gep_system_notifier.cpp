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
void Notifier::notifySelection (const SelectionNotification& notification)
{
  if (_enabled)
    emit signalSelection (notification);
}

/* Notify that a crossover operation has been performed */
void Notifier::notifyCrossover (const CrossoverNotification& notification)
{
  if (_enabled)
    emit signalCrossover (notification);
}

/* Notify that a mutation operation has been performed */
void Notifier::notifyMutation (const MutationNotification& notification)
{
  if (_enabled)
    emit signalMutation (notification);
}

/* Notify that the individual focus changed */
void Notifier::notifyIndividualFocusChanged (const Object::Id& id)
{
  if (_enabled)
    emit signalIndividualFocusChanged (id);
}

}
}

