/*
 * GEPSystemWorld.h - World information
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_WORLD_H__
#define __GEP_SYSTEM_WORLD_H__

#include <QtCore/QVariant>

uint qHash (const QVariant& data);
QString convertToString (const QVariant& data);

namespace GEP {
namespace System {

class Individual;
class Notifier;
class RandomNumberGenerator;

/*
 * World information
 */

class World
{
public:
  World ();
  virtual ~World ();

  virtual double getFitness (const Individual& individual) const = 0;

  double getRandom ();

  Notifier* getNotifier () const;

private:
  Notifier* _notifier;
  RandomNumberGenerator* _random_number_generator;
};



}
}

#endif

