/*
 * GEPSystemDebug.h - Debug functions for GenePool classes
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_DEBUG_H__
#define __GEP_SYSTEM_DEBUG_H__

#include "GEPSystemFitnessOperator.h"
#include "GEPSystemIndividual.h"
#include "GEPSystemPopulation.h"

#include <QtDebug>
#include <QtCore/QString>
#include <QtCore/QTextStream>

namespace GEP {
namespace System {

namespace Debug {

typedef std::map<Object::Id, double> FitnessMap;

/*
 * Print single individual
 */
template <class T>
void print (const Individual<T>& individual, double fitness)
{
  QString text;
  QTextStream out (&text);

  out << "Individual { [";

  QString separator = "";
  for (uint i=0; i < individual.getSize (); ++i)
    {
      out << separator << individual[i];
      separator = ", ";
    }

  out << "], " << fitness << " }";

  qDebug () << text;
}

template <class T>
void print (const Individual<T>& individual, const FitnessMap& fitness_map)
{
  FitnessMap::const_iterator pos = fitness_map.find (individual.getId ());
  if (pos != fitness_map.end ())
    print (individual, pos->second);
  else
    print (individual, 0.0);
}

template <class T>
void print (const Individual<T>& individual, boost::shared_ptr< FitnessOperator<T> > fitness_operator)
{
  print (individual, fitness_operator->compute (individual));
}

/*
 * Print population
 */
template <class T>
void print (const Population<T>& population, const FitnessMap& fitness_map)
{
  qDebug () << "Population {";

  for (typename Population<T>::ConstIterator i = population.begin (); i != population.end (); ++i)
    {
      const Individual<T>& individual = *i;
      print (individual, fitness_map);
    }

  qDebug () << "}";
}

template <class T>
void print (const Population<T>& population, boost::shared_ptr< FitnessOperator<T> > fitness_operator)
{
  qDebug () << "Population {";

  for (typename Population<T>::ConstIterator i = population.begin (); i != population.end (); ++i)
    {
      const Individual<T>& individual = *i;
      print (individual, fitness_operator);
    }

  qDebug () << "}";
}

}

}
}

#endif
