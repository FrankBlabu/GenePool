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
  const uint NUMBER_OF_RUNS = 1;
  const uint POPULATION_SIZE = 10;
  const uint INDIVIDUAL_SIZE = 10;
}

/*
 * Test crossover operators
 */
void TestMain::testMutationOperator ()
{
  for (uint i=0; i < NUMBER_OF_RUNS; ++i)
    {
      TestWorld world;
      GEP::System::Population population = generatePopulation (&world, POPULATION_SIZE, INDIVIDUAL_SIZE);

      GEP::System::SwappingMutationOperator mutation_operator (&world, 1.0 / INDIVIDUAL_SIZE);

      GEP::System::Population mutated = population;
      mutation_operator.compute (mutated);

      uint expected = 0;
      for (uint j=0; j < INDIVIDUAL_SIZE; ++j)
        expected += j;

      for (GEP::System::Population::ConstIterator j = mutated.begin (); j != mutated.end (); ++j)
        {
          const GEP::System::Individual& individual = *j;

          uint sum = 0;
          for (uint k=0; k < individual.getSize (); ++k)
            sum += individual[k].toUInt ();

          QCOMPARE (sum, expected);
        }

      QCOMPARE (population.getSize (), mutated.getSize ());
    }
}

