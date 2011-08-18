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
 * Individual definition
 */
typedef GEP::System::Individual<uint> TestIndividual;
typedef GEP::System::Population<uint> TestPopulation;

//#**************************************************************************
// CLASS RandomFitnessOperator
//#**************************************************************************

/*
 * Fitness operator for a random fitness
 */
template <class T>
class RandomFitnessOperator : public GEP::System::FitnessOperator<T>
{
public:
    RandomFitnessOperator (GEP::System::World<T>* world, const GEP::System::Population<T>& population);
    virtual ~RandomFitnessOperator () {}

    virtual double compute (const GEP::System::Individual<T>& individual) const;

private:
    typedef std::map<GEP::System::Object::Id, double> FitnessMap;
    FitnessMap _fitness_map;
};

/* Constructor */
template<class T>
RandomFitnessOperator<T>::RandomFitnessOperator (GEP::System::World<T>* world, const GEP::System::Population<T>& population)
  : GEP::System::FitnessOperator<T> (world)
{
  for (typename GEP::System::Population<T>::ConstIterator i = population.begin (); i != population.end (); ++i)
    {
      const GEP::System::Individual<T>& individual = *i;
      _fitness_map.insert (std::make_pair (individual.getId (), GEP::System::Operator<T>::_world->getRandom ()));
    }
}

/* Compute fitness for a single individual */
template <class T>
double RandomFitnessOperator<T>::compute (const GEP::System::Individual<T>& individual) const
{
  FitnessMap::const_iterator pos = _fitness_map.find (individual.getId ());
  Q_ASSERT (pos != _fitness_map.end ());

  return pos->second;
}


//#**************************************************************************
// CLASS TestWorld
//#**************************************************************************

/*
 * World information
 */
class TestWorld : public GEP::System::World<uint>
{
public:
    TestWorld ();
    virtual ~TestWorld ();

    virtual double getFitness (const GEP::System::Individual<uint>& individual);
};

//#**************************************************************************
// CLASS TestMain
//#**************************************************************************

/*
 * Main test class
 */
class TestMain : public QObject
{
    Q_OBJECT

public:
    TestMain ();

private:
    TestPopulation generatePopulation (uint population_size, uint individual_size);

private slots:
    void testRandomNumberGenerator ();
    void testSelectionOperator ();
    void testPopulationFitnessIndex ();
    void testCrossoverOperator ();
    void testMutationOperator ();
};

#endif
