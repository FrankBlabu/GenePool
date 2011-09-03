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
  uint reference_sum = 0;

  for (uint i=0; i < 100; ++i)
    {
      sequence.push_back (QVariant (i));
      reference_sum += i;
    }

  GEP::System::ShuffleComparator<QVariant> comparator (&world, sequence);
  std::sort (sequence.begin (), sequence.end (), comparator);

  uint sorted_sum = 0;

  for (uint i=0; i < sequence.size (); ++i)
    {
      Q_ASSERT (sequence[i].type () == QVariant::UInt);
      sorted_sum += sequence[i].toUInt ();
    }

  Q_ASSERT (reference_sum = sorted_sum);
}
