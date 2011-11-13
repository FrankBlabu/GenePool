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
int Individual::getSize () const
{
  return _chromosome.size ();
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

/* Create string representation of this individual */
QString Individual::toString () const
{
  QString s;

  QString separator;
  for (int i=0; i < _chromosome.size (); ++i)
    {
      s += separator + QString::number (_chromosome[i]);
      separator = ",";
    }

  return s;
}

}
}
