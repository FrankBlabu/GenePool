/*
 * GEPSystemFitnessOperator.h - Base class for fitness operators
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_FITNESS_OPERATOR_H__
#define __GEP_SYSTEM_FITNESS_OPERATOR_H__

#include "GEPSystemOperator.h"
#include "GEPSystemPopulation.h"

namespace GEP {
namespace System {

/*
 * Base class for Fitness operators
 */
class FitnessOperator : public Operator
{
public:
    FitnessOperator ();
    virtual ~FitnessOperator ();

    virtual double compute (PopulationPtr population) = 0;
};

typedef boost::shared_ptr<FitnessOperator> FitnessOperatorPtr;

}
}

#endif
