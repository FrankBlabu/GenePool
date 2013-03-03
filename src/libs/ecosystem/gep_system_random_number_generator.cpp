/*
 * gep_system_random_number_generator.cpp - Random number generator
 *
 * Frank Cieslok, Sep. 2011
 */

#include "GEPSystemRandomNumberGenerator.h"

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_real.hpp>

#include <QtCore/QTime>

namespace GEP {
namespace System {

//#**************************************************************************
// CLASS GEP::System::RandomNumberGeneratorImpl
//#**************************************************************************

class RandomNumberGeneratorImpl
{
public:
  RandomNumberGeneratorImpl ();

  double generate ();

private:
  boost::mt19937 _generator;
  boost::variate_generator<boost::mt19937&, boost::uniform_real<> > _die;
};


/* Constructor */
RandomNumberGeneratorImpl::RandomNumberGeneratorImpl ()
 : _generator (),
   _die       (_generator, boost::uniform_real<> (0.0, 1.0))
{
  _generator.seed (static_cast<uint> (QTime::currentTime ().msec ()));
}

/* Generate new random number in interval [0:1[ */
double RandomNumberGeneratorImpl::generate ()
{
  return _die ();
}



//#**************************************************************************
// CLASS GEP::System::RandomNumberGenerator
//#**************************************************************************

/* Constructor */
RandomNumberGenerator::RandomNumberGenerator ()
  : _impl (new RandomNumberGeneratorImpl ())
{
}

/* Generate new random number in interval [0:1] */
double RandomNumberGenerator::generate ()
{
  return _impl->generate ();
}

}
}
