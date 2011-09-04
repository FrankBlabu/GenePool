/*
 * gep_system_object.cpp - Base class for all objects
 *
 * Frank Cieslok, Aug. 2011
 */

#include "GEPSystemObject.h"
#include <limits>

namespace GEP {
namespace System {

//#**************************************************************************
// CLASS GEP::System::Object
//#**************************************************************************

/* Counter for unique object ids [STATIC] */
Object::Id Object::_id_counter = 0;
QMutex Object::_id_counter_lock;

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
  QMutexLocker locker (&_id_counter_lock);
  _id = _id_counter++;
 }

}
}
