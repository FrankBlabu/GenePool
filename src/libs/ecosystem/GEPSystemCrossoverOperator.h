/*
 * GEPSystemCrossoverOperator.h - Base class for crossover operators
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_CROSSOVER_OPERATOR_H__
#define __GEP_SYSTEM_CROSSOVER_OPERATOR_H__

#include "GEPSystemOperator.h"
#include "GEPSystemPopulation.h"

namespace GEP {
namespace System {

/*
 * Base class for Crossover operators
 */
template <class T>
class CrossoverOperator : public Operator<T>
{
public:
    CrossoverOperator (const World<T>* world);
    virtual ~CrossoverOperator () {}

    virtual void compute (Population<T>& population) = 0;
};

/* Constructor */
template <class T>
CrossoverOperator<T>::CrossoverOperator (const World<T>* world)
  : Operator<T> (world)
{
}

}
}

#endif
