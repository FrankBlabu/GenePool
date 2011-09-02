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

//#**************************************************************************
// NAMESPACE GEP::System::Debug
//#**************************************************************************

/*
 * Print single individual
 */
QDebug operator<< (QDebug out, const Individual& individual)
{
  QVector<QVariant> alleles;
  for (uint i=0; i < individual.getSize (); ++i)
    alleles.push_back (individual[i]);

  out.nospace () << "Individual {" << alleles << "}";
  return out.space();
}

/*
 * Print population
 */
QDebug operator<< (QDebug out, const Population& population)
{
  out << "Population {\n";

  for (Population::ConstIterator i = population.begin (); i != population.end (); ++i)
    out << *i << "\n";

  out << "}\n";

  return out;
}

}
}
