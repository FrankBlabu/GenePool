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
class Population;

/*
 * World information
 */
class World
{
public:
  World ();
  virtual ~World ();

  virtual void generateWorld () = 0;
  virtual Population generatePopulation () = 0;

  virtual double getFitness (const Individual& individual) const = 0;
};



}
}

#endif

