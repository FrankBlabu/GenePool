/*
 * gep_system_mutation_operator.cpp - Base class for mutation operators
 *
 * Frank Cieslok, Aug. 2011
 */

#define GEP_DEBUG

#include "GEPSystemMutationOperator.h"
#include "GEPSystemNotifier.h"
#include "GEPSystemRandomNumberGenerator.h"
#include "GEPSystemDebug.h"

#include <math.h>
#include <boost/bind.hpp>

#include <QtConcurrentMap>

namespace GEP {
namespace System {

//#**************************************************************************
// CLASS GEP::System::MutationOperator
//#**************************************************************************

/* Constructor */
MutationOperator::MutationOperator ()
  : Operator ()
{
}

/* Destructor */
MutationOperator::~MutationOperator ()
{
}

//#**************************************************************************
// CLASS GEP::System::SwappingMutationOperator
//#**************************************************************************

/* Constructor */
SwappingMutationOperator::SwappingMutationOperator (double probability)
  : MutationOperator (),
    _probability (probability)
{
}

/* Destructor */
SwappingMutationOperator::~SwappingMutationOperator ()
{
}

/* Mutate population */
void SwappingMutationOperator::compute (const Controller* controller, Population& population)
{
  MutationNotificationList notifications;

  QtConcurrent::blockingMap (population.begin (), population.end (),
                             boost::bind (&SwappingMutationOperator::executeMutation, this, controller, &notifications, _1));

  System::Notifier::getNotifier ()->notifyMutation (notifications);
}

/* Execute mutation on a single individual */
void SwappingMutationOperator::executeMutation (const Controller* controller,
                                                QList<MutationNotification>* notifications,
                                                Individual& individual)
{
  RandomNumberGenerator random_number_generator;

  int size = individual.getNumberOfGenes ();

  IndividualInfo before (individual, controller->getFitness (individual));

  for (int i=0; i < size; ++i)
    {
      if (random_number_generator.generate () <= _probability)
        {
          int index = static_cast<int> (floor (random_number_generator.generate () * (size - 1))) % (size - 1);
          qSwap (individual[i], individual[index % size]);
        }
    }

  IndividualInfo after (individual);
  MutationNotification notification (before, after);

  _mutex.lock ();
  notifications->append (notification);
  _mutex.unlock ();
}

}
}
