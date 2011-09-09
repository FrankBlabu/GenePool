/*
 * gep_traveling_world.cpp - The world of the traveling salesman
 *
 * Frank Cieslok, Sep. 2011
 */

#include "GEPTravelingWorld.h"

namespace GEP {
namespace Traveling {


//#**************************************************************************
// CLASS GEP::Traveling::World
//#**************************************************************************

/* Constructor */
World::World (int number_of_cities)
  : GEP::System::World (),
    _fitness_bias (0.0)
{
  //
  // Randomly place cities
  //
  for (int i=0; i < number_of_cities; ++i)
    _cities.push_back (QPointF (getRandom (), getRandom ()));

  //
  // Compute largest city distance to get a fitness bias
  //
  double max_distance = 0.0;

  for (int i=0; i < _cities.size (); ++i)
    for (int j=i+1; j < _cities.size (); ++j)
      max_distance = std::max (max_distance, getDistance (i, j));

  _fitness_bias = _cities.size () * max_distance;

}

/* Return number of cities */
int World::getSize () const
{
  return _cities.size ();
}

/* Return city coordinate */
const QPointF& World::operator[] (int index) const
{
  Q_ASSERT (index < _cities.size ());
  return _cities[index];
}

/* Compute fitness of a single individual */
double World::getFitness (const Individual& individual) const
{
  double distance = 0.0;

  for (int i=0; i + 1 < individual.getSize (); ++i)
    distance += getDistance (individual[i].toInt (), individual[i + 1].toInt ());

  return _fitness_bias - distance;
}

/* Compute distance between two cities */
double World::getDistance (int city1, int city2) const
{
  return (_cities[city2] - _cities[city1]).manhattanLength ();
}


}
}


