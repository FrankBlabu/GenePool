/*
 * gep_system_notifier.cpp - Notifier for algorithm events
 *
 * Frank Cieslok, Sep. 2011
 */

#define GEP_DEBUG

#include "GEPSystemNotifier.h"
#include "GEPSystemDebug.h"

#include <limits>

namespace GEP {
namespace System {

//#**************************************************************************
// CLASS GEP::System::IndividualInfo
//#**************************************************************************

/* Unknown fitness constant [STATIC] */
const double IndividualInfo::UNKNOWN_FITNESS = std::numeric_limits<double>::max ();

/* Constructor */
IndividualInfo::IndividualInfo ()
  : _id         (),
    _chromosome (),
    _fitness    (UNKNOWN_FITNESS)
{
}

/* Constructor */
IndividualInfo::IndividualInfo (const Individual& individual)
  : _id         (individual.getId ()),
    _chromosome (individual.getChromosome ()),
    _fitness    (UNKNOWN_FITNESS)
{
}

/* Constructor */
IndividualInfo::IndividualInfo (const Individual& individual, double fitness)
  : _id         (individual.getId ()),
    _chromosome (individual.getChromosome ()),
    _fitness    (fitness)
{
}

/* Copy-Constructor */
IndividualInfo::IndividualInfo (const IndividualInfo& toCopy)
  : _id         (toCopy._id),
    _chromosome (toCopy._chromosome),
    _fitness    (toCopy._fitness)
{
}


//#**************************************************************************
// CLASS GEP::System::ControllerStepNotifcation
//#**************************************************************************

/* Constructor */
ControllerStepNotification::ControllerStepNotification ()
{
}

/* Constructor */
ControllerStepNotification::ControllerStepNotification (Controller* controller)
  : _step            (controller->getCurrentStep ()),
    _average_fitness (controller->getCurrentAverageFitness ()),
    _temperature     (controller->getTemperature ())
{
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

/* Notify emerging controller step */
void Notifier::notifyControllerStepStart (const ControllerStepNotification& notification)
{
  if (_enabled)
    emit signalControllerStepStart (notification);
}

/* Notify completed controller step */
void Notifier::notifyControllerStepEnd (const ControllerStepNotification& notification)
{
  if (_enabled)
    emit signalControllerStepEnd (notification);
}

/* Notify world reset */
void Notifier::notifyReset ()
{
  if (_enabled)
    emit signalReset ();
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

/* Notify that the individual focus has changed */
void Notifier::notifyIndividualFocusChanged (const Object::Id& id)
{
  if (_enabled)
    emit signalIndividualFocusChanged (id);
}

}
}

