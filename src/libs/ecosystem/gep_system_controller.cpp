/*
 * gep_system_controller.cpp - Base class for all process controllers
 *
 * Frank Cieslok, Aug. 2011
 */

#include "GEPSystemController.h"

#include <limits>

namespace GEP {
namespace System {

//#**************************************************************************
// CLASS GEP::System::Controller
//#**************************************************************************

/* Constructor */
Controller::Controller ()
  : _crossover_operator   (),
    _fitness_operator     (),
    _mutation_operator    (),
    _selection_operator   (),
    _termination_operator ()
{
}

/* Set crossover operator */
void Controller::setCrossoverOperator (CrossoverOperatorPtr crossover_operator)
{
  _crossover_operator = crossover_operator;
}

/* Set fitness operator */
void Controller::setFitnessOperator (FitnessOperatorPtr fitness_operator)
{
  _fitness_operator = fitness_operator;
}

/* Set mutation operator */
void Controller::setMutationOperator (MutationOperatorPtr mutation_operator)
{
  _mutation_operator = mutation_operator;
}

/* Set selection operator */
void Controller::setSelectionOperator (SelectionOperatorPtr selection_operator)
{
  _selection_operator = selection_operator;
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
SinglePopulationController::SinglePopulationController (const Population& population)
  : _population      (population),
    _current_step    (0),
    _minimum_fitness (0.0),
    _maximum_fitness (0.0),
    _average_fitness (0.0)
{
}

/* Returns current execution step */
uint SinglePopulationController::getCurrentStep () const
{
  return _current_step;
}

/* Returns current fitness value */
double SinglePopulationController::getCurrentFitness (Controller::FitnessType_t type) const
{
  double fitness = 0.0;

  switch (type)
    {
    case Controller::FitnessType::MINIMUM:
      fitness = _minimum_fitness;
      break;
    case Controller::FitnessType::MAXIMUM:
      fitness = _maximum_fitness;
      break;
    case Controller::FitnessType::AVERAGE:
      fitness = _average_fitness;
      break;
    }

  return fitness;
}

/* Initialize algorithm */
void SinglePopulationController::initialize ()
{
  Q_ASSERT (_fitness_operator != 0);
  Q_ASSERT (_selection_operator != 0);
  Q_ASSERT (_crossover_operator != 0);
  Q_ASSERT (_mutation_operator != 0);
  Q_ASSERT (_termination_operator != 0);

  _current_step = 0;
  _fitness_operator->initialize (_population);
}

/* Execute algorithm */
bool SinglePopulationController::executeStep ()
{
  //
  // Compute single step
  //
  _selection_operator->compute (_population);
  _crossover_operator->compute (_population);
  _mutation_operator->compute (_population);
  _fitness_operator->initialize (_population);

  //
  // Compute fitness values
  //
  _minimum_fitness = std::numeric_limits<double>::max ();
  _maximum_fitness = 0.0;
  _average_fitness = 0.0;

  for (Population::ConstIterator i = _population.begin (); i != _population.end (); ++i)
    {
      const Individual& individual = *i;
      double fitness = _fitness_operator->compute (individual);

      _minimum_fitness = std::min (_minimum_fitness, fitness);
      _maximum_fitness = std::max (_maximum_fitness, fitness);
      _average_fitness += fitness;
    }

  _average_fitness /= _population.getSize ();

  return _termination_operator->compute (_population, ++_current_step);
}


}
}

