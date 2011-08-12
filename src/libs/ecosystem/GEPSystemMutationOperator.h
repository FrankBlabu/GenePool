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
class MutationOperator : public Operator
{
public:
    MutationOperator ();
    virtual ~MutationOperator ();

    virtual PopulationPtr compute (PopulationPtr population) = 0;
};

typedef boost::shared_ptr<MutationOperator> MutationOperatorPtr;

}
}

#endif
