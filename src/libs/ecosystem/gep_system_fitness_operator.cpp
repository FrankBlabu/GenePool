/*
 * gep_system_fitness_operator.cpp - Base class for fitness operators
 *
 * Frank Cieslok, Aug. 2011
 */

#define GEP_DEBUG

#include "GEPSystemFitnessOperator.h"
#include "GEPSystemDebug.h"

#include <limits>


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
// CLASS GEP::System::CachedFitnessOperator
//#**************************************************************************

/* Constructor */
CachedFitnessOperator::CachedFitnessOperator (World* world)
  : FitnessOperator (world)
{
}

/* Destructor */
CachedFitnessOperator::~CachedFitnessOperator ()
{
}

/* Initialite fitness computation for a population */
void CachedFitnessOperator::initialize (const Population& population)
{
  Q_ASSERT (population.getSize () > 0);

  _fitness_cache.clear ();

  for (Population::ConstIterator i = population.begin (); i != population.end (); ++i)
    {
      const Individual& individual = *i;
      _fitness_cache.insert (individual.getId (), _world->getFitness (individual));
    }
}

/* Normalize cached fitness values */
void CachedFitnessOperator::normalizeFitness ()
{
  Q_ASSERT (!_fitness_cache.isEmpty ());

  double fitness_sum = 0.0;

  for (FitnessMap::ConstIterator i = _fitness_cache.begin (); i != _fitness_cache.end (); ++i)
    fitness_sum += i.value ();

  for (FitnessMap::Iterator i = _fitness_cache.begin (); i != _fitness_cache.end (); ++i)
    i.value () /= fitness_sum;
}


//#**************************************************************************
// CLASS GEP::System::LinearStaticScaledFitnessOperator
//#**************************************************************************

/* Constructor */
LinearStaticScaledFitnessOperator::LinearStaticScaledFitnessOperator (World* world, double offset, double scale)
  : CachedFitnessOperator (world),
    _offset (offset),
    _scale  (scale)
{
}

/* Destructor */
LinearStaticScaledFitnessOperator::~LinearStaticScaledFitnessOperator ()
{
}

/* Initialite fitness computation for a population */
void LinearStaticScaledFitnessOperator::initialize (const Population& population)
{
  CachedFitnessOperator::initialize (population);
  normalizeFitness ();
}

/* Compute fitness for a population */
double LinearStaticScaledFitnessOperator::compute (const Individual& individual)
{
  FitnessMap::const_iterator pos = _fitness_cache.find (individual.getId ());
  Q_ASSERT (pos != _fitness_cache.end ());

  return _offset + pos.value () * _scale;
}


//#**************************************************************************
// CLASS GEP::System::LinearDynamicScaledFitnessOperator
//#**************************************************************************

/* Constructor */
LinearDynamicScaledFitnessOperator::LinearDynamicScaledFitnessOperator (World* world, double scale)
  : CachedFitnessOperator  (world),
    _scale (scale)
{
}

/* Destructor */
LinearDynamicScaledFitnessOperator::~LinearDynamicScaledFitnessOperator ()
{
}

/* Initialite fitness computation for a population */
void LinearDynamicScaledFitnessOperator::initialize (const Population& population)
{
  CachedFitnessOperator::initialize (population);
  normalizeFitness ();
}

/* Compute fitness for a population */
double LinearDynamicScaledFitnessOperator::compute (const Individual& individual)
{
  FitnessMap::const_iterator pos = _fitness_cache.find (individual.getId ());
  Q_ASSERT (pos != _fitness_cache.end ());

  return pos.value () * pos.value () * _scale;
}

}
}
