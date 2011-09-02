/*
 * GEPSystemSelectionOperator.h - Base class for selection operators
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_SELECTION_OPERATOR_H__
#define __GEP_SYSTEM_SELECTION_OPERATOR_H__

#include "GEPSystemOperator.h"
#include "GEPSystemFitnessOperator.h"
#include "GEPSystemPopulation.h"
#include "GEPSystemPopulationFitnessIndex.h"

#include <math.h>
#include <map>

namespace GEP {
namespace System {

/*
 * Base class for selection operators
 */
class SelectionOperator : public Operator
{
public:
  typedef QSharedPointer<FitnessOperator> FitnessOperatorPtr;

public:
    SelectionOperator (World* world, FitnessOperatorPtr fitness_operator);
    virtual ~SelectionOperator ();

    virtual void compute (Population& population) const = 0;

protected:
    FitnessOperatorPtr _fitness_operator;
};


/*
 * Selection operator based on remainder stochastic sampling
 */
class RemainderStochasticSamplingSelectionOperator : public SelectionOperator
{
public:
    RemainderStochasticSamplingSelectionOperator (World* world, FitnessOperatorPtr fitness_operator);
    virtual ~RemainderStochasticSamplingSelectionOperator ();

    virtual void compute (Population& population) const;
};

}
}

#endif
