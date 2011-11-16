/*
 * gep_traveling_world.cpp - The world of the traveling salesman
 *
 * Frank Cieslok, Sep. 2011
 */

#include <GEPSystemRandomNumberGenerator.h>
#include <GEPSystemPopulation.h>
#include <GEPSystemShuffleComparator.h>

#include "GEPTravelingWorld.h"

#include <algorithm>

namespace GEP {
namespace Traveling {


//#**************************************************************************
// CLASS GEP::Traveling::World
//#**************************************************************************

/* Constructor */
World::World ()
  : GEP::System::World (),
    _number_of_cities (0),
    _population_size  (0),
    _cities           ()
{
}

/* Gets the number of cities */
int World::getNumberOfCities () const
{
  return _number_of_cities;
}

/* Sets the number of cities */
void World::setNumberOfCities (int number_of_cities)
{
  _number_of_cities = number_of_cities;
}

/* Gets the population size */
int World::getPopulationSize () const
{
  return _population_size;
}

/* Sets the population size */
void World::setPopulationSize (int population_size)
{
  _population_size = population_size;
}

/* Generate world */
void World::generateWorld ()
{
  Q_ASSERT (_number_of_cities > 0);
  Q_ASSERT (_population_size > 0);

  System::RandomNumberGenerator random_number_generator;

  //
  // Clear current world
  //
  _cities.clear ();

  //
  // Randomly place cities
  //
  for (int i=0; i < _number_of_cities; ++i)
    _cities.append (QPointF (random_number_generator.generate (), random_number_generator.generate ()));
}

/* Generate random world population */
GEP::System::Population World::generatePopulation ()
{
  Q_ASSERT (_number_of_cities > 0);
  Q_ASSERT (_population_size > 0);
  Q_ASSERT (!_cities.empty ());

  GEP::System::Population population;

  GEP::System::Individual::Chromosome chromosome;
  for (int i=0; i < _number_of_cities; ++i)
    chromosome.append (i);

  for (int i=0; i < _population_size; ++i)
    {
      GEP::System::ShuffleComparator<GEP::System::Individual::Gene> comparator (chromosome);
      qSort (chromosome.begin (), chromosome.end (), comparator);
      population.add (GEP::Traveling::Individual (chromosome));
    }

  return population;
}

/* Return number of cities */
int World::getSize () const
{
  Q_ASSERT (!_cities.empty ());
  return _cities.size ();
}

/* Return city coordinate */
const QPointF& World::operator[] (int index) const
{
  Q_ASSERT (!_cities.empty ());
  Q_ASSERT (index >= 0 && index < _cities.size ());

  return _cities[index];
}

/* Get the directory type of the fitness value */
World::FitnessType_t World::getFitnessType () const
{
  return FitnessType::HIGHER_IS_WORSE;
}

/* Compute fitness of a single individual */
double World::computeFitness (const Individual& individual) const
{
  Q_ASSERT (!_cities.empty ());

  double distance = 0.0;

  for (int i=0; i + 1 < individual.getNumberOfGenes (); ++i)
    distance += getDistance (individual[i], individual[i + 1]);

  return distance;
}

/* Compute distance between two cities */
double World::getDistance (int city1, int city2) const
{
  Q_ASSERT (!_cities.empty ());
  Q_ASSERT (city1 >= 0 && city1 < _cities.size ());
  Q_ASSERT (city2 >= 0 && city2 < _cities.size ());

  return (_cities[city2] - _cities[city1]).manhattanLength ();
}


}
}


