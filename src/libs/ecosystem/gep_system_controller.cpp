/*
 * gep_system_controller.cpp - Base class for all process controllers
 *
 * Frank Cieslok, Aug. 2011
 */

#define GEP_DEBUG

#include "GEPSystemDebug.h"
#include "GEPSystemController.h"
#include "GEPSystemNotifier.h"
#include "GEPSystemWorld.h"

#include <limits>

namespace GEP {
namespace System {

//#**************************************************************************
// CLASS GEP::System::Controller
//#**************************************************************************

/* Constructor */
Controller::Controller (World* world)
  : _world                (world),
    _crossover_operator   (),
    _fitness_operator     (),
    _mutation_operator    (),
    _selection_operator   (),
    _termination_operator ()
{
}

/* Return the world the controller works with */
World* Controller::getWorld () const
{
  return _world;
}

/* Get crossover operator */
CrossoverOperatorPtr Controller::getCrossoverOperator () const
{
  return _crossover_operator;
}

/* Set crossover operator */
void Controller::setCrossoverOperator (CrossoverOperatorPtr crossover_operator)
{
  _crossover_operator = crossover_operator;
}

/* Get fitness operator */
FitnessOperatorPtr Controller::getFitnessOperator () const
{
  return _fitness_operator;
}

/* Set fitness operator */
void Controller::setFitnessOperator (FitnessOperatorPtr fitness_operator)
{
  _fitness_operator = fitness_operator;
}

/* Get mutation operator */
MutationOperatorPtr Controller::getMutationOperator () const
{
  return _mutation_operator;
}

/* Set mutation operator */
void Controller::setMutationOperator (MutationOperatorPtr mutation_operator)
{
  _mutation_operator = mutation_operator;
}

/* Get selection operator */
SelectionOperatorPtr Controller::getSelectionOperator () const
{
  return _selection_operator;
}

/* Set selection operator */
void Controller::setSelectionOperator (SelectionOperatorPtr selection_operator)
{
  _selection_operator = selection_operator;
}

/* Get termination operator */
TerminationOperatorPtr Controller::getTerminationOperator () const
{
  return _termination_operator;
}

/* Set termination operator */
void Controller::setTerminationOperator (TerminationOperatorPtr termination_operator)
{
  _termination_operator = termination_operator;
}

/* Init controller for a new run */
void Controller::initialize ()
{
}

//#**************************************************************************
// CLASS GEP::System::SinglePopulationController
//#**************************************************************************

/* Constructor */
SinglePopulationController::SinglePopulationController (World* world)
  : Controller       (world),
    _population      (),
    _current_step    (0),
    _minimum_fitness (0.0),
    _maximum_fitness (0.0),
    _average_fitness (0.0)
{
}

/* Returns current execution step */
int SinglePopulationController::getCurrentStep () const
{
  return _current_step;
}

/* Returns the number of necessary steps */
int SinglePopulationController::getNumberOfSteps () const
{
  Q_ASSERT (_termination_operator != 0);
  return _termination_operator->getNumberOfSteps ();
}

/* Returns current fitness value */
double SinglePopulationController::getCurrentFitness (Controller::FitnessStatistics_t type) const
{
  double fitness = 0.0;

  switch (type)
    {
    case Controller::FitnessStatistics::MINIMUM:
      fitness = _minimum_fitness;
      break;
    case Controller::FitnessStatistics::MAXIMUM:
      fitness = _maximum_fitness;
      break;
    case Controller::FitnessStatistics::AVERAGE:
      fitness = _average_fitness;
      break;
    }

  return fitness;
}

/* Returns the current population */
const Population& SinglePopulationController::getPopulation () const
{
  return _population;
}

/* Set the current population */
void SinglePopulationController::setPopulation (const Population& population)
{
  _population = population;
}

/* Initialize algorithm */
void SinglePopulationController::initialize ()
{
  Q_ASSERT (_fitness_operator != 0);
  Q_ASSERT (_selection_operator != 0);
  Q_ASSERT (_crossover_operator != 0);
  Q_ASSERT (_mutation_operator != 0);
  Q_ASSERT (_termination_operator != 0);

  _population = _world->generatePopulation ();
  _current_step = 0;

  updateFitness ();
}

/* Execute algorithm */
bool SinglePopulationController::executeNextStep ()
{
  System::Notifier::getNotifier ()->notifyControllerStep (this);

  //
  // Compute single step
  //
  _selection_operator->compute (this, _population);
  updateFitness ();

  _crossover_operator->compute (_population);
  updateFitness ();

  _mutation_operator->compute (_population);
  updateFitness ();

  return _termination_operator->compute (_population, ++_current_step);
}

/*
 * Return cached fitness of an individual
 */
double SinglePopulationController::getFitness (const Individual& individual) const
{
  FitnessMap::ConstIterator pos = _fitness.find (individual.getId ());
  Q_ASSERT (pos != _fitness.end ());
  return pos.value ();
}


/*
 * Compute current population fitness
 */
void SinglePopulationController::updateFitness ()
{
  _fitness.clear ();

  _minimum_fitness = std::numeric_limits<double>::max ();
  _maximum_fitness = -std::numeric_limits<double>::max ();
  _average_fitness = 0.0;

  //
  // Compute raw fitness
  //
  FitnessMap raw_fitness;
  double minimum_raw_fitness = std::numeric_limits<double>::max ();
  double maximum_raw_fitness = -std::numeric_limits<double>::max ();

  for (Population::ConstIterator i = _population.begin (); i != _population.end (); ++i)
    {
      const Individual& individual = *i;
      double fitness = _world->computeFitness (individual);

      raw_fitness.insert (individual.getId (), fitness);
      minimum_raw_fitness = qMin (minimum_raw_fitness, fitness);
      maximum_raw_fitness = qMax (maximum_raw_fitness, fitness);
    }

  //
  // Normalize raw fitness
  //
  for (Population::ConstIterator i = _population.begin (); i != _population.end (); ++i)
    {
      const Individual& individual = *i;

      FitnessMap::ConstIterator pos = raw_fitness.find (individual.getId ());
      Q_ASSERT (pos != raw_fitness.end ());

      _fitness.insert (individual.getId (), (pos.value () - minimum_raw_fitness) / (maximum_raw_fitness - minimum_raw_fitness));
    }

  _fitness_operator->initialize (_fitness);

  for (FitnessMap::Iterator i = _fitness.begin (); i != _fitness.end (); ++i)
    {
      double fitness = _fitness_operator->compute (i.value ());
      i.value () = fitness;

      _minimum_fitness = qMin (_minimum_fitness, fitness);
      _maximum_fitness = qMax (_maximum_fitness, fitness);
      _average_fitness += fitness;
    }

  _average_fitness /= _population.getSize ();

  switch (_world->getFitnessType ())
    {
    case World::FitnessType::HIGHER_IS_BETTER:
      break;
    case World::FitnessType::HIGHER_IS_WORSE:
      break;
    }
}

}
}

