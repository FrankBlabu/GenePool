/*
 * gep_system_shuffle_comparator.cpp - Comparator class for sort-shuffling
 *
 * Frank Cieslok, Aug. 2011
 */

#include "GEPSystemShuffleComparator.h"

#include <QDebug>

namespace GEP {
namespace System {

//#**************************************************************************
// CLASS GEP::System::ShuffleComparator
//#**************************************************************************

/* Constructor */
ShuffleComparator::ShuffleComparator (World* world)
  : _world (world)
{
}

/* Comparison operator */
bool ShuffleComparator::operator () (const QVariant& object1, const QVariant& object2)
{
  return getOrder (object1) < getOrder (object2);
}

/* Return order of the given object */
double ShuffleComparator::getOrder (const QVariant& object)
{
  double order = 0.0;

  OrderMap::const_iterator pos = _order_map.find (object);
  if (pos == _order_map.end ())
    {
      order = _world->getRandom ();
      _order_map.insert (object, order);
    }
  else
    order = pos.value ();

  return order;
}

}
}
