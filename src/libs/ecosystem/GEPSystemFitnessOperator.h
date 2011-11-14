/*
 * GEPSystemFitnessOperator.h - Base class for fitness operators
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_FITNESS_OPERATOR_H__
#define __GEP_SYSTEM_FITNESS_OPERATOR_H__

#include "GEPSystemOperator.h"
#include "GEPSystemPopulation.h"

#include <QtCore/QMap>

namespace GEP {
namespace System {

/*
 * Base class for fitness operators
 */
class FitnessOperator : public Operator
{
public:
    FitnessOperator (World* world);
    virtual ~FitnessOperator ();

    typedef QMap<Object::Id, double> FitnessMap;

    virtual void initialize (const FitnessMap& fitness_map);
    virtual double compute (double fitness) const = 0;
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

  virtual void initialize (const FitnessMap& fitness_map);
  virtual double compute (double fitness) const;

private:
  double _offset;
  double _scale;

  double _minimum_fitness;
  double _maximum_fitness;
};


/*
 * Linear dynamic scaled fitness operator
 */
class LinearDynamicScaledFitnessOperator : public FitnessOperator
{
public:
  LinearDynamicScaledFitnessOperator (World* world, double scale);
  virtual ~LinearDynamicScaledFitnessOperator ();

  virtual void initialize (const FitnessMap& fitness_map);
  virtual double compute (double fitness) const;

private:
  double _scale;

  double _minimum_fitness;
  double _maximum_fitness;
};


}
}

#endif
