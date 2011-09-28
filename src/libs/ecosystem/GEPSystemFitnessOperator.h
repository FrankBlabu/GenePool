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

    virtual void initialize (const Population& population);
    virtual double compute (const Individual& individual) = 0;
};

typedef QSharedPointer<FitnessOperator> FitnessOperatorPtr;

/*
 * Base class for cached fitness operators
 */
class CachedFitnessOperator : public FitnessOperator
{
public:
    CachedFitnessOperator (World* world);
    virtual ~CachedFitnessOperator ();

    virtual void initialize (const Population& population);
    virtual double compute (const Individual& individual) = 0;

protected:
    void normalizeFitness ();

protected:
    typedef QMap<Object::Id, double> FitnessMap;
    FitnessMap _fitness_cache;
};


/*
 * Linear static scaled fitness operator
 */
class LinearStaticScaledFitnessOperator : public CachedFitnessOperator
{
public:
  LinearStaticScaledFitnessOperator (World* world, double offset, double scale);
  virtual ~LinearStaticScaledFitnessOperator ();

  virtual void initialize (const Population& population);
  virtual double compute (const Individual& individual);

private:
  double _offset;
  double _scale;
};


/*
 * Linear dynamic scaled fitness operator
 */
class LinearDynamicScaledFitnessOperator : public CachedFitnessOperator
{
public:
  LinearDynamicScaledFitnessOperator (World* world, double scale);
  virtual ~LinearDynamicScaledFitnessOperator ();

  virtual void initialize (const Population& population);
  virtual double compute (const Individual& individual);

private:
  double _scale;
};


}
}

#endif
