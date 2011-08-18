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
        TestPopulation population = generatePopulation (10, 10);

        QSharedPointer< GEP::System::FitnessOperator<uint> > fitness_operator
            (new RandomFitnessOperator<uint> (&world, population));

        GEP::System::RemainderStochasticSamplingSelectionOperator<uint> selection_operator (&world, fitness_operator);

        TestPopulation selected = population;
        selection_operator.compute (selected);

        QCOMPARE (population.getSize (), selected.getSize ());
      }
  }
}
