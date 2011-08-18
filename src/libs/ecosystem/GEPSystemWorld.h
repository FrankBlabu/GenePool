/*
 * GEPSystemWorld.h - World information
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_WORLD_H__
#define __GEP_SYSTEM_WORLD_H__

#include "GEPSystemIndividual.h"

namespace GEP {
namespace System {

/*
 * World information
 */
class RandomNumberGenerator;

class WorldBase
{
public:
  WorldBase ();
  virtual ~WorldBase ();

  double getRandom ();

private:
  RandomNumberGenerator* _random_number_generator;
};

template <class T>
class World : public WorldBase
{
public:
    World ();
    virtual ~World ();

    virtual double getFitness (const Individual<T>& individual) = 0;
};


/* Constructor */
template <class T>
World<T>::World ()
{

}

/* Destructor */
template <class T>
World<T>::~World ()
{
}


}
}

#endif

