/*
 * GEPSystemObject.h - Base class for all objects
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_OBJECT_H__
#define __GEP_SYSTEM_OBJECT_H__

#include <QtGlobal>
#include <QtCore/QAtomicInt>

namespace GEP {
namespace System {

/*
 * Base class for all objects
 */
class Object
{
public:
  Object ();
  Object (const Object& toCopy);

  typedef quint64 Id;
  inline Id getId () const { return _id; }

  void computeUniqueId ();

private:
  Id _id;

  static QAtomicInt _id_counter;
};

}
}

#endif
