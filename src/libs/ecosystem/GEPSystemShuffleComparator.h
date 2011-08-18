/*
 * GEPSystemShuffleComparator.h - Comparator class for sort-shuffling
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_SHUFFLE_COMPARATOR_H__
#define __GEP_SYSTEM_SHUFFLE_COMPARATOR_H__

#include "GEPSystemWorld.h"

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
  ShuffleComparator (World<T>* world);

  bool operator () (T object1, T object2);

private:
  double getOrder (T object);

private:
  World<T>* _world;

  typedef std::map<T, double> OrderMap;
  OrderMap _order_map;
};

/* Constructor */
template <class T>
ShuffleComparator<T>::ShuffleComparator (World<T>* world)
  : _world (world)
{
}

/* Comparison operator */
template <class T>
bool ShuffleComparator<T>::operator () (T object1, T object2)
{
  return getOrder (object1) < getOrder (object2);
}

/* Return order of the given object */
template <class T>
double ShuffleComparator<T>::getOrder (T object)
{
  double order = 0.0;

  typename OrderMap::const_iterator pos = _order_map.find (object);
  if (pos == _order_map.end ())
    {
      order = _world->getRandom ();
      _order_map.insert (std::make_pair (object, order));
    }
  else
    order = pos->second;

  return order;
}

}
}

#endif
