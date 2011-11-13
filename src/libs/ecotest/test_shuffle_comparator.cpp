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
  GEP::System::Individual::Chromosome chromosome;
  int reference_sum = 0;

  for (int i=0; i < 100; ++i)
    {
      chromosome.append (i);
      reference_sum += i;
    }

  GEP::System::ShuffleComparator<GEP::System::Individual::Gene> comparator (chromosome);
  qSort (chromosome.begin (), chromosome.end (), comparator);

  int sorted_sum = 0;

  for (int i=0; i < chromosome.size (); ++i)
    sorted_sum += chromosome[i];

  Q_ASSERT (reference_sum = sorted_sum);
}
