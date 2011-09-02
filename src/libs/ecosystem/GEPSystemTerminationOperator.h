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

    virtual bool compute (const Population& population, uint step) = 0;
};


/*
 * Termination after a fixed number of steps
 */
class FixedStepTerminationOperator : public TerminationOperator
{
public:
    FixedStepTerminationOperator (World* world, uint steps);
    virtual ~FixedStepTerminationOperator ();

    virtual bool compute (const Population& population, uint step);

private:
    uint _steps;
};

}
}

#endif
