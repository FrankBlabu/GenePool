/*
 * GEPSystemPopulation.h - Population container
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_POPULATION_H__
#define __GEP_SYSTEM_POPULATION_H__

#include "GEPSystemIndividual.h"

#include <QList>
#include <boost/shared_ptr.hpp>

namespace GEP {
namespace System {

/*
 * Population container
 */
class Population
{
public:
    Population ();
    ~Population ();

    void compute ();

    void add (IndividualPtr individual);

private:
    void computeFitness (IndividualPtr individual);

private:
    QList<IndividualPtr> _individuals;
};

typedef boost::shared_ptr<Population> PopulationPtr;

}
}

#endif
