/*
 * gep_system_individual.cpp - Base class for single individuals
 *
 * Frank Cieslok, Aug. 2011
 */

#include "GEPSystemIndividual.h"

#include <QtGlobal>

namespace GEP {
namespace System {

//#**************************************************************************
// CLASS GEP::System::Individual
//#**************************************************************************

/* Constructor */
Individual::Individual ()
  : _fitness (0.0)
{
}

/* Destructor */
Individual::~Individual ()
{
}

/* Return fitness of this individual */
double Individual::getFitness () const
{
  Q_ASSERT (_fitness != 0.0);
  return _fitness;
}

}
}
