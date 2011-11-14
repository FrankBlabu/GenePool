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
  PopulationFitnessIndexComparator (const Controller* controller);

  inline bool operator () (const Object::Id& id1, const Object::Id& id2) const;

private:
  const Controller* _controller;
};

/* Constructor */
PopulationFitnessIndexComparator::PopulationFitnessIndexComparator (const Controller* controller)
  : _controller (controller)
{
}

/* Constructor */
PopulationFitnessIndexComparator::PopulationFitnessIndexComparator (const FitnessMap& fitness_map)
  : _fitness_map (fitness_map)
{
}

/* Comparison operator */
inline bool PopulationFitnessIndexComparator::operator () (const Object::Id& id1, const Object::Id& id2) const
{
  return _controller->getFitness (id1) > _controller->getFitness (id2);
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
  qSort (_sorted_ids.begin (), _sorted_ids.end (), comparator);
}

/* Constructor */
PopulationFitnessIndex::PopulationFitnessIndex (const Population& population, const FitnessMap& fitness_map)
  : _population (population)
{
  computeIndexMap (population);

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

/*
 * Compute internal index map
 */
void PopulationFitnessIndex::computeIndexMap (const Population& population)
{
  int count = 0;
  for (Population::ConstIterator i = population.begin (); i != population.end (); ++i, ++count)
    {
      const Individual& individual = *i;
      _sorted_ids.append (individual.getId ());
      _index_map.insert (individual.getId (), count);
    }
}

}
}
