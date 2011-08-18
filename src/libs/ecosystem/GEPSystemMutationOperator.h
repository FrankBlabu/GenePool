/*
 * GEPSystemMutationOperator.h - Base class for mutation operators
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_MUTATION_OPERATOR_H__
#define __GEP_SYSTEM_MUTATION_OPERATOR_H__

#include "GEPSystemOperator.h"
#include "GEPSystemIndividual.h"
#include "GEPSystemPopulation.h"
#include "GEPSystemDebug.h"

namespace GEP {
namespace System {

//#**************************************************************************
// CLASS GEP::System::MutationOperator
//#**************************************************************************

/*
 * Base class for Mutation operators
 */
template <class T>
class MutationOperator : public Operator<T>
{
public:
    MutationOperator (World<T>* world);
    virtual ~MutationOperator () {}

    virtual void compute (Population<T>& population) = 0;
};

/* Constructor */
template <class T>
MutationOperator<T>::MutationOperator (World<T>* world)
  : Operator<T> (world)
{
}

//#**************************************************************************
// CLASS GEP::System::SwappingMutationOperator
//#**************************************************************************

/*
 * Base class for Mutation operators
 */
template <class T>
class SwappingMutationOperator : public MutationOperator<T>
{
public:
    SwappingMutationOperator (World<T>* world, double probability);
    virtual ~SwappingMutationOperator () {}

    virtual void compute (Population<T>& population);

private:
    double _probability;
};

/* Constructor */
template <class T>
SwappingMutationOperator<T>::SwappingMutationOperator (World<T>* world, double probability)
  : MutationOperator<T> (world),
    _probability (probability)
{
}

/* Mutate population */
template <class T>
void SwappingMutationOperator<T>::compute (Population<T>& population)
{
  for (uint i=0; i < population.getSize (); ++i)
    {
      Individual<T>& individual = population[i];
      uint size = individual.getSize ();

      for (uint j=0; j < size; ++j)
        {
          if (Operator<T>::_world->getRandom () <= _probability)
            {
              uint k = static_cast<uint> (floor (Operator<T>::_world->getRandom () * (size - 1))) % (size - 1);
              std::swap (individual[j], individual[k % size]);
            }
        }
    }
}

}
}

#endif
