/*
 * test_population_fitness_index.cpp - Test for the population fitness index class
 *
 * Frank Cieslok, Aug. 2011
 */

#include "TestMain.h"

#include <GEPSystemPopulationFitnessIndex.h>

#include <QDebug>

/*
 * Test population fitness index
 */
void TestMain::testPopulationFitnessIndex ()
{
  TestWorld world;
  GEP::System::Population population = generatePopulation (&world, 10, 10);

  qDebug () << "*** Test ***";

  typedef QMap<GEP::System::Object::Id, double> FitnessMap;
  FitnessMap fitness_map;

  qDebug () << "Generate:";

  for (GEP::System::Population::ConstIterator i = population.begin (); i != population.end (); ++i)
    {
      const GEP::System::Individual& individual = *i;
      double fitness = world.getRandom ();
      fitness_map.insert (individual.getId (), fitness);

      qDebug () << "  " << individual.getId () << ": " << fitness;
    }

  GEP::System::PopulationFitnessIndex fitness_index (population, fitness_map);

  QCOMPARE (population.getSize (), fitness_index.getSize ());

  qDebug () << "Sorted:";

  double upper_bound = 1.0;
  for (int i=0; i < fitness_index.getSize (); ++i)
    {
      const GEP::System::Individual& individual = fitness_index.getIndividual (i);

      FitnessMap::const_iterator pos = fitness_map.find (individual.getId ());
      Q_ASSERT (pos != fitness_map.end ());

      double fitness = pos.value ();

      qDebug () << "  " << individual.getId () << ": " << fitness;

      QVERIFY (fitness <= upper_bound);
      upper_bound = fitness;
    }
}
