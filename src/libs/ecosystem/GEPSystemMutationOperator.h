/*
 * GEPSystemMutationOperator.h - Base class for mutation operators
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_MUTATION_OPERATOR_H__
#define __GEP_SYSTEM_MUTATION_OPERATOR_H__

#include "GEPSystemOperator.h"
#include "GEPSystemPopulation.h"

namespace GEP {
namespace System {

/*
 * Base class for Mutation operators
 */
template <class T>
class MutationOperator : public Operator<T>
{
public:
    MutationOperator (const World<T>* world);
    virtual ~MutationOperator () {}

    virtual void compute (Population<T>& population) = 0;
};

/* Constructor */
template <class T>
MutationOperator<T>::MutationOperator (const World<T>* world)
  : Operator<T> (world)
{
}

}
}

#endif
