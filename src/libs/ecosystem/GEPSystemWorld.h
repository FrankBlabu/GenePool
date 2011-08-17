/*
 * GEPSystemWorld.h - World information
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_WORLD_H__
#define __GEP_SYSTEM_WORLD_H__

#include "GEPSystemIndividual.h"
#include "GEPSystemRandomNumberGenerator.h"

namespace GEP {
namespace System {

/*
 * World information
 */
template <class T>
class World
{
public:
    World (RandomNumberGeneratorPtr random_number_generator);
    virtual ~World ();

    virtual double getFitness (const Individual<T>& individual) = 0;
    virtual double getRandom ();

private:
    RandomNumberGeneratorPtr _random_number_generator;
};


/* Constructor */
template <class T>
World<T>::World (RandomNumberGeneratorPtr random_number_generator)
  : _random_number_generator (random_number_generator)
{
}

/* Destructor */
template <class T>
World<T>::~World ()
{
}

/* Get random number */
template <class T>
double World<T>::getRandom ()
{
  return _random_number_generator->generate ();
}


}
}

#endif

