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

  struct FitnessType { enum Type_t { HIGHER_IS_BETTER, HIGHER_IS_WORSE }; };
  typedef FitnessType::Type_t FitnessType_t;

  virtual int getNumberOfFitnessValues () const = 0;
  virtual FitnessType_t getFitnessType (int index) const = 0;
  virtual double getFitnessWeight (int index) const = 0;
  virtual double computeFitness (int index, const Individual& individual) const = 0;
};



}
}

#endif

