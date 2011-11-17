/*
 * GEPSystemPopulation.h - Population container
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_POPULATION_H__
#define __GEP_SYSTEM_POPULATION_H__

#include "GEPSystemIndividual.h"

#include <QtCore/QList>
#include <QtCore/QMap>

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
    typedef QList<Individual>::iterator Iterator;

    inline Iterator begin () { return _individuals.begin (); }
    inline Iterator end () { return _individuals.end (); }
    inline ConstIterator begin () const { return _individuals.begin (); }
    inline ConstIterator end () const { return _individuals.end (); }

    inline int getSize () const { return _individuals.size (); }

    Individual& operator[] (int index);
    const Individual& operator[] (int index) const;

    Individual& operator[] (const Object::Id& id);
    const Individual& operator[] (const Object::Id& id) const;

private:
    QList<Individual> _individuals;

    typedef QMap<Object::Id, int> IndexMap;
    IndexMap _index_map;
};

}
}

#endif
