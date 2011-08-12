/*
 * GEPSystemRandomNumberGenerator.h - Random number generators
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_RANDOM_NUMBER_GENERATOR_H__
#define __GEP_SYSTEM_RANDOM_NUMBER_GENERATOR_H__

#include <boost/shared_ptr.hpp>

namespace GEP {
namespace System {

/*
 * Base class for random number generators
 */
class RandomNumberGenerator
{
public:
    RandomNumberGenerator ();
    virtual ~RandomNumberGenerator ();

    virtual double generate () = 0;
};

typedef boost::shared_ptr<RandomNumberGenerator> RandomNumberGeneratorPtr;

/*
 * Simple non-deterministic random number generator
 */
class MersenneTwisterRandomNumberGeneratorImp;

class MersenneTwisterRandomNumberGenerator : public RandomNumberGenerator
{
public:
    MersenneTwisterRandomNumberGenerator ();
    virtual ~MersenneTwisterRandomNumberGenerator ();

    virtual double generate ();

private:
    MersenneTwisterRandomNumberGeneratorImp* _imp;
};

}
}

#endif
