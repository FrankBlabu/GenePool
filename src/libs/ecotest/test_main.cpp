/*
 * test_main.cpp - Main file for test cases
 *
 * Frank Cieslok, Aug. 2011
 */

#include "GEPSystemShuffleComparator.h"

#include <QtCore/QString>
#include <QtTest/QtTest>

#include "TestMain.h"


//#**************************************************************************
// CLASS TestWorld
//#**************************************************************************

/* Constructor */
TestWorld::TestWorld ()
  : GEP::System::World<uint> (GEP::System::RandomNumberGeneratorPtr (new GEP::System::MersenneTwisterRandomNumberGenerator))
{
}

/* Destructor */
TestWorld::~TestWorld ()
{
}

/* Get random number */
double TestWorld::getFitness (const GEP::System::Individual<uint>& individual)
{
  Q_UNUSED (individual);

  return GEP::System::World<uint>::getRandom () * 100.0;
}


//#**************************************************************************
// CLASS TestMain
//#**************************************************************************

/* Constructor */
TestMain::TestMain ()
{
}

/* Generate test population */
TestPopulation TestMain::generatePopulation (uint population_size, uint individual_size)
{
  TestPopulation population;

  for (uint i=0; i < population_size; ++i)
    {
      std::vector<uint> genes;
      for (uint j=0; j < individual_size; ++j)
        genes.push_back (j);

      std::sort (genes.begin (), genes.end (), GEP::System::ShuffleComparator<uint> ());

      population.add (TestIndividual (genes));
    }

  return population;
}


QTEST_MAIN (TestMain);
