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
  TestPopulation population = generatePopulation ();

  typedef std::map<GEP::System::Object::Id, double> FitnessMap;
  FitnessMap fitness_map;

  for (TestPopulation::ConstIterator i = population.begin (); i != population.end (); ++i)
    {
      const TestIndividual& individual = *i;
      fitness_map.insert (std::make_pair (individual.getId (), _random_number_generator->generate ()));
    }

  GEP::System::PopulationFitnessIndex<uint> fitness_index (population, fitness_map);

  QCOMPARE (population.getSize (), fitness_index.getSize ());

  double upper_bound = 1.0;
  for (uint i=0; i < fitness_index.getSize (); ++i)
    {
      const TestIndividual& individual = fitness_index.getIndividual (i);

      FitnessMap::const_iterator pos = fitness_map.find (individual.getId ());
      Q_ASSERT (pos != fitness_map.end ());

      double fitness = pos->second;

      QVERIFY (fitness <= upper_bound);
      upper_bound = fitness;
    }
}
