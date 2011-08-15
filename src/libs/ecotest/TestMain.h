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
#include <GEPSystemRandomNumberGenerator.h>

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
    RandomFitnessOperator (const GEP::System::Population<T>& population);
    virtual ~RandomFitnessOperator () {}

    virtual double compute (const GEP::System::Individual<T>& individual) const;

protected:
    virtual double getFitness (const GEP::System::Individual<T>& individual) const;

private:
    typedef std::map<GEP::System::Object::Id, double> FitnessMap;
    FitnessMap _fitness_map;
};

/* Constructor */
template<class T>
RandomFitnessOperator<T>::RandomFitnessOperator (const GEP::System::Population<T>& population)
{
  GEP::System::MersenneTwisterRandomNumberGenerator _random_number_generator;

  for (typename GEP::System::Population<T>::ConstIterator i = population.begin (); i != population.end (); ++i)
    {
      const GEP::System::Individual<T>& individual = *i;
      _fitness_map.insert (std::make_pair (individual.getId (), _random_number_generator.generate ()));
    }
}

/* Compute fitness for a single individual */
template <class T>
double RandomFitnessOperator<T>::compute (const GEP::System::Individual<T>& individual) const
{
  return getFitness (individual);
}

/* Return individuals fitness */
template <class T>
double RandomFitnessOperator<T>::getFitness (const GEP::System::Individual<T>& individual) const
{
  FitnessMap::const_iterator pos = _fitness_map.find (individual.getId ());
  Q_ASSERT (pos != _fitness_map.end ());

  return pos->second;
}


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
    TestPopulation generatePopulation ();

private slots:
    void testRandomNumberGenerator ();
    void testPopulationFitnessIndex ();
    void testSelectionOperator ();

private:
    boost::shared_ptr<GEP::System::RandomNumberGenerator> _random_number_generator;
};

#endif
