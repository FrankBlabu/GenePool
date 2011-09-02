/*
 * gep_system_individual.cpp - Base class for single individuals
 *
 * Frank Cieslok, Aug. 2011
 */

#include "GEPSystemIndividual.h"

namespace GEP {
namespace System {

//#**************************************************************************
// CLASS GEP::System::Individual
//#**************************************************************************

/* Constructor */
Individual::Individual (const std::vector<QVariant>& genes)
  : Object (),
    _genes (genes)
{
}

/* Copy constructor */
Individual::Individual (const Individual& toCopy)
  : Object (),
    _genes (toCopy._genes)
{
}

/* Return number of genes in this individual */
uint Individual::getSize () const
{
  return _genes.size ();
}

/* Access operator */
QVariant& Individual::operator[] (uint index)
{
  Q_ASSERT (index < _genes.size ());
  return _genes[index];
}

/* Access operator */
const QVariant& Individual::operator[] (uint index) const
{
  Q_ASSERT (index < static_cast<uint> (_genes.size ()));
  return _genes[index];
}


}
}
