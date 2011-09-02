/*
 * GEPSystemWorld.h - World information
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_WORLD_H__
#define __GEP_SYSTEM_WORLD_H__

#include "GEPSystemIndividual.h"

uint qHash (const QVariant& data);

namespace GEP {
namespace System {

/*
 * World information
 */
class RandomNumberGenerator;

class World
{
public:
  World ();
  virtual ~World ();

  virtual double getFitness (const Individual& individual) = 0;

  double getRandom ();

private:
  RandomNumberGenerator* _random_number_generator;
};



}
}

#endif

