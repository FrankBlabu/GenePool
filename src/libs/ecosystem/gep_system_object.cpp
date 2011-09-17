/*
 * gep_system_object.cpp - Base class for all objects
 *
 * Frank Cieslok, Aug. 2011
 */

#include "GEPSystemObject.h"

#include <QtCore/QAtomicInt>
#include <limits>

namespace GEP {
namespace System {

//#**************************************************************************
// CLASS GEP::System::Object
//#**************************************************************************

/* Counter for unique object ids [STATIC] */
QAtomicInt Object::_id_counter = 0;

/* Value fpr invalid ids [STATIC] */
Object::Id Object::INVALID = std::numeric_limits<Id>::max ();

/* Constructor */
Object::Object ()
  : _id (std::numeric_limits<Id>::max ())
{
  computeUniqueId ();
}

/* Copy constructor */
Object::Object (const Object& toCopy)
  : _id (toCopy._id)
{
}

/* Compute unique id for this object */
void Object::computeUniqueId ()
{
  _id = _id_counter.fetchAndAddRelaxed (1);
 }

}
}
