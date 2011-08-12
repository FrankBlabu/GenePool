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
class CrossoverOperator : public Operator
{
public:
    CrossoverOperator ();
    virtual ~CrossoverOperator ();

    virtual PopulationPtr compute (PopulationPtr population) = 0;
};

typedef boost::shared_ptr<CrossoverOperator> CrossoverOperatorPtr;

}
}

#endif
