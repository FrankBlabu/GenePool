/*
 * GEPSystemOperator.h - Base class for all operator classes
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_OPERATOR_H__
#define __GEP_SYSTEM_OPERATOR_H__

#include "GEPSystemRandomNumberGenerator.h"

namespace GEP {
namespace System {

/*
 * Base class for all operator classes
 */
class Operator
{
public:
    Operator ();
    virtual ~Operator ();

    void setRandomNumberGenerator (RandomNumberGeneratorPtr random_number_generator);

protected:
    double getRandom () const;

private:
    RandomNumberGeneratorPtr _random_number_generator;
};

}
}

#endif

