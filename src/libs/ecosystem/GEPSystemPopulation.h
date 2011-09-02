/*
 * GEPSystemPopulation.h - Population container
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_POPULATION_H__
#define __GEP_SYSTEM_POPULATION_H__

#include "GEPSystemIndividual.h"

#include <QtCore/QList>

namespace GEP {
namespace System {

/*
 * Population container
 */
class Population
{
public:
    Population ();
    Population (const Population& toCopy);

    void add (const Individual& individual);

    typedef QList<Individual>::const_iterator ConstIterator;

    inline ConstIterator begin () const { return _individuals.begin (); }
    inline ConstIterator end () const { return _individuals.end (); }

    inline uint getSize () const { return _individuals.size (); }

    Individual& operator[] (uint index);
    const Individual& operator[] (uint index) const;

private:
    QList<Individual> _individuals;
};

}
}

#endif
