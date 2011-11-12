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
// CLASS GEP::System::ControllerStepNotifcation
//#**************************************************************************

/* Constructor */
ControllerStepNotification::ControllerStepNotification ()
{
}

/* Constructor */
ControllerStepNotification::ControllerStepNotification (Controller* controller)
  : _step (controller->getCurrentStep ())
{
  _fitness.insert (Controller::FitnessType::MINIMUM, controller->getCurrentFitness (Controller::FitnessType::MINIMUM));
  _fitness.insert (Controller::FitnessType::AVERAGE, controller->getCurrentFitness (Controller::FitnessType::AVERAGE));
  _fitness.insert (Controller::FitnessType::MAXIMUM, controller->getCurrentFitness (Controller::FitnessType::MAXIMUM));
}

/* Get fitness of the given type */
double ControllerStepNotification::getFitness (Controller::FitnessType_t type) const
{
  FitnessMap::ConstIterator pos = _fitness.find (type);
  Q_ASSERT (pos != _fitness.end ());
  return pos.value ();
}

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

/* Notify new controller step */
void Notifier::notifyControllerStep (const ControllerStepNotification& notification)
{
  if (_enabled)
    emit signalControllerStep (notification);
}

/* Notify individual selection */
void Notifier::notifySelection (const SelectionNotificationList& notifications)
{
  if (_enabled)
    emit signalSelection (notifications);
}

/* Notify that a crossover operation has been performed */
void Notifier::notifyCrossover (const CrossoverNotificationList& notifications)
{
  if (_enabled)
    emit signalCrossover (notifications);
}

/* Notify that a mutation operation has been performed */
void Notifier::notifyMutation (const MutationNotificationList& notifications)
{
  if (_enabled)
    emit signalMutation (notifications);
}

/* Notify that the individual focus changed */
void Notifier::notifyIndividualFocusChanged (const Object::Id& id)
{
  if (_enabled)
    emit signalIndividualFocusChanged (id);
}

}
}

