/*
 * gep_system_controller.cpp - Base class for all process controllers
 *
 * Frank Cieslok, Aug. 2011
 */

#include "GEPSystemController.h"

namespace GEP {
namespace System {

//#**************************************************************************
// CLASS GEP::System::Controller
//#**************************************************************************

/* Constructor */
Controller::Controller ()
: _crossover_operator (),
  _fitness_operator   (),
  _mutation_operator  (),
  _selection_operator ()
{
}

/* Destructor */
Controller::~Controller ()
{
}

/*
 * Execute algorithm
 */
PopulationPtr Controller::run (PopulationPtr population)
{
  //
  // Check if all neccessary operators are registered
  //
  Q_ASSERT (_crossover_operator != 0);
  Q_ASSERT (_fitness_operator != 0);
  Q_ASSERT (_mutation_operator != 0);
  Q_ASSERT (_selection_operator != 0);

  //
  // Compute initial fitness of the population
  //
  population->compute ();

  //
  // Main loop
  //
  double fitness = 0.0;
  uint step = 0;

  while (!isFinished (population, fitness, step))
    {
      PopulationPtr selected = _selection_operator->compute (population);
      PopulationPtr crossed = _crossover_operator->compute (selected);
      population = _mutation_operator->compute (crossed);

      population->compute ();

      fitness = _fitness_operator->compute (population);
      step += 1;
    }

  return population;
}

/*
 * Check if the computation should be terminated for the given population
 */
bool Controller::isFinished (PopulationPtr population, double fitness, uint step)
{
  Q_UNUSED (population);
  Q_UNUSED (fitness);
  Q_UNUSED (step);

  return false;
}

/*
 * Sets the operator used for individual crossover
 */
void Controller::setCrossoverOperator (CrossoverOperatorPtr crossover_operator)
{
  _crossover_operator = crossover_operator;
}

/*
 * Sets the operator used for individual crossover
 */
void Controller::setFitnessOperator (FitnessOperatorPtr fitness_operator)
{
  _fitness_operator = fitness_operator;
}

/*
 * Sets the operator used for individual mutation
 */
void Controller::setMutationOperator (MutationOperatorPtr mutation_operator)
{
  _mutation_operator = mutation_operator;
}

/*
 * Sets the operator used for individual selection
 */
void Controller::setSelectionOperator (SelectionOperatorPtr selection_operator)
{
  _selection_operator = selection_operator;
}

}
}

