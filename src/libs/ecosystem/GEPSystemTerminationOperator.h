/*
 * GEPSystemTerminationOperator.h - Base class for termination operators
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_TERMINATION_OPERATOR_H__
#define __GEP_SYSTEM_TERMINAATION_OPERATOR_H__

#include "GEPSystemOperator.h"
#include "GEPSystemPopulation.h"

namespace GEP {
namespace System {

/*
 * Base class for termination operators
 */
class TerminationOperator : public Operator
{
public:
    TerminationOperator (World* world);
    virtual ~TerminationOperator ();

    virtual int getNumberOfSteps () const = 0;
    virtual bool compute (const Population& population, int step) = 0;
};

typedef QSharedPointer<TerminationOperator> TerminationOperatorPtr;


/*
 * Termination after a fixed number of steps
 */
class FixedStepTerminationOperator : public TerminationOperator
{
public:
    FixedStepTerminationOperator (World* world, int steps);
    virtual ~FixedStepTerminationOperator ();

    virtual int getNumberOfSteps () const;
    virtual bool compute (const Population& population, int step);

private:
    int _steps;
};

}
}

#endif
