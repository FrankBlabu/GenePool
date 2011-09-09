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
Individual::Individual (const QVariantList& genes)
  : Object (),
    _genes (genes)
{
}

/* Copy constructor */
Individual::Individual (const Individual& toCopy)
  : Object (toCopy),
    _genes (toCopy._genes)
{
}

/* Return number of genes in this individual */
int Individual::getSize () const
{
  return _genes.size ();
}

/* Access operator */
QVariant& Individual::operator[] (int index)
{
  Q_ASSERT (index < _genes.size ());
  return _genes[index];
}

/* Access operator */
const QVariant& Individual::operator[] (int index) const
{
  Q_ASSERT (index < _genes.size ());
  return _genes[index];
}

/* Create string representation of this individual */
QString Individual::toString () const
{
  QString s;

  QString separator;
  for (int i=0; i < _genes.size (); ++i)
    {
      s += separator + convertToString (_genes[i]);
      separator = ",";
    }

  return s;
}

}
}
