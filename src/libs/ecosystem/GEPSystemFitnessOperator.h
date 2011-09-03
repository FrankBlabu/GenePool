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
    FitnessOperator (World* world);
    virtual ~FitnessOperator ();

    virtual void initialize (const Population& population);
    virtual double compute (const Individual& individual) const = 0;
};

typedef QSharedPointer<FitnessOperator> FitnessOperatorPtr;

/*
 * Linear static scaled fitness operator
 */
class LinearStaticScaledFitnessOperator : public FitnessOperator
{
public:
  LinearStaticScaledFitnessOperator (World* world, double offset, double scale);
  virtual ~LinearStaticScaledFitnessOperator ();

  virtual double compute (const Individual& individual) const;

private:
  double _offset;
  double _scale;
};


/*
 * Linear dynamic scaled fitness operator
 */
class LinearDynamicScaledFitnessOperator : public FitnessOperator
{
public:
  LinearDynamicScaledFitnessOperator (World* world, double scale);
  virtual ~LinearDynamicScaledFitnessOperator ();

  virtual void initialize (const Population& population);
  virtual double compute (const Individual& individual) const;

private:
  double _scale;
  double _minimum_fitness;
};


}
}

#endif
