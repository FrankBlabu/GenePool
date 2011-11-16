/*
 * gep_system_mutation_operator.cpp - Base class for mutation operators
 *
 * Frank Cieslok, Aug. 2011
 */

#include "GEPSystemMutationOperator.h"
#include "GEPSystemNotifier.h"

#include <math.h>

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

  for (int i=0; i < population.getSize (); ++i)
    {
      Individual& individual = population[i];
      int size = individual.getNumberOfGenes ();

      IndividualInfo before (individual, controller->getFitness (individual));

      for (int j=0; j < size; ++j)
        {
          if (_random_number_generator.generate () <= _probability)
            {
              int k = static_cast<int> (floor (_random_number_generator.generate () * (size - 1))) % (size - 1);
              qSwap (individual[j], individual[k % size]);
            }
        }

      IndividualInfo after (individual);
      notifications.append (MutationNotification (before, after));
    }

  System::Notifier::getNotifier ()->notifyMutation (notifications);
}

}
}
