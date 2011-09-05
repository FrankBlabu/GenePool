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
  World (uint number_of_cities);

  uint getSize () const;
  const QPointF& operator[] (int index) const;

  virtual double getFitness (const Individual& individual) const;

private:
  double getDistance (int city1, int city2) const;

private:
  QList<QPointF> _cities;
  double _fitness_bias;
};

}
}

#endif
