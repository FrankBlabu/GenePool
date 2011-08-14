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
    Individual (const QList<T>& genes);
    Individual (const Individual<T>& toCopy);

    uint getNumberOfGenes () const;

    T& operator[] (uint index);
    const T& operator[] (uint index) const;

protected:
    QList<T> _genes;
};


/* Constructor */
template <class T>
Individual<T>::Individual (const QList<T>& genes)
  : _genes (genes)
{
}

/* Copy constructor */
template <class T>
Individual<T>::Individual (const Individual<T>& toCopy)
  : _genes (toCopy._genes)
{
}

/* Return number of genes in this individual */
template <class T>
uint Individual<T>::getNumberOfGenes () const
{
  return _genes.size ();
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
  Q_ASSERT (index < static_cast<uint> (_genes.size ()));
  return _genes[index];
}

}
}

#endif
