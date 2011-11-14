/*
 * GEPSystemOperator.h - Base class for all operator classes
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_OPERATOR_H__
#define __GEP_SYSTEM_OPERATOR_H__

#include "GEPSystemWorld.h"

#include <QtCore/QSharedPointer>

namespace GEP {
namespace System {

/*
 * Base class for all operator classes
 */
class Operator
{
public:
    Operator (World* world);

protected:
    World* getWorld () const;

protected:
    World* _world;
};

}
}

#endif

