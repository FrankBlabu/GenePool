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
  const uint NUMBER_OF_RUNS = 1;
  const uint POPULATION_SIZE = 10;
  const uint INDIVIDUAL_SIZE = 10;
}

/*
 * Test crossover operators
 */
void TestMain::testCrossoverOperator ()
{
  for (uint i=0; i < NUMBER_OF_RUNS; ++i)
    {
      TestWorld world;
      TestPopulation population = generatePopulation (POPULATION_SIZE, INDIVIDUAL_SIZE);

      boost::shared_ptr< GEP::System::FitnessOperator<uint> > fitness_operator
          (new RandomFitnessOperator<uint> (&world, population));

      GEP::System::PartiallyMatchedCrossoverOperator<uint> crossover_operator (&world);

      TestPopulation crossed = population;
      crossover_operator.compute (crossed);

      uint expected = 0;
      for (uint j=0; j < INDIVIDUAL_SIZE; ++j)
        expected += j;

      for (TestPopulation::ConstIterator j = crossed.begin (); j != crossed.end (); ++j)
        {
          const TestIndividual& individual = *j;

          uint sum = 0;
          for (uint k=0; k < individual.getSize (); ++k)
            sum += individual[k];

          QCOMPARE (sum, expected);
        }

      QCOMPARE (population.getSize (), crossed.getSize ());
    }
}

