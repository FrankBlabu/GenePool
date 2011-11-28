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

#include <GEPSystemController.h>
#include <GEPSystemIndividual.h>
#include <GEPSystemPopulation.h>
#include <GEPSystemFitnessOperator.h>
#include <GEPSystemWorld.h>

/*
 * World information
 */
class TestWorld : public GEP::System::World
{
public:
    TestWorld (int population_size, int individual_size);
    virtual ~TestWorld ();

    virtual void generateWorld ();
    virtual GEP::System::Population generatePopulation ();

    virtual FitnessType_t getFitnessType () const;
    virtual double computeFitness (const GEP::System::Individual& individual) const;

    typedef QMap<GEP::System::Object::Id, double> FitnessMap;
    FitnessMap computeFitnessMap (const GEP::System::Population& population) const;

private:
    int _population_size;
    int _individual_size;
};

/*
 * Test controller
 */
class TestController : public GEP::System::SinglePopulationController
{
public:
  TestController (GEP::System::World* world);
  virtual ~TestController ();

  typedef QMap<GEP::System::Object::Id, double> FitnessMap;
  const FitnessMap& getFitnessMap () const;
};

/*
 * Main test class
 */
class TestMain : public QObject
{
    Q_OBJECT

public:
    TestMain ();

private slots:
    void testShuffleComparator ();
    void testRandomNumberGenerator ();
    void testSelectionOperator ();
    void testPopulationFitnessIndex ();
    void testCrossoverOperator ();
    void testMutationOperator ();
};

#endif
