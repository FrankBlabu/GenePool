/*
 * test_random_number_generator.cpp - Test for the random number generators
 *
 * Frank Cieslok, Aug. 2011
 */

#include "TestMain.h"

#include <GEPSystemWorld.h>

/*
 * Test random number generator
 */
void TestMain::testRandomNumberGenerator ()
{
  static const uint NUMBER_OF_RUNS = 1000000;

  QBENCHMARK
  {
    double sum = 0.0;

    TestWorld world;
    for (uint i=0; i < NUMBER_OF_RUNS; ++i)
      {
        double n = world.getRandom ();

        Q_ASSERT (n >= 0.0);
        Q_ASSERT (n <= 1.0);

        sum += n;
      }

    sum /= NUMBER_OF_RUNS;

    Q_ASSERT (sum > 0.0);
    Q_ASSERT (sum < 1.0);
  }
}
