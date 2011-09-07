/*
 * GEPSystemShuffleComparator.h - Comparator class for sort-shuffling
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_SHUFFLE_COMPARATOR_H__
#define __GEP_SYSTEM_SHUFFLE_COMPARATOR_H__

#include "GEPSystemWorld.h"
#include "GEPSystemIndividual.h"

#include <QtCore/QHash>

namespace GEP {
namespace System {

/*
 * Comparator class for sort-shuffling
 */
template <class T>
class ShuffleComparator
{
public:
  ShuffleComparator (World* world, const std::vector<T>& values);

  bool operator () (const T& object1, const T& object2);

private:
  typedef QHash<T, double> OrderMap;
  OrderMap _order_map;
};

/* Constructor */
template <class T>
ShuffleComparator<T>::ShuffleComparator (World* world, const std::vector<T>& values)
{
  for (uint i=0; i < values.size (); ++i)
    _order_map.insert (values[i], world->getRandom ());
}

/* Comparison operator */
template <class T>
bool ShuffleComparator<T>::operator () (const T& object1, const T& object2)
{
  typename OrderMap::const_iterator i = _order_map.find (object1);
  Q_ASSERT (i != _order_map.end ());

  typename OrderMap::const_iterator j = _order_map.find (object2);
  Q_ASSERT (j != _order_map.end ());

  return i.value () < j.value ();
}


}
}

#endif
