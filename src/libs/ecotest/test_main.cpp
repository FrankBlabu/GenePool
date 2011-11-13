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

/* Get random number */
double TestWorld::computeFitness (const GEP::System::Individual& individual) const
{
  double fitness = 0.0;

  for (int i=0; i < individual.getSize (); ++i)
    fitness += (i + 1) * individual[i];

  return fmod (fitness, 100.0);
}


//#**************************************************************************
// CLASS TestMain
//#**************************************************************************

/* Constructor */
TestMain::TestMain ()
{
}


QTEST_MAIN (TestMain);
