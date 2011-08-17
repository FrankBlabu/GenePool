/*
 * GEPSystemPopulationFitnessIndex.h - Population indexing a population according
 *                                     to the individual fitness
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_POPULATION_FITNESS_INDEX_H__
#define __GEP_SYSTEM_POPULATION_FITNESS_INDEX_H__

#include "GEPSystemIndividual.h"
#include "GEPSystemFitnessOperator.h"
#include "GEPSystemPopulation.h"

#include <map>
#include <vector>

namespace GEP {
namespace System {

//#**************************************************************************
// CLASS GEP::System::PopulationFitnessIndexComparator
//#**************************************************************************
 namespace {

/*
 * Comparator class for sorting a population according to the individual fitness
 */
template <class T>
class PopulationFitnessIndexComparator
{
public:
  typedef boost::shared_ptr< FitnessOperator<T> > FitnessOperatorPtr;
  PopulationFitnessIndexComparator (const Population<T>& population, FitnessOperatorPtr fitness_operator);

  typedef std::map<Object::Id, double> FitnessMap;
  PopulationFitnessIndexComparator (const FitnessMap& fitness_map);

  inline bool operator () (const Object::Id& id1, const Object::Id& id2) const;

private:
  FitnessMap _fitness_map;
};

/* Constructor */
template <class T>
PopulationFitnessIndexComparator<T>::PopulationFitnessIndexComparator (const Population<T>& population, FitnessOperatorPtr fitness_operator)
{
  for (typename Population<T>::ConstIterator i = population.begin (); i != population.end (); ++i)
    {
      const Individual<T>& individual = *i;
      _fitness_map.insert (make_pair (individual.getId (), fitness_operator->getFitness ()));
    }
}

/* Constructor */
template <class T>
PopulationFitnessIndexComparator<T>::PopulationFitnessIndexComparator (const FitnessMap& fitness_map)
  : _fitness_map (fitness_map)
{
}

/* Comparison operator */
template <class T>
inline bool PopulationFitnessIndexComparator<T>::operator () (const Object::Id& id1, const Object::Id& id2) const
{
  FitnessMap::const_iterator i = _fitness_map.find (id1);
  Q_ASSERT (i != _fitness_map.end ());

  FitnessMap::const_iterator j = _fitness_map.find (id2);
  Q_ASSERT (j != _fitness_map.end ());

  return i->second > j->second;
}

}

//#**************************************************************************
// CLASS GEP::System::PopulationFitnessIndex
//#**************************************************************************

/*
 * Index for the individuals of a population based on their fitness
 */
template <class T>
class PopulationFitnessIndex
{
public:
  typedef boost::shared_ptr< FitnessOperator<T> > FitnessOperatorPtr;
  PopulationFitnessIndex (const Population<T>& population, FitnessOperatorPtr fitness_operator);

  typedef std::map<Object::Id, double> FitnessMap;
  PopulationFitnessIndex (const Population<T>& population, const FitnessMap& fitness_map);

  uint getSize () const;
  const Individual<T>& getIndividual (uint index) const;

private:
  void computeIndexMap (const Population<T>& population);

private:
  const Population<T>& _population;

  typedef std::map<Object::Id, uint> IndexMap;
  IndexMap _index_map;

  std::vector<Object::Id> _sorted_ids;
};

/* Constructor */
template <class T>
PopulationFitnessIndex<T>::PopulationFitnessIndex (const Population<T>& population, FitnessOperatorPtr fitness_operator)
  : _population (population)
{
  computeIndexMap (population);

  PopulationFitnessIndexComparator<T> comparator (population, fitness_operator);
  std::sort (_sorted_ids.begin (), _sorted_ids.end (), comparator);
}

/* Constructor */
template <class T>
PopulationFitnessIndex<T>::PopulationFitnessIndex (const Population<T>& population, const FitnessMap& fitness_map)
  : _population (population)
{
  computeIndexMap (population);

  PopulationFitnessIndexComparator<T> comparator (fitness_map);
  std::sort (_sorted_ids.begin (), _sorted_ids.end (), comparator);
}

/*
 * Return n-th individual of the population sorted by its fitness
 */
template <class T>
const Individual<T>& PopulationFitnessIndex<T>::getIndividual (uint index) const
{
  Q_ASSERT (index < _sorted_ids.size ());

  IndexMap::const_iterator pos = _index_map.find (_sorted_ids[index]);
  Q_ASSERT (pos != _index_map.end ());

  return _population[pos->second];
}

/*
 * Return size of the index table
 */
template <class T>
uint PopulationFitnessIndex<T>::getSize () const
{
  return _population.getSize ();
}

/*
 * Compute internal index map
 */
template <class T>
void PopulationFitnessIndex<T>::computeIndexMap (const Population<T>& population)
{
  uint count = 0;
  for (typename Population<T>::ConstIterator i = population.begin (); i != population.end (); ++i, ++count)
    {
      const Individual<T>& individual = *i;
      _sorted_ids.push_back (individual.getId ());
      _index_map.insert (std::make_pair (individual.getId (), count));
    }
}

}
}

#endif
