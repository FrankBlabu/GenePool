/*
 * gep_system_population_fitness_index.cpp - Class indexing a population according
 *                                           to the individual fitness
 *
 * Frank Cieslok, Aug. 2011
 */

#include "GEPSystemPopulationFitnessIndex.h"
#include <map>

namespace GEP {
namespace System {

//#**************************************************************************
// CLASS GEP::System::PopulationFitnessIndexComparator
//#**************************************************************************

namespace {

/*
 * Comparator class for sorting a population according to the individual fitness
 */
class PopulationFitnessIndexComparator
{
public:
  typedef QSharedPointer<FitnessOperator> FitnessOperatorPtr;
  PopulationFitnessIndexComparator (const Population& population, FitnessOperatorPtr fitness_operator);

  typedef QMap<Object::Id, double> FitnessMap;
  PopulationFitnessIndexComparator (const FitnessMap& fitness_map);

  inline bool operator () (const Object::Id& id1, const Object::Id& id2) const;

private:
  FitnessMap _fitness_map;
};

/* Constructor */
PopulationFitnessIndexComparator::PopulationFitnessIndexComparator (const Population& population, FitnessOperatorPtr fitness_operator)
{
  for (Population::ConstIterator i = population.begin (); i != population.end (); ++i)
    {
      const Individual& individual = *i;
      _fitness_map.insert (individual.getId (), fitness_operator->compute (individual));
    }
}

/* Constructor */
PopulationFitnessIndexComparator::PopulationFitnessIndexComparator (const FitnessMap& fitness_map)
  : _fitness_map (fitness_map)
{
}

/* Comparison operator */
inline bool PopulationFitnessIndexComparator::operator () (const Object::Id& id1, const Object::Id& id2) const
{
  FitnessMap::const_iterator i = _fitness_map.find (id1);
  Q_ASSERT (i != _fitness_map.end ());

  FitnessMap::const_iterator j = _fitness_map.find (id2);
  Q_ASSERT (j != _fitness_map.end ());

  return i.value () > j.value ();
}

}


//#**************************************************************************
// CLASS GEP::System::PopulationFitnessIndex
//#**************************************************************************

/* Constructor */
PopulationFitnessIndex::PopulationFitnessIndex (const Population& population, FitnessOperatorPtr fitness_operator)
  : _population (population)
{
  computeIndexMap (population);

  PopulationFitnessIndexComparator comparator (population, fitness_operator);
  std::sort (_sorted_ids.begin (), _sorted_ids.end (), comparator);
}

/* Constructor */
PopulationFitnessIndex::PopulationFitnessIndex (const Population& population, const FitnessMap& fitness_map)
  : _population (population)
{
  computeIndexMap (population);

  PopulationFitnessIndexComparator comparator (fitness_map);
  std::sort (_sorted_ids.begin (), _sorted_ids.end (), comparator);
}

/*
 * Return n-th individual of the population sorted by its fitness
 */
const Individual& PopulationFitnessIndex::getIndividual (uint index) const
{
  Q_ASSERT (index < _sorted_ids.size ());

  IndexMap::const_iterator pos = _index_map.find (_sorted_ids[index]);
  Q_ASSERT (pos != _index_map.end ());

  return _population[pos.value ()];
}

/*
 * Return size of the index table
 */
uint PopulationFitnessIndex::getSize () const
{
  return _population.getSize ();
}

/*
 * Compute internal index map
 */
void PopulationFitnessIndex::computeIndexMap (const Population& population)
{
  uint count = 0;
  for (Population::ConstIterator i = population.begin (); i != population.end (); ++i, ++count)
    {
      const Individual& individual = *i;
      _sorted_ids.push_back (individual.getId ());
      _index_map.insert (individual.getId (), count);
    }
}

}
}
