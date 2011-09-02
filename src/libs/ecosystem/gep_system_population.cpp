/*
 * gep_system_population.cpp - Population container
 *
 * Frank Cieslok, Aug. 2011
 */

#include "GEPSystemPopulation.h"

namespace GEP {
namespace System {

//#**************************************************************************
// CLASS GEP::System::Population
//#**************************************************************************

/* Constructor */
Population::Population ()
{
}

/* Copy constructor */
Population::Population (const Population& toCopy)
  : _individuals (toCopy._individuals)
{
}

/* Add individual to population */
void Population::add (const Individual& individual)
{
  _individuals.append (individual);
}

/* Access operator */
Individual& Population::operator[] (uint index)
{
  Q_ASSERT (index < static_cast<uint> (_individuals.size ()));
  return _individuals[index];
}

/* Access operator */
const Individual& Population::operator[] (uint index) const
{
  Q_ASSERT (index < static_cast<uint> (_individuals.size ()));
  return _individuals[index];
}



}
}
