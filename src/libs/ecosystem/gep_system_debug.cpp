/*
 * gep_system_debug.cpp - Debug functions for GenePool classes
 *
 * Frank Cieslok, Aug. 2011
 */

#include "GEPSystemDebug.h"
#include "GEPSystemIndividual.h"
#include "GEPSystemPopulation.h"

namespace GEP {
namespace System {

/*
 * Print single individual
 */
QDebug operator<< (QDebug out, const Individual& individual)
{
  out.nospace () << "Individual {" << individual.getChromosome () << "}";
  return out;
}

/*
 * Print population
 */
QDebug operator<< (QDebug out, const Population& population)
{
  out.nospace () << "Population {\n";

  for (Population::ConstIterator i = population.begin (); i != population.end (); ++i)
    out << *i << "\n";

  out << "}\n";

  return out;
}

}
}
