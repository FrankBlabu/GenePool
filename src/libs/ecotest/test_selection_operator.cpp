/*
 * test_selection_operator.cpp - Test for the selection operator
 *
 * Frank Cieslok, Aug. 2011
 */

#include "TestMain.h"

#include <GEPSystemSelectionOperator.h>

//#**************************************************************************
// CLASS FitnessSortingComparator
//#**************************************************************************

/*
 * Comparator for fitness based sorting
 */
class FitnessSortingComparator
{
public:
  FitnessSortingComparator (GEP::System::FitnessOperatorPtr fitness_operator);

  inline bool operator ()(const GEP::System::Individual* individual1, const GEP::System::Individual* individual2);

private:
  GEP::System::FitnessOperatorPtr _fitness_operator;
};

/* Constructor */
FitnessSortingComparator::FitnessSortingComparator (GEP::System::FitnessOperatorPtr fitness_operator)
  : _fitness_operator (fitness_operator)
{
}

/* Comparison operator */
inline bool FitnessSortingComparator::operator () (const GEP::System::Individual* individual1,
                                                   const GEP::System::Individual* individual2)
{
  return _fitness_operator->compute (*individual1) > _fitness_operator->compute (*individual2);
}

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
            (new GEP::System::LinearDynamicScaledFitnessOperator (&world, 1.0));

        fitness_operator->initialize (population);
        GEP::System::RemainderStochasticSamplingSelectionOperator selection_operator (&world, fitness_operator);

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
