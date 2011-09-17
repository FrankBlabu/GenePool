/*
 * gep_system_world.cpp - World information
 *
 * Frank Cieslok, Aug. 2011
 */

#include "GEPSystemWorld.h"
#include "GEPSystemIndividual.h"

//#**************************************************************************
// Global functions
//#**************************************************************************

uint qHash (const QVariant& data)
{
  uint hash = 0;

  //
  // Standard data types. Missing: Mechanism for generic data types.
  //
  if (data.type () == QVariant::UInt)
    hash = data.toUInt ();
  else if (data.type () == QVariant::Int)
    hash = data.toInt ();
  else
    Q_ASSERT (false && "Unknown variant data typo");

  return hash;
}

QString convertToString (const QVariant& data)
{
  QString s;

  //
  // Standard data types. Missing: Mechanism for generic data types.
  //
  if (data.type () == QVariant::UInt)
    s = QString::number (data.toUInt ());
  else if (data.type () == QVariant::Int)
    s = QString::number (data.toInt ());
  else
    Q_ASSERT (false && "Unknown variant data typo");

  return s;
}

namespace GEP {
namespace System {


//#**************************************************************************
// CLASS GEP::System::World
//#**************************************************************************

/* Constructor */
World::World ()
{
}

/* Destructor */
World::~World ()
{
}


}
}
