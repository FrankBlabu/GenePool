/*
 * GEPSystemDebug.h - Debug functions for GenePool classes
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_DEBUG_H__
#define __GEP_SYSTEM_DEBUG_H__

#include "GEPSystemIndividual.h"
#include "GEPSystemPopulation.h"

#include <QtDebug>

namespace GEP {
namespace System {

/*
 * Print single individual
 */
template <class T>
QDebug operator<< (QDebug out, const Individual<T>& individual)
{
  QVector<T> alleles;
  for (uint i=0; i < individual.getSize (); ++i)
    alleles.push_back (individual[i]);

  out.nospace () << "Individual {" << alleles << "}";
  return out.space();
}

/*
 * Print population
 */
template <class T>
QDebug operator<< (QDebug out, const Population<T>& population)
{
  out << "Population {\n";

  for (typename Population<T>::ConstIterator i = population.begin (); i != population.end (); ++i)
    out << *i << "\n";

  out << "}\n";

  return out;
}

}
}

#endif
