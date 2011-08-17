/*
 * GEPSystemOperator.h - Base class for all operator classes
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_OPERATOR_H__
#define __GEP_SYSTEM_OPERATOR_H__

#include "GEPSystemWorld.h"

namespace GEP {
namespace System {

/*
 * Base class for all operator classes
 */
template <class T>
class Operator
{
public:
    Operator (World<T>* world);

protected:
    World<T>* _world;
};

/* Constructor */
template <class T>
Operator<T>::Operator (World<T>* world)
  : _world (world)
{
}

}
}

#endif

