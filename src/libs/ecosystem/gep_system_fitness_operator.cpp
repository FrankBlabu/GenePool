/*
 * gep_system_fitness_operator.cpp - Base class for fitness operators
 *
 * Frank Cieslok, Aug. 2011
 */

#include "GEPSystemFitnessOperator.h"

namespace GEP {
namespace System {

//#**************************************************************************
// CLASS GEP::System::FitnessOperator
//#**************************************************************************

/* Constructor */
FitnessOperator::FitnessOperator (World* world)
  : Operator (world)
{
}

/* Destructor */
FitnessOperator::~FitnessOperator ()
{
}

/* Initialite fitness computation for a population */
void FitnessOperator::initialize (const Population& population)
{
  Q_UNUSED (population);
}

//#**************************************************************************
// CLASS GEP::System::LinearStaticScaledFitnessOperator
//#**************************************************************************

/* Constructor */
LinearStaticScaledFitnessOperator::LinearStaticScaledFitnessOperator (World* world, double offset, double scale)
  : FitnessOperator (world),
    _offset         (offset),
    _scale          (scale)
{
}

/* Destructor */
LinearStaticScaledFitnessOperator::~LinearStaticScaledFitnessOperator ()
{
}

/* Compute fitness for a population */
double LinearStaticScaledFitnessOperator::compute (const Individual& individual) const
{
  return _world->getFitness (individual) * _scale + _offset;
}

//#**************************************************************************
// CLASS GEP::System::LinearDynamicScaledFitnessOperator
//#**************************************************************************

/* Constructor */
LinearDynamicScaledFitnessOperator::LinearDynamicScaledFitnessOperator (World* world, double scale)
  : FitnessOperator  (world),
    _scale           (scale),
    _minimum_fitness (0.0)
{
}

/* Destructor */
LinearDynamicScaledFitnessOperator::~LinearDynamicScaledFitnessOperator ()
{
}

/* Initialite fitness computation for a population */
void LinearDynamicScaledFitnessOperator::initialize (const Population& population)
{
  _minimum_fitness = 0.0;

  for (Population::ConstIterator i = population.begin (); i != population.end (); ++i)
    {
      const Individual& individual = *i;
      _minimum_fitness = std::min (_minimum_fitness, _world->getFitness (individual));
    }
}


/* Compute fitness for a population */
double LinearDynamicScaledFitnessOperator::compute (const Individual& individual) const
{
  return _world->getFitness (individual) * _scale - _minimum_fitness;
}

}
}
