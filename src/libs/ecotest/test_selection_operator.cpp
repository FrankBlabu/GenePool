/*
 * test_selection_operator.cpp - Test for the selection operator
 *
 * Frank Cieslok, Aug. 2011
 */

#include "TestMain.h"

#include <GEPSystemSelectionOperator.h>
#include <GEPSystemController.h>


//#**************************************************************************
// CLASS TestMain
//#**************************************************************************

/*
 * Test selection operators
 */
void TestMain::testSelectionOperator ()
{
  static const int POPULATION_SIZE = 10;
  static const int INDIVIDUAL_SIZE = 10;

  QBENCHMARK {
    for (int i=0; i < 1000; ++i)
      {
        TestWorld world (POPULATION_SIZE, INDIVIDUAL_SIZE);
        GEP::System::Population population = world.generatePopulation ();

        QSharedPointer<GEP::System::FitnessOperator> fitness_operator
            (new GEP::System::LinearDynamicScaledFitnessOperator (1.0));

        TestWorld::FitnessMap fitness = world.computeFitnessMap (population);

        fitness_operator->initialize (fitness);
        GEP::System::RemainderStochasticSamplingSelectionOperator selection_operator;

        GEP::System::Population selected = population;
        selection_operator.compute (selected);

        QCOMPARE (population.getSize (), selected.getSize ());

        fitness_operator->initialize (population);

        double sum1 = 0.0;
        for (int i=0; i < population.getSize (); ++i)
          sum1 += fitness_operator->compute (population[i]);

        fitness_operator->initialize (selected);

        double sum2 = 0.0;
        for (int i=0; i < selected.getSize (); ++i)
          sum2 += fitness_operator->compute (selected[i]);
      }
  }
}
