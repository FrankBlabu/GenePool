/*
 * test_mutation_operator.cpp - Test for the mutation operator
 *
 * Frank Cieslok, Aug. 2011
 */

#include "TestMain.h"

#include <GEPSystemMutationOperator.h>

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
void TestMain::testMutationOperator ()
{
  for (int i=0; i < NUMBER_OF_RUNS; ++i)
    {
      TestWorld world (POPULATION_SIZE, INDIVIDUAL_SIZE);
      GEP::System::Population population = world.generatePopulation ();

      GEP::System::SwappingMutationOperator mutation_operator (&world, 1.0 / INDIVIDUAL_SIZE);

      GEP::System::Population mutated = population;
      mutation_operator.compute (mutated);

      int expected = 0;
      for (int j=0; j < INDIVIDUAL_SIZE; ++j)
        expected += j;

      for (GEP::System::Population::ConstIterator j = mutated.begin (); j != mutated.end (); ++j)
        {
          const GEP::System::Individual& individual = *j;

          int sum = 0;
          for (int k=0; k < individual.getSize (); ++k)
            sum += individual[k];

          QCOMPARE (sum, expected);
        }

      QCOMPARE (population.getSize (), mutated.getSize ());
    }
}

