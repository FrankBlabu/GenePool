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
#include "GEPSystemRandomNumberGenerator.h"
#include "GEPSystemDebug.h"

namespace GEP {
namespace System {

class Controller;

/*
 * Base class for Mutation operators
 */
class MutationOperator : public Operator
{
public:
    MutationOperator ();
    virtual ~MutationOperator ();

    virtual void compute (const Controller* controller, Population& population) = 0;
};

typedef QSharedPointer<MutationOperator> MutationOperatorPtr;


/*
 * Base class for Mutation operators
 */
class SwappingMutationOperator : public MutationOperator
{
public:
    SwappingMutationOperator (double probability);
    virtual ~SwappingMutationOperator ();

    virtual void compute (const Controller* controller, Population& population);

private:
    RandomNumberGenerator _random_number_generator;
    double _probability;
};

}
}

#endif
