/*
 * gep_system_mutation_operator.cpp - Base class for mutation operators
 *
 * Frank Cieslok, Aug. 2011
 */

#include "GEPSystemMutationOperator.h"
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
  for (uint i=0; i < population.getSize (); ++i)
    {
      Individual& individual = population[i];
      uint size = individual.getSize ();

      for (uint j=0; j < size; ++j)
        {
          if (_world->getRandom () <= _probability)
            {
              uint k = static_cast<uint> (floor (_world->getRandom () * (size - 1))) % (size - 1);
              std::swap (individual[j], individual[k % size]);
            }
        }
    }
}

}
}
