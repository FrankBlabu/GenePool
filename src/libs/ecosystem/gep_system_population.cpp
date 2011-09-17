/*
 * gep_system_population.cpp - Population container
 *
 * Frank Cieslok, Aug. 2011
 */

#include "GEPSystemPopulation.h"
#include "GEPSystemNotifier.h"


namespace GEP {
namespace System {

//#**************************************************************************
// CLASS GEP::System::Population
//#**************************************************************************

/* Constructor */
Population::Population ()
  : _individuals (),
    _index_map   ()
{
}

/* Copy constructor */
Population::Population (const Population& toCopy)
  : _individuals (toCopy._individuals),
    _index_map   (toCopy._index_map)
{
}

/* Add individual to population */
void Population::add (const Individual& individual)
{
  _individuals.append (individual);
  _index_map.insert (individual.getId (), _individuals.size () - 1);

  System::Notifier::getNotifier ()->notifyIndividualCreated (individual);
}

/* Access operator */
Individual& Population::operator[] (int index)
{
  Q_ASSERT (index < _individuals.size ());
  return _individuals[index];
}

/* Access operator */
const Individual& Population::operator[] (int index) const
{
  Q_ASSERT (index < _individuals.size ());
  return _individuals[index];
}

/* Access operator */
Individual& Population::operator[] (const Object::Id& id)
{
  IndexMap::const_iterator pos = _index_map.find (id);
  Q_ASSERT (pos != _index_map.end ());
  return _individuals[pos.value ()];
}


/* Access operator */
const Individual& Population::operator[] (const Object::Id& id) const
{
  IndexMap::const_iterator pos = _index_map.find (id);
  Q_ASSERT (pos != _index_map.end ());
  return _individuals[pos.value ()];
}


}
}
