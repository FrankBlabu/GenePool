/*
 * test_main.cpp - Main file for test cases
 *
 * Frank Cieslok, Aug. 2011
 */

#include <QtCore/QString>
#include <QtTest/QtTest>

#include "TestMain.h"

//#**************************************************************************
// Configuration
//#**************************************************************************

namespace {
const uint NUMBER_OF_INDIVIDUALS = 10;
const uint INDIVIDUAL_SIZE = 10;
}

//#**************************************************************************
// CLASS ShuffleComparator
//#**************************************************************************

/*
 * Comparator class for shuffling a sequence
 */
class ShuffleComparator
{
public:
  ShuffleComparator (GEP::System::RandomNumberGeneratorPtr random_number_generator, uint size);

  bool operator () (uint value1, uint value2) const;

private:
  QMap<uint, double> _order;
};

/* Constructor */
ShuffleComparator::ShuffleComparator (GEP::System::RandomNumberGeneratorPtr random_number_generator, uint size)
{
  for (uint i=0; i < size; ++i)
    _order.insert (i, random_number_generator->generate ());
}

/* Compare operator */
bool ShuffleComparator::operator () (uint value1, uint value2) const
{
  Q_ASSERT (value1 < static_cast<uint> (_order.size ()));
  Q_ASSERT (value2 < static_cast<uint> (_order.size ()));

  return _order[value1] < _order[value2];
}

//#**************************************************************************
// CLASS TestMain
//#**************************************************************************

/* Constructor */
TestMain::TestMain ()
  : _random_number_generator (new GEP::System::MersenneTwisterRandomNumberGenerator ())
{
}

/* Generate test population */
TestPopulation TestMain::generatePopulation ()
{
  TestPopulation population;

  for (uint i=0; i < NUMBER_OF_INDIVIDUALS; ++i)
    {
      std::vector<uint> genes;
      for (uint j=0; j < INDIVIDUAL_SIZE; ++j)
        genes.push_back (j);

      std::sort (genes.begin (), genes.end (), ShuffleComparator (_random_number_generator, genes.size ()));

      population.add (TestIndividual (genes));
    }

  return population;
}


QTEST_MAIN (TestMain);
