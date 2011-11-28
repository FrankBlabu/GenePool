/*
 * test_main.cpp - Main file for test cases
 *
 * Frank Cieslok, Aug. 2011
 */

#include "GEPSystemShuffleComparator.h"
#include "TestMain.h"

#include <QtCore/QString>
#include <QtTest/QtTest>

#include <algorithm>


//#**************************************************************************
// CLASS TestWorld
//#**************************************************************************

/* Constructor */
TestWorld::TestWorld (int population_size, int individual_size)
  : GEP::System::World (),
    _population_size (population_size),
    _individual_size (individual_size)

{
  Q_ASSERT (population_size > 0);
  Q_ASSERT (individual_size > 0);
}

/* Destructor */
TestWorld::~TestWorld ()
{
}

/* Generate world */
void TestWorld::generateWorld ()
{
}

/* Generate world population */
GEP::System::Population TestWorld::generatePopulation ()
{
  GEP::System::Population population;

  for (int i=0; i < _population_size; ++i)
    {
      GEP::System::Individual::Chromosome chromosome;
      for (int j=0; j < _individual_size; ++j)
        chromosome.append (j);

      GEP::System::ShuffleComparator<GEP::System::Individual::Gene> comparator (chromosome);
      qSort (chromosome.begin (), chromosome.end (), comparator);

      population.add (GEP::System::Individual (chromosome));
    }

  return population;
}

/* Get fitness direction type */
TestWorld::FitnessType_t TestWorld::getFitnessType () const
{
  return FitnessType::HIGHER_IS_BETTER;
}

/* Get random number */
double TestWorld::computeFitness (const GEP::System::Individual& individual) const
{
  double fitness = 0.0;

  for (int i=0; i < individual.getNumberOfGenes (); ++i)
    fitness += (i + 1) * individual[i];

  return fmod (fitness / 100.0, 1.0);
}

/* Compute fitness map for a population */
TestWorld::FitnessMap TestWorld::computeFitnessMap (const GEP::System::Population& population) const
{
  FitnessMap fitness;

  for (GEP::System::Population::ConstIterator i = population.begin (); i != population.end (); ++i)
    {
      const GEP::System::Individual& individual = *i;
      fitness.insert (individual.getId (), computeFitness (individual));
    }

  return fitness;
}


//#**************************************************************************
// CLASS TestController
//#**************************************************************************

/* Constructor */
TestController::TestController (GEP::System::World* world)
  : GEP::System::SinglePopulationController (world)
{
}

/* Destructor */
TestController::~TestController ()
{
}

/* Return current fitness map */
const TestController::FitnessMap& TestController::getFitnessMap () const
{
  return _fitness;
}


//#**************************************************************************
// CLASS TestMain
//#**************************************************************************

/* Constructor */
TestMain::TestMain ()
{
}


QTEST_MAIN (TestMain);
