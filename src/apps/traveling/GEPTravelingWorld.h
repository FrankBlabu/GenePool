/*
 * GEPTravelingWorld.h - The world of the traveling salesman
 *
 * Frank Cieslok, Sep. 2011
 */

#ifndef __GEP_TRAVELING_WORLD__H__
#define __GEP_TRAVELING_WORLD__H__

#include <GEPSystemWorld.h>
#include <GEPSystemIndividual.h>

#include <QtCore/QList>
#include <QtCore/QPointF>

namespace GEP {
namespace Traveling {

//#**************************************************************************
// CLASS GEP::Traveling::Individual
//#**************************************************************************

/*
 * Individual: Single path
 */
typedef GEP::System::Individual Individual;


//#**************************************************************************
// CLASS GEP::Traveling::World
//#**************************************************************************

/*
 * World of the traveling salesman
 */
class World : public GEP::System::World
{
public:
  World ();

  int getNumberOfCities () const;
  void setNumberOfCities (int number_of_cities);

  int getPopulationSize () const;
  void setPopulationSize (int population_size);

  int getSize () const;
  const QPointF& operator[] (int index) const;

  virtual void generateWorld ();
  virtual GEP::System::Population generatePopulation ();

  virtual FitnessType_t getFitnessType () const;
  virtual double computeFitness (const Individual& individual) const;

private:
  double getDistance (int city1, int city2) const;

private:
  int _number_of_cities;
  int _population_size;

  QList<QPointF> _cities;
  double _fitness_bias;
};

}
}

#endif
