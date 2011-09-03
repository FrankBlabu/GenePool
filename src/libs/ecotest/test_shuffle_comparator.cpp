/*
 * test_shuffle_comparator.cpp - Test for the shuffle comparator
 *
 * Frank Cieslok, Aug. 2011
 */

#include "TestMain.h"

#include <GEPSystemShuffleComparator.h>
#include <algorithm>

/*
 * Test shuffle comparator
 */
void TestMain::testShuffleComparator ()
{
  TestWorld world;

  std::vector<QVariant> sequence;
  for (uint i=0; i < 100; ++i)
    sequence.push_back (QVariant (i));

  GEP::System::ShuffleComparator<QVariant> comparator (&world, sequence);
  std::sort (sequence.begin (), sequence.end (), comparator);
}
