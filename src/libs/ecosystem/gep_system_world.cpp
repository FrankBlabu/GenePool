/*
 * gep_system_world.cpp - World information
 *
 * Frank Cieslok, Aug. 2011
 */

#include "GEPSystemWorld.h"

#include <sys/time.h>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_real.hpp>

namespace GEP {
namespace System {

//#**************************************************************************
// CLASS GEP::System::RandomNumberGenerator
//#**************************************************************************

/* Random number generator */
class RandomNumberGenerator
{
public:
  RandomNumberGenerator ();

  double generate ();

private:
  boost::mt19937 _generator;
  boost::variate_generator<boost::mt19937&, boost::uniform_real<> > _die;
};


/* Constructor */
RandomNumberGenerator::RandomNumberGenerator ()
 : _generator (),
   _die       (_generator, boost::uniform_real<> (0.0, 1.0))
{
  struct timeval tv;
  gettimeofday (&tv, 0);

  _generator.seed (static_cast<uint> (tv.tv_usec));
}

/* Generate new random number in interval [0:1] */
double RandomNumberGenerator::generate ()
{
  return _die ();
}


//#**************************************************************************
// CLASS GEP::System::WorldBase
//#**************************************************************************

/* Constructor */
WorldBase::WorldBase ()
  : _random_number_generator (new RandomNumberGenerator ())
{
}

/* Destructor */
WorldBase::~WorldBase ()
{
  delete _random_number_generator;
  _random_number_generator = 0;
}

/* Generate random number in interval [0:1] */
double WorldBase::getRandom ()
{
  return _random_number_generator->generate ();
}

//#**************************************************************************
// CLASS GEP::System::World
//#**************************************************************************

}
}
