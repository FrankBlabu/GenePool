/*
 * gep_system_fitness_operator.cpp - Base class for fitness operators
 *
 * Frank Cieslok, Aug. 2011
 */

#define GEP_DEBUG

#include "GEPSystemFitnessOperator.h"
#include "GEPSystemDebug.h"

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
    _scale          (scale),
    _fitness_cache  ()
{
}

/* Destructor */
LinearStaticScaledFitnessOperator::~LinearStaticScaledFitnessOperator ()
{
}

/* Initialite fitness computation for a population */
void LinearStaticScaledFitnessOperator::initialize (const Population& population)
{
  Q_UNUSED (population);
  _fitness_cache.clear ();
}

/* Compute fitness for a population */
double LinearStaticScaledFitnessOperator::compute (const Individual& individual)
{
  double fitness = 0.0;

  FitnessMap::const_iterator pos = _fitness_cache.find (individual.getId ());
  if (pos == _fitness_cache.end ())
    {
      fitness = _world->getFitness (individual) * _scale + _offset;
      _fitness_cache.insert (individual.getId (), fitness);
    }
  else
    fitness = pos.value ();

  return fitness;
}


//#**************************************************************************
// CLASS GEP::System::LinearDynamicScaledFitnessOperator
//#**************************************************************************

/* Constructor */
LinearDynamicScaledFitnessOperator::LinearDynamicScaledFitnessOperator (World* world, double scale)
  : FitnessOperator  (world),
    _scale           (scale),
    _minimum_fitness (0.0),
    _fitness_cache   ()
{
}

/* Destructor */
LinearDynamicScaledFitnessOperator::~LinearDynamicScaledFitnessOperator ()
{
}

/* Initialite fitness computation for a population */
void LinearDynamicScaledFitnessOperator::initialize (const Population& population)
{
  _fitness_cache.clear ();
  _minimum_fitness = 0.0;

  for (Population::ConstIterator i = population.begin (); i != population.end (); ++i)
    {
      const Individual& individual = *i;

      double fitness = _world->getFitness (individual);

      _minimum_fitness = std::min (_minimum_fitness, _world->getFitness (individual));
      _fitness_cache.insert (individual.getId (), fitness);
    }
}


/* Compute fitness for a population */
double LinearDynamicScaledFitnessOperator::compute (const Individual& individual)
{
  FitnessMap::const_iterator pos = _fitness_cache.find (individual.getId ());

  Q_ASSERT (pos != _fitness_cache.end ());

  return pos.value () * _scale - _minimum_fitness;
}

}
}
