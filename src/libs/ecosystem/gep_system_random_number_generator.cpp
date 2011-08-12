/*
 * gep_system_random_number_generator.cpp - Random number generators
 *
 * Frank Cieslok, Aug. 2011
 */

#include "GEPSystemRandomNumberGenerator.h"

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

/* Constructor */
RandomNumberGenerator::RandomNumberGenerator ()
{
}

/* Destructor */
RandomNumberGenerator::~RandomNumberGenerator ()
{
}

//#**************************************************************************
// CLASS GEP::System::MersenneTwisterRandomNumberGeneratorImp
//#**************************************************************************

class MersenneTwisterRandomNumberGeneratorImp
{
public:
  MersenneTwisterRandomNumberGeneratorImp ();

  double generate ();

private:
  boost::mt19937 _generator;
  boost::variate_generator<boost::mt19937&, boost::uniform_real<> > _die;
};


/* Constructor */
MersenneTwisterRandomNumberGeneratorImp::MersenneTwisterRandomNumberGeneratorImp ()
 : _generator (),
   _die       (_generator, boost::uniform_real<> (0.0, 1.0))
{
  struct timeval tv;
  gettimeofday (&tv, 0);

  _generator.seed (static_cast<uint> (tv.tv_usec));
}

/* Generate new random number in interval [0:1] */
double MersenneTwisterRandomNumberGeneratorImp::generate ()
{
  return _die ();
}


//#**************************************************************************
// CLASS GEP::System::MersenneTwisterRandomNumberGenerator
//#**************************************************************************

/* Constructor */
MersenneTwisterRandomNumberGenerator::MersenneTwisterRandomNumberGenerator ()
: _imp (new MersenneTwisterRandomNumberGeneratorImp ())
{
}

/* Destructor */
MersenneTwisterRandomNumberGenerator::~MersenneTwisterRandomNumberGenerator ()
{
  delete _imp;
  _imp = 0;
}

/* Generate new random number in interval [0:1] */
double MersenneTwisterRandomNumberGenerator::generate ()
{
  return _imp->generate ();
}

}
}
