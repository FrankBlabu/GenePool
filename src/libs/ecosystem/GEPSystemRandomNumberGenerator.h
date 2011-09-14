/*
 * GEPSystemRandomNumberGenerator.h - Random number generator
 *
 * Frank Cieslok, Sep. 2011
 */

#ifndef __GEP_SYSTEM_RANDOM_NUMBER_GENERATOR_H__
#define __GEP_SYSTEM_RANDOM_NUMBER_GENERATOR_H__

namespace GEP {
namespace System {

class RandomNumberGeneratorImpl;

/*
 * Random number generator
 *
 * Generates random number in a uniform distribution between [0...1[
 */
class RandomNumberGenerator
{
public:
  RandomNumberGenerator ();

  double generate ();

private:
  RandomNumberGeneratorImpl* _impl;
};


}
}

#endif

