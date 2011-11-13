/*
 * GEPSystemWorld.h - World information
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_WORLD_H__
#define __GEP_SYSTEM_WORLD_H__

namespace GEP {
namespace System {

class Individual;
class Population;

/*
 * World information
 */
class World
{
public:
  World ();
  virtual ~World ();

  virtual void generateWorld () = 0;
  virtual Population generatePopulation () = 0;

  virtual double computeFitness (const Individual& individual) const = 0;
};



}
}

#endif

