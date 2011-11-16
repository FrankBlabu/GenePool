/*
 * gep_system_individual.cpp - Base class for single individuals
 *
 * Frank Cieslok, Aug. 2011
 */

#include "GEPSystemIndividual.h"
#include "GEPSystemWorld.h"

namespace GEP {
namespace System {

//#**************************************************************************
// CLASS GEP::System::Individual
//#**************************************************************************

/* Constructor */
Individual::Individual (const Chromosome& chromosome)
  : Object (),
    _chromosome (chromosome)
{
}

/* Copy constructor */
Individual::Individual (const Individual& toCopy)
  : Object (toCopy),
    _chromosome (toCopy._chromosome)
{
}

/* Return number of genes in this individuals chromosome */
int Individual::getNumberOfGenes () const
{
  return _chromosome.size ();
}

/* Return individuals chromosome */
const Individual::Chromosome& Individual::getChromosome () const
{
  return _chromosome;
}

/* Access operator */
Individual::Gene& Individual::operator[] (int index)
{
  Q_ASSERT (index < _chromosome.size ());
  return _chromosome[index];
}

/* Access operator */
Individual::Gene Individual::operator[] (int index) const
{
  Q_ASSERT (index < _chromosome.size ());
  return _chromosome[index];
}

}
}
