/*
 * gep_system_selection_operator.cpp - Base class for selection operators
 *
 * Frank Cieslok, Aug. 2011
 */

#include "GEPSystemSelectionOperator.h"
#include "GEPSystemNotifier.h"

namespace GEP {
namespace System {

//#**************************************************************************
// CLASS GEP::System::SelectionOperator
//#**************************************************************************

/* Constructor */
SelectionOperator::SelectionOperator (World* world, FitnessOperatorPtr fitness_operator)
  : Operator          (world),
    _fitness_operator (fitness_operator)
{
}

/* Destructor */
SelectionOperator::~SelectionOperator ()
{
}


//#**************************************************************************
// CLASS GEP::System::RemainderStochasticSamplingSelectionOperator
//#**************************************************************************

/* Constructor */
RemainderStochasticSamplingSelectionOperator::RemainderStochasticSamplingSelectionOperator (World* world, FitnessOperatorPtr fitness_operator)
  : SelectionOperator (world, fitness_operator)
{
}

/* Destructor */
RemainderStochasticSamplingSelectionOperator::~RemainderStochasticSamplingSelectionOperator ()
{
}

/* Perform selection */
void RemainderStochasticSamplingSelectionOperator::compute (Population& population) const
{
  Notifier* notifier = _world->getNotifier ();

  //
  // Compute individual fitness and fitness sum
  //
  typedef QMap<Object::Id, double> FitnessMap;
  FitnessMap fitness_map;

  double fitness_sum = 0.0;
  for (Population::ConstIterator i = population.begin (); i != population.end (); ++i)
    {
      const Individual& individual = *i;

      double fitness = _fitness_operator->compute (individual);

      fitness_map.insert (individual.getId (), fitness);
      fitness_sum += fitness;
    }

  //
  // Step 1: Insert individuals according to their relativ selection probability
  //
  Population selected;

  for (Population::ConstIterator i = population.begin (); i != population.end (); ++i)
    {
      const Individual& individual = *i;
      Object::Id id = individual.getId ();

      Q_ASSERT (fitness_map.find (id) != fitness_map.end ());

      double p = fitness_map[id] / fitness_sum;
      uint n = static_cast<uint> (floor (p * population.getSize ()));

      fitness_map[id] = p * population.getSize () - floor (p * population.getSize ());

      for (uint i=0; i < n; ++i)
        {
          Individual copied (individual);
          copied.computeUniqueId ();
          selected.add (copied);

          notifier->notifyIndividualSelection (individual.getId (), copied.getId ());
        }
    }

  //
  // Step 2: The remaining space in the target population is filled using roulette wheel selection
  //
  fitness_sum = 0.0;
  for (FitnessMap::const_iterator i = fitness_map.begin (); i != fitness_map.end (); ++i)
    fitness_sum += i.value ();

  PopulationFitnessIndex fitness_index (population, fitness_map);

  while (population.getSize () > selected.getSize ())
    {
      double value = _world->getRandom ();

      double sum = 0.0;
      bool found = false;
      for (uint i=0; i < fitness_index.getSize () && !found; ++i)
        {
          const Individual& individual = fitness_index.getIndividual (i);

          FitnessMap::const_iterator pos = fitness_map.find (individual.getId ());
          Q_ASSERT (pos != fitness_map.end ());

          sum += pos.value () / fitness_sum;

          if (value <= sum)
            {
              Individual copied (individual);
              copied.computeUniqueId ();
              selected.add (copied);

              notifier->notifyIndividualSelection (individual.getId (), copied.getId ());

              found = true;
            }
        }

      Q_ASSERT (found);
    }

  population = selected;
}

}
}
