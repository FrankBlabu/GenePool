/*
 * GEPSystemCrossoverOperator.h - Base class for crossover operators
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_CROSSOVER_OPERATOR_H__
#define __GEP_SYSTEM_CROSSOVER_OPERATOR_H__

#include "GEPSystemOperator.h"
#include "GEPSystemPopulation.h"
#include "GEPSystemRandomNumberGenerator.h"
#include "GEPSystemShuffleComparator.h"
#include "GEPSystemDebug.h"

#include <algorithm>
#include <vector>

namespace GEP {
namespace System {

class Controller;

/*
 * Base class for Crossover operators
 */
class CrossoverOperator : public Operator
{
public:
    CrossoverOperator ();
    virtual ~CrossoverOperator ();

    virtual void compute (const Controller* controller, Population& population) = 0;
};

typedef QSharedPointer<CrossoverOperator> CrossoverOperatorPtr;

/*
 * Base class for Crossover operators
 */
class PartiallyMatchedCrossoverOperator : public CrossoverOperator
{
public:
    PartiallyMatchedCrossoverOperator ();
    virtual ~PartiallyMatchedCrossoverOperator ();

    virtual void compute (const Controller* controller, Population& population);

private:
    RandomNumberGenerator _random_number_generator;
};

}
}

#endif
