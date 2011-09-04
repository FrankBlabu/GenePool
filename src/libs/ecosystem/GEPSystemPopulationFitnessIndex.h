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

#include <QtCore/QMap>

#include <algorithm>
#include <vector>

namespace GEP {
namespace System {


//#**************************************************************************
// CLASS GEP::System::PopulationFitnessIndex
//#**************************************************************************

/*
 * Index for the individuals of a population based on their fitness
 */
class PopulationFitnessIndex
{
public:
  PopulationFitnessIndex (const Population& population, FitnessOperatorPtr fitness_operator);

  typedef QMap<Object::Id, double> FitnessMap;
  PopulationFitnessIndex (const Population& population, const FitnessMap& fitness_map);

  uint getSize () const;
  const Individual& getIndividual (uint index) const;

private:
  void computeIndexMap (const Population& population);

private:
  const Population& _population;

  typedef QMap<Object::Id, uint> IndexMap;
  IndexMap _index_map;

  std::vector<Object::Id> _sorted_ids;
};

}
}

#endif
