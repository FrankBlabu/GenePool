/*
 * TestMain.cpp - Main file for test cases
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __TEST_MAIN_H__
#define __TEST_MAIN_H__

#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtTest/QtTest>

#include <GEPSystemIndividual.h>
#include <GEPSystemPopulation.h>
#include <GEPSystemFitnessOperator.h>


/*
 * World information
 */
class TestWorld : public GEP::System::World
{
public:
    TestWorld ();
    virtual ~TestWorld ();

    virtual double getFitness (const GEP::System::Individual& individual) const;
};

/*
 * Main test class
 */
class TestMain : public QObject
{
    Q_OBJECT

public:
    TestMain ();

private:
    GEP::System::Population generatePopulation (GEP::System::World* world, int population_size, int individual_size);

private slots:
    void testShuffleComparator ();
    void testRandomNumberGenerator ();
    void testSelectionOperator ();
    void testPopulationFitnessIndex ();
    void testCrossoverOperator ();
    void testMutationOperator ();
};

#endif
