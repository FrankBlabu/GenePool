/*
 * GEPTravelingIndividual.h - Single individual for the traveling salesman problem
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_TRAVELING_INDIVIDUAL_H__
#define __GEP_TRAVELING_INDIVIDUAL_H__

#include <GEPSystemIndividual.h>

namespace GEP {

/*
 * Single individual for the traveling salesman problem
 */
class TravelingIndividual : public System::Individual
{
public:
    TravelingIndividual ();
    virtual ~TravelingIndividual ();

    virtual void compute ();
};

}

#endif
