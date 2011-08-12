/*
 * GEPSystemIndividual.h - Base class for single individuals
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_INDIVIDUAL_H__
#define __GEP_SYSTEM_INDIVIDUAL_H__

#include <boost/shared_ptr.hpp>

namespace GEP {
namespace System {

/*
 * Base class for single individuals
 */
class Individual
{
public:
    Individual ();
    virtual ~Individual ();

    double getFitness () const;

    virtual void compute () = 0;

protected:
    double _fitness;
};

typedef boost::shared_ptr<Individual> IndividualPtr;

}
}

#endif
