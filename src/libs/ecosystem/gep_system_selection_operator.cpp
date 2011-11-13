/*
 * gep_system_selection_operator.cpp - Base class for selection operators
 *
 * Frank Cieslok, Aug. 2011
 */

#define GEP_DEBUG

#include "GEPSystemSelectionOperator.h"
#include "GEPSystemNotifier.h"
#include "GEPSystemDebug.h"

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
// CLASS GEP::System::RouletteWheelSelectionOperator::WheelSegment
//#**************************************************************************

/* Constructor */
RouletteWheelSelectionOperator::WheelSegment::WheelSegment (const Object::Id& id, double fitness)
  : _id      (id),
    _fitness (fitness)
{
}

/* Copy constructor */
RouletteWheelSelectionOperator::WheelSegment::WheelSegment (const WheelSegment& toCopy)
  : _id      (toCopy._id),
    _fitness (toCopy._fitness)
{
}

//#**************************************************************************
// CLASS GEP::System::RouletteWheelSelectionOperator
//#**************************************************************************

/* Constructor */
RouletteWheelSelectionOperator::RouletteWheelSelectionOperator (World* world, FitnessOperatorPtr fitness_operator)
  : SelectionOperator (world, fitness_operator)
{
}

/* Destructor */
RouletteWheelSelectionOperator::~RouletteWheelSelectionOperator ()
{
}

/* Perform selection */
void RouletteWheelSelectionOperator::compute (Population& population)
{
  SelectionNotificationList notifications;

  //
  // Step 1: Compute fitness list
  //
  QList<WheelSegment> segments;

  double fitness_sum = 0.0;
  for (Population::ConstIterator i = population.begin (); i != population.end (); ++i)
    {
      const Individual& individual = *i;

      double fitness = _fitness_operator->compute (individual);

      fitness_sum += fitness;
      segments.append (WheelSegment (individual.getId (), fitness_sum));
    }

  for (int i=0; i < segments.size (); ++i)
    {
      WheelSegment& segment = segments[i];
      segment._fitness /= fitness_sum;
    }

  //
  // Step 2: Perform roulette wheel selection
  //
  Population selected;

  while (selected.getSize () < population.getSize ())
    {
      double n = _random_number_generator.generate ();

      bool found = false;
      for (int i=0; i < segments.size () && !found; ++i)
        {
          const WheelSegment& segment = segments[i];
          if (n <= segment._fitness)
            {
              const Individual& individual = population[segment._id];
              Individual copied (individual);
              copied.computeUniqueId ();
              selected.add (copied);

              notifications.append (SelectionNotification (IndividualInfo (individual, _world->computeFitness (individual)),
                                                           IndividualInfo (copied, _world->computeFitness (copied))));

              found= true;
            }
        }

      Q_ASSERT (found);
    }

  population = selected;

  System::Notifier::getNotifier ()->notifySelection (notifications);
}


//#**************************************************************************
// CLASS GEP::System::RemainderStochasticSamplingSelectionOperator
//#**************************************************************************

/* Constructor */
RemainderStochasticSamplingSelectionOperator::RemainderStochasticSamplingSelectionOperator (World* world, FitnessOperatorPtr fitness_operator)
  : SelectionOperator (world, fitness_operator),
    _selection_mode (SelectionMode::TAKE_AWAY)
{
}

/* Destructor */
RemainderStochasticSamplingSelectionOperator::~RemainderStochasticSamplingSelectionOperator ()
{
}

/* Get operator selection mode */
RemainderStochasticSamplingSelectionOperator::SelectionMode_t RemainderStochasticSamplingSelectionOperator::getSelectionMode () const
{
  return _selection_mode;
}

/* Set operator selection mode */
void RemainderStochasticSamplingSelectionOperator::setSelectionMode (SelectionMode_t selection_mode)
{
  _selection_mode = selection_mode;
}


/* Perform selection */
void RemainderStochasticSamplingSelectionOperator::compute (Population& population)
{
  SelectionNotificationList notifications;

  //
  // Step 1: Compute individual fitness and fitness sum
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
  // Step 2: Insert individuals according to their relativ selection probability
  //
  Population selected;

  for (Population::ConstIterator i = population.begin (); i != population.end (); ++i)
    {
      const Individual& individual = *i;
      Object::Id id = individual.getId ();

      Q_ASSERT (fitness_map.find (id) != fitness_map.end ());

      double p = fitness_map[id] / fitness_sum;
      int n = static_cast<int> (floor (p * population.getSize ()));

      switch (_selection_mode)
        {
        case SelectionMode::PUT_BACK:
          break;
        case SelectionMode::TAKE_AWAY:
          fitness_map[id] = p * population.getSize () - floor (p * population.getSize ());
          break;
        }

      for (int i=0; i < n; ++i)
        {
          Individual copied (individual);
          copied.computeUniqueId ();
          selected.add (copied);

          notifications.append (SelectionNotification (IndividualInfo (individual, _world->computeFitness (individual)),
                                                       IndividualInfo (copied, _world->computeFitness (copied))));

        }
    }

  //
  // Step 3: The remaining space in the target population is filled using roulette wheel selection
  //
  fitness_sum = 0.0;
  for (FitnessMap::const_iterator i = fitness_map.begin (); i != fitness_map.end (); ++i)
    fitness_sum += i.value ();

  PopulationFitnessIndex fitness_index (population, fitness_map);

  while (population.getSize () > selected.getSize ())
    {
      double value = _random_number_generator.generate ();

      double sum = 0.0;
      bool found = false;
      for (int i=0; i < fitness_index.getSize () && !found; ++i)
        {
          const Individual& individual = fitness_index.getIndividual (i);

          FitnessMap::const_iterator pos = fitness_map.find (individual.getId ());
          Q_ASSERT (pos != fitness_map.end ());


          sum += pos.value () / fitness_sum;

          if (sum >= value)
            {
              Individual copied (individual);
              copied.computeUniqueId ();
              selected.add (copied);

              notifications.append (SelectionNotification (IndividualInfo (individual, _world->computeFitness (individual)),
                                                           IndividualInfo (copied, _world->computeFitness (copied))));

              found = true;
            }
        }

      Q_ASSERT (found);
    }

  population = selected;

  System::Notifier::getNotifier ()->notifySelection (notifications);
}

}
}
