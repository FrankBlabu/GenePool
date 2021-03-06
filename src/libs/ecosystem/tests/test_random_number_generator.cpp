/*
 * test_random_number_generator.cpp - Test for the random number generators
 *
 * Frank Cieslok, Aug. 2011
 */

#include <iostream>
#include <QtTest/QtTest>

#include <GEPSystemRandomNumberGenerator.h>

class TestRandomNumberGenerator: public QObject
{
  Q_OBJECT

private slots:
  void testMersenneTwisterRandomNumberGenerator ();
};

void TestRandomNumberGenerator::testMersenneTwisterRandomNumberGenerator ()
{
  GEP::System::MersenneTwisterRandomNumberGenerator generator;

  static const uint NUMBER_OF_RUNS = 1000000;

  QBENCHMARK
  {
    double sum = 0.0;

    for (uint i=0; i < NUMBER_OF_RUNS; ++i)
      {
        double n = generator.generate ();

        Q_ASSERT (n >= 0.0);
        Q_ASSERT (n <= 1.0);

        sum += n;
      }

    sum /= NUMBER_OF_RUNS;

    Q_ASSERT (sum > 0.0);
    Q_ASSERT (sum < 1.0);
  }
}

QTEST_MAIN (TestRandomNumberGenerator)
#include "test_random_number_generator.moc"
