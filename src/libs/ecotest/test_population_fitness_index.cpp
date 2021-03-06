/*
 * test_population_fitness_index.cpp - Test for the population fitness index class
 *
 * Frank Cieslok, Aug. 2011
 */

#include "TestMain.h"

#include <GEPSystemPopulationFitnessIndex.h>
#include <GEPSystemRandomNumberGenerator.h>

/*
 * Test population fitness index
 */
void TestMain::testPopulationFitnessIndex ()
{
  static const int POPULATION_SIZE = 10;
  static const int INDIVIDUAL_SIZE = 10;

  TestWorld world (POPULATION_SIZE, INDIVIDUAL_SIZE);
  GEP::System::RandomNumberGenerator random_number_generator;

  GEP::System::Population population = world.generatePopulation ();

  typedef QMap<GEP::System::Object::Id, double> FitnessMap;
  FitnessMap fitness_map;

  for (GEP::System::Population::ConstIterator i = population.begin (); i != population.end (); ++i)
    {
      const GEP::System::Individual& individual = *i;
      double fitness = random_number_generator.generate ();
      fitness_map.insert (individual.getId (), fitness);
    }

  GEP::System::PopulationFitnessIndex fitness_index (population, fitness_map);

  QCOMPARE (population.getSize (), fitness_index.getSize ());

  double upper_bound = 1.0;
  for (int i=0; i < fitness_index.getSize (); ++i)
    {
      const GEP::System::Individual& individual = fitness_index.getIndividual (i);

      FitnessMap::const_iterator pos = fitness_map.find (individual.getId ());
      Q_ASSERT (pos != fitness_map.end ());

      double fitness = pos.value ();

      QVERIFY (fitness <= upper_bound);
      upper_bound = fitness;
    }
}
