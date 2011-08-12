/*
 * gep_system_population.cpp - Population container
 *
 * Frank Cieslok, Aug. 2011
 */

#include "GEPSystemPopulation.h"

#include <QtConcurrentMap>

namespace GEP {
namespace System {

//#**************************************************************************
// Local functions
//#**************************************************************************

namespace {

void computeIndividualFunc (IndividualPtr individual)
{
  individual->compute ();
}

}

//#**************************************************************************
// CLASS GEP::System::Population
//#**************************************************************************

/* Constructor */
Population::Population ()
: _individuals ()
{
}

/* Destructor */
Population::~Population ()
{
}

/* Compute current population state (individual fitness, ...) */
void Population::compute ()
{
  QtConcurrent::blockingMap (_individuals, &computeIndividualFunc);
}

/* Add individual to population */
void Population::add (IndividualPtr individual)
{
    _individuals.append (individual);
}

}
}
