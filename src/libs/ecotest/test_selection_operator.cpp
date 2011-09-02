/*
 * test_selection_operator.cpp - Test for the selection operator
 *
 * Frank Cieslok, Aug. 2011
 */

#include "TestMain.h"

#include <GEPSystemSelectionOperator.h>


/*
 * Test selection operators
 */
void TestMain::testSelectionOperator ()
{
  QBENCHMARK {
    for (uint i=0; i < 1000; ++i)
      {
        TestWorld world;
        GEP::System::Population population = generatePopulation (&world, 10, 10);

        QSharedPointer<GEP::System::FitnessOperator> fitness_operator
            (new RandomFitnessOperator (&world, population));

        GEP::System::RemainderStochasticSamplingSelectionOperator selection_operator (&world, fitness_operator);

        GEP::System::Population selected = population;
        selection_operator.compute (selected);

        QCOMPARE (population.getSize (), selected.getSize ());
      }
  }
}
