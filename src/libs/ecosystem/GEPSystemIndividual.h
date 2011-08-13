/*
 * GEPSystemIndividual.h - Base class for single individuals
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_INDIVIDUAL_H__
#define __GEP_SYSTEM_INDIVIDUAL_H__

#include <QtGlobal>
#include <QtCore/QList>

#include <boost/shared_ptr.hpp>

namespace GEP {
namespace System {


/*
 * Base class for single individuals
 */
template <class T>
class Individual
{
public:
    Individual ();
    Individual (const Individual<T>& toCopy);

    double getFitness () const;

    T& operator[] (uint index);
    const T& operator[] (uint index) const;

protected:
    QList<T> _genes;
};


/* Constructor */
template <class T>
Individual<T>::Individual ()
  : _genes ()
{
}

/* Copy constructor */
template <class T>
Individual<T>::Individual (const Individual<T>& toCopy)
  : _genes (toCopy._genes)
{
}

/* Return the current fitness of this individual */
template <class T>
double Individual<T>::getFitness () const
{
  qFatal ("Fitness function not implemented");
  return 0.0;
}

/* Access operator */
template <class T>
T& Individual<T>::operator[] (uint index)
{
  Q_ASSERT (index < _genes.size ());
  return _genes[index];
}

/* Access operator */
template <class T>
const T& Individual<T>::operator[] (uint index) const
{
  Q_ASSERT (index < _genes.size ());
  return _genes[index];
}

}
}

#endif
