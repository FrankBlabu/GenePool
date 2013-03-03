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
#include <boost/bind.hpp>

#include <QFuture>
#include <QtConcurrent>
#include <QtCore/QThread>

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
    _termination_operator (),
    _temperature_function ()
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

/* Get temperature function */
TemperatureFunctionPtr Controller::getTemperatureFunction () const
{
  return _temperature_function;
}

/* Set temperature function */
void Controller::setTemperatureFunction (TemperatureFunctionPtr temperature_function)
{
  _temperature_function = temperature_function;
}

/*
 * Return system temperature
 *
 * \return Normalized system temperature in [0:1[
 */
double Controller::getTemperature () const
{
  Q_ASSERT (_termination_operator != 0);
  Q_ASSERT (_temperature_function != 0);

  return _temperature_function->getTemperature (getCurrentStep (), _termination_operator->getNumberOfSteps ());
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

/* Returns current average fitness value */
double SinglePopulationController::getCurrentAverageFitness () const
{
  return _average_fitness;
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
  Q_ASSERT (_temperature_function != 0);

  _population = _world->generatePopulation ();
  _current_step = 0;

  updateFitness ();

  System::Notifier::getNotifier ()->notifyControllerStepStart (this);
  System::Notifier::getNotifier ()->notifyControllerStepEnd (this);

  ++_current_step;
}

/* Execute algorithm */
bool SinglePopulationController::executeNextStep ()
{
  System::Notifier::getNotifier ()->notifyControllerStepStart (this);

  //
  // Compute single step
  //
  _selection_operator->compute (this, _population);
  updateFitness ();

  _crossover_operator->compute (this, _population);
  updateFitness ();

  _mutation_operator->compute (this, _population);
  updateFitness ();

  System::Notifier::getNotifier ()->notifyControllerStepEnd (this);

  return _termination_operator->compute (this, _population, ++_current_step);
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
  _average_fitness = 0.0;
  //
  // Compute raw fitness
  //
  for (int index=0; index < _world->getNumberOfFitnessValues (); ++index)
    {
      FitnessMap raw_fitness;
      double minimum_raw_fitness = std::numeric_limits<double>::max ();
      double maximum_raw_fitness = -std::numeric_limits<double>::max ();

      QList<double> results = QtConcurrent::blockingMapped< QList<double> >
          (_population.begin (), _population.end (), boost::bind (&World::computeFitness, _world, index, _1));

      int count = 0;
      for (Population::ConstIterator i = _population.begin (); i != _population.end (); ++i, ++count)
        {
          const Individual& individual = *i;

          Q_ASSERT (index < results.size ());
          double fitness = results[count];

          raw_fitness.insert (individual.getId (), fitness);
          minimum_raw_fitness = qMin (minimum_raw_fitness, fitness);
          maximum_raw_fitness = qMax (maximum_raw_fitness, fitness);
        }

      Q_ASSERT (count == _population.getSize ());

      switch (_world->getFitnessType (index))
        {
        case World::FitnessType::HIGHER_IS_BETTER:
          break;

        case World::FitnessType::HIGHER_IS_WORSE:
          {
            double median = minimum_raw_fitness + (maximum_raw_fitness - minimum_raw_fitness) / 2;

            for (FitnessMap::Iterator i = raw_fitness.begin (); i != raw_fitness.end (); ++i)
              {
                double fitness = i.value ();
                i.value () = median + (median - fitness);
              }
          }
          break;
        }

      //
      // Normalize raw fitness
      //
      for (Population::ConstIterator i = _population.begin (); i != _population.end (); ++i)
        {
          const Individual& individual = *i;

          FitnessMap::ConstIterator pos = raw_fitness.find (individual.getId ());
          Q_ASSERT (pos != raw_fitness.end ());

          double fitness = (pos.value () - minimum_raw_fitness) / (maximum_raw_fitness - minimum_raw_fitness);

          fitness *= _world->getFitnessWeight (index);

          if (qFuzzyCompare (fitness, 1.0))
            fitness = 1.0;
          else if (qFuzzyIsNull (fitness))
            fitness = 0.0;

          Q_ASSERT (fitness >= 0.0);
          Q_ASSERT (fitness <= 1.0);

          if (i == 0)
            _fitness.insert (individual.getId (), fitness);
          else
            _fitness[individual.getId ()] += fitness;
        }
    }

  _fitness_operator->initialize (_fitness);

  for (FitnessMap::Iterator i = _fitness.begin (); i != _fitness.end (); ++i)
    {
      double fitness = _fitness_operator->compute (i.value ());
      i.value () = fitness;

      _average_fitness += fitness;
    }

  _average_fitness /= _population.getSize ();

  Q_ASSERT (_average_fitness >= 0.0);
  Q_ASSERT (_average_fitness <= 1.0);
}

}
}

