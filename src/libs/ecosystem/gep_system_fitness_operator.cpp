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
FitnessOperator::FitnessOperator ()
  : Operator ()
{
}

/* Destructor */
FitnessOperator::~FitnessOperator ()
{
}

/* Initialite fitness computation for a population */
void FitnessOperator::initialize (const FitnessMap& fitness_map)
{
  Q_UNUSED (fitness_map);
}

//#**************************************************************************
// CLASS GEP::System::LinearStaticScaledFitnessOperator
//#**************************************************************************

/* Constructor */
LinearStaticScaledFitnessOperator::LinearStaticScaledFitnessOperator (double offset, double scale)
  : FitnessOperator (),
    _offset          (offset),
    _scale           (scale),
    _minimum_fitness (0.0),
    _maximum_fitness (0.0)
{
}

/* Destructor */
LinearStaticScaledFitnessOperator::~LinearStaticScaledFitnessOperator ()
{
}

/* Initialite fitness computation for a population */
void LinearStaticScaledFitnessOperator::initialize (const FitnessMap& fitness_map)
{
  _minimum_fitness = std::numeric_limits<double>::max ();
  _maximum_fitness = -std::numeric_limits<double>::max ();

  for (FitnessMap::ConstIterator i = fitness_map.begin (); i != fitness_map.end (); ++i)
    {
      double fitness = _offset + i.value () * _scale;
      _minimum_fitness = qMin (_minimum_fitness, fitness);
      _maximum_fitness = qMax (_maximum_fitness, fitness);
    }
}

/* Compute fitness for a population */
double LinearStaticScaledFitnessOperator::compute (double fitness) const
{
  return ((_offset + fitness * _scale) - _minimum_fitness) / (_maximum_fitness - _minimum_fitness);
}


//#**************************************************************************
// CLASS GEP::System::LinearDynamicScaledFitnessOperator
//#**************************************************************************

/* Constructor */
LinearDynamicScaledFitnessOperator::LinearDynamicScaledFitnessOperator (double scale)
  : FitnessOperator (),
    _scale           (scale),
    _minimum_fitness (0.0),
    _maximum_fitness (0.0)
{
}

/* Destructor */
LinearDynamicScaledFitnessOperator::~LinearDynamicScaledFitnessOperator ()
{
}

/* Initialite fitness computation for a population */
void LinearDynamicScaledFitnessOperator::initialize (const FitnessMap& fitness_map)
{
  _minimum_fitness = std::numeric_limits<double>::max ();
  _maximum_fitness = -std::numeric_limits<double>::max ();

  for (FitnessMap::ConstIterator i = fitness_map.begin (); i != fitness_map.end (); ++i)
    {
      double fitness = i.value () * i.value () * _scale;
      _minimum_fitness = qMin (_minimum_fitness, fitness);
      _maximum_fitness = qMax (_maximum_fitness, fitness);
    }
}

/* Compute fitness for a population */
double LinearDynamicScaledFitnessOperator::compute (double fitness) const
{
  return ((fitness * fitness * _scale) - _minimum_fitness) / (_maximum_fitness - _minimum_fitness);
}

}
}
