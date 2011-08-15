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
        TestPopulation population = generatePopulation ();

        boost::shared_ptr< GEP::System::FitnessOperator<uint> > fitness_operator
            (new RandomFitnessOperator<uint> (population));

        GEP::System::RemainderStochasticSamplingSelectionOperator<uint> selection_operator (fitness_operator);
        selection_operator.setRandomNumberGenerator (_random_number_generator);

        TestPopulation selected;
        selection_operator.compute (population, &selected);

        QCOMPARE (population.getSize (), selected.getSize ());
      }
  }
}
