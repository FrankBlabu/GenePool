/*
 * GEPSystemShuffleComparator.h - Comparator class for sort-shuffling
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_SHUFFLE_COMPARATOR_H__
#define __GEP_SYSTEM_SHUFFLE_COMPARATOR_H__

#include "GEPSystemRandomNumberGenerator.h"

#include <map>

namespace GEP {
namespace System {

//#**************************************************************************
// CLASS GEP::System::ShuffleComparator
//#**************************************************************************

/*
 * Comparator class for sort-shuffling
 */
template <class T>
class ShuffleComparator
{
public:
  ShuffleComparator ();

  bool operator () (const T& object1, const T& object2) const;

private:
  double getOrder (const T& object) const;

private:
  mutable MersenneTwisterRandomNumberGenerator _random_number_generator;

  typedef std::map<T, double> OrderMap;
  mutable OrderMap _order_map;
};

/* Constructor */
template <class T>
ShuffleComparator<T>::ShuffleComparator ()
{
}

/* Comparison operator */
template <class T>
bool ShuffleComparator<T>::operator () (const T& object1, const T& object2) const
{
  return getOrder (object1) < getOrder (object2);
}

/* Return order of the given object */
template <class T>
double ShuffleComparator<T>::getOrder (const T& object) const
{
  double order = 0.0;

  typename OrderMap::const_iterator pos = _order_map.find (object);
  if (pos == _order_map.end ())
    {
      order = _random_number_generator.generate ();
      _order_map.insert (std::make_pair (object, order));
    }
  else
    order = pos->second;

  return order;
}

}
}

#endif
