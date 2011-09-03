/*
 * GEPSystemMutationOperator.h - Base class for mutation operators
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_MUTATION_OPERATOR_H__
#define __GEP_SYSTEM_MUTATION_OPERATOR_H__

#include "GEPSystemOperator.h"
#include "GEPSystemIndividual.h"
#include "GEPSystemPopulation.h"
#include "GEPSystemDebug.h"

namespace GEP {
namespace System {

/*
 * Base class for Mutation operators
 */
class MutationOperator : public Operator
{
public:
    MutationOperator (World* world);
    virtual ~MutationOperator ();

    virtual void compute (Population& population) = 0;
};

typedef QSharedPointer<MutationOperator> MutationOperatorPtr;


/*
 * Base class for Mutation operators
 */
class SwappingMutationOperator : public MutationOperator
{
public:
    SwappingMutationOperator (World* world, double probability);
    virtual ~SwappingMutationOperator ();

    virtual void compute (Population& population);

private:
    double _probability;
};

}
}

#endif
