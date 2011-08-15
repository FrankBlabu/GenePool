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

//#**************************************************************************
// CLASS GEP::System::Population
//#**************************************************************************

/*
 * Population container
 */
template<class T>
class Population
{
public:
    Population ();
    Population (const Population<T>& toCopy);

    void add (const Individual<T>& individual);

    typedef typename QList< Individual<T> >::const_iterator ConstIterator;

    inline ConstIterator begin () const { return _individuals.begin (); }
    inline ConstIterator end () const { return _individuals.end (); }

    inline uint getSize () const { return _individuals.size (); }

    Individual<T>& operator[] (uint index);
    const Individual<T>& operator[] (uint index) const;

private:
    QList< Individual<T> > _individuals;
};

/* Constructor */
template <class T>
Population<T>::Population ()
{
}

/* Copy constructor */
template <class T>
Population<T>::Population (const Population<T>& toCopy)
  : _individuals (toCopy._individuals)
{
}

/* Add individual to population */
template <class T>
void Population<T>::add (const Individual<T>& individual)
{
  _individuals.append (individual);
}

/* Access operator */
template <class T>
Individual<T>& Population<T>::operator[] (uint index)
{
  Q_ASSERT (index < _individuals.size ());
  return _individuals[index];
}

/* Access operator */
template <class T>
const Individual<T>& Population<T>::operator[] (uint index) const
{
  Q_ASSERT (index < static_cast<uint> (_individuals.size ()));
  return _individuals[index];
}


}
}

#endif
