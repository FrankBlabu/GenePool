/*
 * gep_system_world.cpp - World information
 *
 * Frank Cieslok, Aug. 2011
 */

#include "GEPSystemWorld.h"
#include "GEPSystemIndividual.h"
#include "GEPSystemNotifier.h"

#include <stdlib.h>
#include <sys/time.h>

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
// CLASS GEP::System::RandomNumberGenerator
//#**************************************************************************


/* Random number generator */
class RandomNumberGenerator
{
public:
  RandomNumberGenerator ();

  double generate ();
};


/* Constructor */
RandomNumberGenerator::RandomNumberGenerator ()
{
  struct timeval tv;
  gettimeofday (&tv, 0);

  unsigned short seeds[3];
  seeds[0] = tv.tv_usec;
  seeds[1] = tv.tv_usec;
  seeds[2] = tv.tv_sec;

  seed48 (seeds);
}

/* Generate new random number in interval [0:1] */
double RandomNumberGenerator::generate ()
{
  return drand48 ();
}

//#**************************************************************************
// CLASS GEP::System::World
//#**************************************************************************

/* Constructor */
World::World ()
  : _notifier                (new Notifier ()),
    _random_number_generator (new RandomNumberGenerator ())
{
}

/* Destructor */
World::~World ()
{
  delete _random_number_generator;
  _random_number_generator = 0;

  delete _notifier;
  _notifier = 0;
}

/* Generate random number in interval [0:1] */
double World::getRandom ()
{
  return _random_number_generator->generate ();
}

/* Return world notifier */
Notifier* World::getNotifier () const
{
  return _notifier;
}

}
}
