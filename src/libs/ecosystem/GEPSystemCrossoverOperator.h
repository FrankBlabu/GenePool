/*
 * GEPSystemCrossoverOperator.h - Base class for crossover operators
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_CROSSOVER_OPERATOR_H__
#define __GEP_SYSTEM_CROSSOVER_OPERATOR_H__

#include "GEPSystemOperator.h"
#include "GEPSystemPopulation.h"
#include "GEPSystemShuffleComparator.h"
#include "GEPSystemDebug.h"

#include <algorithm>
#include <vector>

namespace GEP {
namespace System {

/*
 * Base class for Crossover operators
 */
class CrossoverOperator : public Operator
{
public:
    CrossoverOperator (World* world);
    virtual ~CrossoverOperator ();

    virtual void compute (Population& population) = 0;
};

/*
 * Base class for Crossover operators
 */
class PartiallyMatchedCrossoverOperator : public CrossoverOperator
{
public:
    PartiallyMatchedCrossoverOperator (World* world);
    virtual ~PartiallyMatchedCrossoverOperator ();

    virtual void compute (Population& population);
};

}
}

#endif
