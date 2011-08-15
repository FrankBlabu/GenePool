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

//#**************************************************************************
// CLASS GEP::System::FitnessOperator
//#**************************************************************************

/*
 * Base class for Fitness operators
 */
template <class T>
class FitnessOperator : public Operator
{
public:
    FitnessOperator () {}
    virtual ~FitnessOperator () {}

    virtual void initialize (const Population<T>& population);
    virtual double compute (const Individual<T>& individual) const = 0;

protected:
    virtual double getFitness (const Individual<T>& individual) const = 0;
};

/* Initialite fitness computation for a population */
template <class T>
void FitnessOperator<T>::initialize (const Population<T>& population)
{
  Q_UNUSED (population);
}

//#**************************************************************************
// CLASS GEP::System::LinearStaticScaledFitnessOperator
//#**************************************************************************

/*
 * Linear static scaled fitness operator
 */
template <class T>
class LinearStaticScaledFitnessOperator : public FitnessOperator<T>
{
public:
  LinearStaticScaledFitnessOperator (double offset, double scale);
  virtual ~LinearStaticScaledFitnessOperator () {}

  virtual double compute (const Individual<T>& individual) const;

private:
  double _offset;
  double _scale;
};

/* Constructor */
template <class T>
LinearStaticScaledFitnessOperator<T>::LinearStaticScaledFitnessOperator (double offset, double scale)
  : _offset (offset),
    _scale  (scale)
{
}

/* Compute fitness for a population */
template <class T>
double LinearStaticScaledFitnessOperator<T>::compute (const Individual<T>& individual) const
{
return individual.getFitness () * _scale + _offset;
}


//#**************************************************************************
// CLASS GEP::System::LinearDynamicScaledFitnessOperator
//#**************************************************************************

/*
 * Linear dynamic scaled fitness operator
 */
template <class T>
class LinearDynamicScaledFitnessOperator : public FitnessOperator<T>
{
public:
  LinearDynamicScaledFitnessOperator (double scale);
  virtual ~LinearDynamicScaledFitnessOperator () {}

  virtual void initialize (const Population<T>& population);
  virtual double compute (const Individual<T>& individual) const;

private:
  double _scale;
  double _minimum_fitness;
};

/* Constructor */
template <class T>
LinearDynamicScaledFitnessOperator<T>::LinearDynamicScaledFitnessOperator (double scale)
  : _scale           (scale),
    _minimum_fitness (0.0)
{
}

/* Initialite fitness computation for a population */
template <class T>
void LinearDynamicScaledFitnessOperator<T>::initialize (const Population<T>& population)
{
  _minimum_fitness = 0.0;

  for (typename Population<T>::ConstIterator i = population.begin (); i != population.end (); ++i)
    {
      const Individual<T>& individual = *i;
      _minimum_fitness = std::min (_minimum_fitness, getFitness (individual));
    }
}


/* Compute fitness for a population */
template <class T>
double LinearDynamicScaledFitnessOperator<T>::compute (const Individual<T>& individual) const
{
  return getFitness (individual) * _scale - _minimum_fitness;
}

}
}

#endif
