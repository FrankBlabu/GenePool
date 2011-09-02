/*
 * gep_system_operator.cpp - Base class for all operator classes
 *
 * Frank Cieslok, Aug. 2011
 */

#include "GEPSystemOperator.h"

#include <QtGlobal>

namespace GEP {
namespace System {

//#**************************************************************************
// CLASS GEP::System::Operator
//#**************************************************************************

/* Constructor */
Operator::Operator (World* world)
  : _world (world)
{
}

}
}
