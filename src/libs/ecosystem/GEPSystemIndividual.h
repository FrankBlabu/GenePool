/*
 * GEPSystemIndividual.h - Base class for single individuals
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_INDIVIDUAL_H__
#define __GEP_SYSTEM_INDIVIDUAL_H__

#include "GEPSystemObject.h"

#include <limits>
#include <vector>

#include <QtGlobal>
#include <QtCore/QMutex>


namespace GEP {
namespace System {

//#**************************************************************************
// CLASS GEP::System::Individual
//#**************************************************************************

/*
 * Base class for single individuals
 */
template <class T>
class Individual : public Object
{
public:
    Individual (const std::vector<T>& genes);
    Individual (const Individual<T>& toCopy);

    uint getSize () const;

    T& operator[] (uint index);
    const T& operator[] (uint index) const;

protected:
    std::vector<T> _genes;
};

/* Constructor */
template <class T>
Individual<T>::Individual (const std::vector<T>& genes)
  : Object (),
    _genes (genes)
{
}

/* Copy constructor */
template <class T>
Individual<T>::Individual (const Individual<T>& toCopy)
  : Object (),
    _genes (toCopy._genes)
{
}

/* Return number of genes in this individual */
template <class T>
uint Individual<T>::getSize () const
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
