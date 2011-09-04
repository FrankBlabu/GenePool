/*
 * test_population_fitness_index.cpp - Test for the population fitness index class
 *
 * Frank Cieslok, Aug. 2011
 */

#include "TestMain.h"

#include <GEPSystemPopulationFitnessIndex.h>

/*
 * Test population fitness index
 */
void TestMain::testPopulationFitnessIndex ()
{
  TestWorld world;
  GEP::System::Population population = generatePopulation (&world, 10, 10);

  typedef QMap<GEP::System::Object::Id, double> FitnessMap;
  FitnessMap fitness_map;

  for (GEP::System::Population::ConstIterator i = population.begin (); i != population.end (); ++i)
    {
      const GEP::System::Individual& individual = *i;
      fitness_map.insert (individual.getId (), world.getRandom ());
    }

  GEP::System::PopulationFitnessIndex fitness_index (population, fitness_map);

  QCOMPARE (population.getSize (), fitness_index.getSize ());

  double upper_bound = 1.0;
  for (uint i=0; i < fitness_index.getSize (); ++i)
    {
      const GEP::System::Individual& individual = fitness_index.getIndividual (i);

      FitnessMap::const_iterator pos = fitness_map.find (individual.getId ());
      Q_ASSERT (pos != fitness_map.end ());

      double fitness = pos.value ();

      QVERIFY (fitness <= upper_bound);
      upper_bound = fitness;
    }
}
