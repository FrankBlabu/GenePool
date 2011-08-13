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
template <class T>
class TerminationOperator : public Operator
{
public:
    TerminationOperator () {}
    virtual ~TerminationOperator () {}

    virtual bool compute (const Population<T>& population, uint step) = 0;
};

}
}

#endif
