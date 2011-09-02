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
// CLASS RandomFitnessOperator
//#**************************************************************************

/* Constructor */
RandomFitnessOperator::RandomFitnessOperator (GEP::System::World* world, const GEP::System::Population& population)
  : GEP::System::FitnessOperator (world)
{
  for (GEP::System::Population::ConstIterator i = population.begin (); i != population.end (); ++i)
    {
      const GEP::System::Individual& individual = *i;
      _fitness_map.insert (std::make_pair (individual.getId (), _world->getRandom ()));
    }
}

/* Destructor */
RandomFitnessOperator::~RandomFitnessOperator ()
{
}

/* Compute fitness for a single individual */
double RandomFitnessOperator::compute (const GEP::System::Individual& individual) const
{
  FitnessMap::const_iterator pos = _fitness_map.find (individual.getId ());
  Q_ASSERT (pos != _fitness_map.end ());

  return pos->second;
}


//#**************************************************************************
// CLASS TestWorld
//#**************************************************************************

/* Constructor */
TestWorld::TestWorld ()
  : GEP::System::World ()
{
}

/* Destructor */
TestWorld::~TestWorld ()
{
}

/* Get random number */
double TestWorld::getFitness (const GEP::System::Individual& individual)
{
  Q_UNUSED (individual);

  return GEP::System::World::getRandom () * 100.0;
}


//#**************************************************************************
// CLASS TestMain
//#**************************************************************************

/* Constructor */
TestMain::TestMain ()
{
}

/* Generate test population */
GEP::System::Population TestMain::generatePopulation (GEP::System::World* world, uint population_size, uint individual_size)
{
  GEP::System::Population population;

  for (uint i=0; i < population_size; ++i)
    {
      std::vector<QVariant> genes;
      for (uint j=0; j < individual_size; ++j)
        genes.push_back (QVariant (j));

      std::sort (genes.begin (), genes.end (), GEP::System::ShuffleComparator (world));

      population.add (GEP::System::Individual (genes));
    }

  return population;
}


QTEST_MAIN (TestMain);
