/*
 * test_crossover_operator.cpp - Test for the crossover operator
 *
 * Frank Cieslok, Aug. 2011
 */

#include "TestMain.h"

#include <GEPSystemCrossoverOperator.h>

/*
 * Test configuration
 */

namespace {
  const int NUMBER_OF_RUNS = 1;
  const int POPULATION_SIZE = 10;
  const int INDIVIDUAL_SIZE = 10;
}

/*
 * Test crossover operators
 */
void TestMain::testCrossoverOperator ()
{
  for (int i=0; i < NUMBER_OF_RUNS; ++i)
    {
      TestWorld world;
      GEP::System::Population population = generatePopulation (POPULATION_SIZE, INDIVIDUAL_SIZE);

      GEP::System::PartiallyMatchedCrossoverOperator crossover_operator (&world);

      GEP::System::Population crossed = population;
      crossover_operator.compute (crossed);

      int expected = 0;
      for (int j=0; j < INDIVIDUAL_SIZE; ++j)
        expected += j;

      for (GEP::System::Population::ConstIterator j = crossed.begin (); j != crossed.end (); ++j)
        {
          const GEP::System::Individual& individual = *j;

          int sum = 0;
          for (int k=0; k < individual.getSize (); ++k)
            sum += individual[k].toInt ();

          QCOMPARE (sum, expected);
        }

      QCOMPARE (population.getSize (), crossed.getSize ());
    }
}

