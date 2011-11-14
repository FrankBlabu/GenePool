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
  typedef PopulationFitnessIndex::FitnessMap FitnessMap;
  PopulationFitnessIndexComparator (const FitnessMap& fitness_map);

  inline bool operator () (const Object::Id& id1, const Object::Id& id2) const;

private:
  const FitnessMap& _fitness_map;
};

/* Constructor */
PopulationFitnessIndexComparator::PopulationFitnessIndexComparator (const FitnessMap& fitness_map)
  : _fitness_map (fitness_map)
{
}

/* Comparison operator */
inline bool PopulationFitnessIndexComparator::operator () (const Object::Id& id1, const Object::Id& id2) const
{
  FitnessMap::ConstIterator i = _fitness_map.find (id1);
  Q_ASSERT (i != _fitness_map.end ());

  FitnessMap::ConstIterator j = _fitness_map.find (id2);
  Q_ASSERT (j != _fitness_map.end ());

  return i.value () > j.value ();
}

}


//#**************************************************************************
// CLASS GEP::System::PopulationFitnessIndex
//#**************************************************************************

/* Constructor */
PopulationFitnessIndex::PopulationFitnessIndex (const Population& population, const FitnessMap& fitness_map)
  : _population (population)
{
  int count = 0;
  for (Population::ConstIterator i = population.begin (); i != population.end (); ++i, ++count)
    {
      const Individual& individual = *i;
      _sorted_ids.append (individual.getId ());
      _index_map.insert (individual.getId (), count);
    }

  PopulationFitnessIndexComparator comparator (fitness_map);
  qSort (_sorted_ids.begin (), _sorted_ids.end (), comparator);
}

/*
 * Return n-th individual of the population sorted by its fitness
 */
const Individual& PopulationFitnessIndex::getIndividual (int index) const
{
  Q_ASSERT (index < _sorted_ids.size ());

  IndexMap::const_iterator pos = _index_map.find (_sorted_ids[index]);
  Q_ASSERT (pos != _index_map.end ());

  return _population[pos.value ()];
}

/*
 * Return size of the index table
 */
int PopulationFitnessIndex::getSize () const
{
  return _population.getSize ();
}


}
}
