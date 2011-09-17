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
MutationOperator::MutationOperator (World* world)
  : Operator (world)
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
SwappingMutationOperator::SwappingMutationOperator (World* world, double probability)
  : MutationOperator (world),
    _probability (probability)
{
}

/* Destructor */
SwappingMutationOperator::~SwappingMutationOperator ()
{
}

/* Mutate population */
void SwappingMutationOperator::compute (Population& population)
{
  Notifier* notifier = System::Notifier::getNotifier ();

  for (int i=0; i < population.getSize (); ++i)
    {
      Individual& individual = population[i];
      int size = individual.getSize ();

      notifier->notifyPreMutation (individual.getId ());

      for (int j=0; j < size; ++j)
        {
          if (_random_number_generator.generate () <= _probability)
            {
              int k = static_cast<int> (floor (_random_number_generator.generate () * (size - 1))) % (size - 1);
              std::swap (individual[j], individual[k % size]);
            }
        }

      notifier->notifyMutation (individual.getId ());
    }
}

}
}
