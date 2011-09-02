/*
 * TestMain.cpp - Main file for test cases
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __TEST_MAIN_H__
#define __TEST_MAIN_H__

#include <QtCore/QObject>
#include <QtTest/QtTest>

#include <GEPSystemIndividual.h>
#include <GEPSystemPopulation.h>
#include <GEPSystemFitnessOperator.h>

/*
 * Fitness operator for a random fitness
 */
class RandomFitnessOperator : public GEP::System::FitnessOperator
{
public:
    RandomFitnessOperator (GEP::System::World* world, const GEP::System::Population& population);
    virtual ~RandomFitnessOperator ();

    virtual double compute (const GEP::System::Individual& individual) const;

private:
    typedef std::map<GEP::System::Object::Id, double> FitnessMap;
    FitnessMap _fitness_map;
};

/*
 * World information
 */
class TestWorld : public GEP::System::World
{
public:
    TestWorld ();
    virtual ~TestWorld ();

    virtual double getFitness (const GEP::System::Individual& individual);
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
    GEP::System::Population generatePopulation (GEP::System::World* world, uint population_size, uint individual_size);

private slots:
    void testShuffleComparator ();
    void testRandomNumberGenerator ();
    void testSelectionOperator ();
    void testPopulationFitnessIndex ();
    void testCrossoverOperator ();
    void testMutationOperator ();
};

#endif
