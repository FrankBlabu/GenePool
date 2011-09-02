/*
 * GEPSystemShuffleComparator.h - Comparator class for sort-shuffling
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_SHUFFLE_COMPARATOR_H__
#define __GEP_SYSTEM_SHUFFLE_COMPARATOR_H__

#include "GEPSystemWorld.h"

#include <QtCore/QVariant>
#include <QtCore/QHash>

namespace GEP {
namespace System {

/*
 * Comparator class for sort-shuffling
 */
class ShuffleComparator
{
public:
  ShuffleComparator (World* world);

  bool operator () (const QVariant& object1, const QVariant& object2);

private:
  double getOrder (const QVariant& object);

private:
  World* _world;

  typedef QHash<QVariant, double> OrderMap;
  OrderMap _order_map;
};


}
}

#endif
