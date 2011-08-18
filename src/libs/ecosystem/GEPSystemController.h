/*
 * GEPSystemController.h - Base class for all process controllers
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_CONTROLLER_H__
#define __GEP_SYSTEM_CONTROLLER_H__

#include <QtCore/QSharedPointer>

#include "GEPSystemPopulation.h"
#include "GEPSystemCrossoverOperator.h"
#include "GEPSystemFitnessOperator.h"
#include "GEPSystemMutationOperator.h"
#include "GEPSystemSelectionOperator.h"
#include "GEPSystemTerminationOperator.h"

namespace GEP {
namespace System {

//#**************************************************************************
// CLASS GEP::System::Controller
//#**************************************************************************

/*
 * Base class for all process controllers
 */
class Controller
{
public:
  Controller ();

  struct FitnessType { enum Type_t { MINIMUM, MAXIMUM, AVERAGE }; };
  typedef FitnessType::Type_t FitnessType_t;

  virtual double getCurrentFitness (FitnessType_t type) const = 0;
  virtual uint getCurrentStep () const = 0;

  virtual void initialize ();
  virtual bool executeStep () = 0;
};


//#**************************************************************************
// CLASS GEP::System::StandardController
//#**************************************************************************

/*
 * Standard controller base class
 */
template <class T>
class StandardController : public Controller
{
public:
  StandardController ();

  typedef QSharedPointer< CrossoverOperator<T> > CrossoverOperatorPtr;
  typedef QSharedPointer< FitnessOperator<T> > FitnessOperatorPtr;
  typedef QSharedPointer< MutationOperator<T> > MutationOperatorPtr;
  typedef QSharedPointer< SelectionOperator<T> > SelectionOperatorPtr;
  typedef QSharedPointer< TerminationOperator<T> > TerminationOperatorPtr;

  void setCrossoverOperator (CrossoverOperatorPtr crossover_operator);
  void setFitnessOperator (FitnessOperatorPtr fitness_operator);
  void setMutationOperator (MutationOperatorPtr mutation_operator);
  void setSelectionOperator (SelectionOperatorPtr selection_operator);
  void setTerminationOperator (TerminationOperatorPtr termination_operator);

protected:
  CrossoverOperatorPtr _crossover_operator;
  FitnessOperatorPtr _fitness_operator;
  MutationOperatorPtr _mutation_operator;
  SelectionOperatorPtr _selection_operator;
  TerminationOperatorPtr _termination_operator;
};

/* Constructor */
template <class T>
StandardController<T>::StandardController ()
  : _crossover_operator   (),
    _fitness_operator     (),
    _mutation_operator    (),
    _selection_operator   (),
    _termination_operator ()
{
}

/* Set crossover operator */
template <class T>
void StandardController<T>::setCrossoverOperator (CrossoverOperatorPtr crossover_operator)
{
  _crossover_operator = crossover_operator;
}

/* Set fitness operator */
template <class T>
void StandardController<T>::setFitnessOperator (FitnessOperatorPtr fitness_operator)
{
  _fitness_operator = fitness_operator;
}

/* Set mutation operator */
template <class T>
void StandardController<T>::setMutationOperator (MutationOperatorPtr mutation_operator)
{
  _mutation_operator = mutation_operator;
}

/* Set selection operator */
template <class T>
void StandardController<T>::setSelectionOperator (SelectionOperatorPtr selection_operator)
{
  _selection_operator = selection_operator;
}

/* Set termination operator */
template <class T>
void StandardController<T>::setTerminationOperator (TerminationOperatorPtr termination_operator)
{
  _termination_operator = termination_operator;
}


//#**************************************************************************
// CLASS GEP::System::SinglePopulationController
//#**************************************************************************

/*
 * Single population standard controller
 */
template <class T>
class SinglePopulationController : public StandardController<T>
{
public:
  SinglePopulationController (const Population<T>& population);

  virtual double getCurrentFitness (Controller::FitnessType_t type) const;
  virtual uint getCurrentStep () const;

  virtual void initialize ();
  virtual bool executeStep ();

private:
  Population<T> _population;

  uint _current_step;

  double _minimum_fitness;
  double _maximum_fitness;
  double _average_fitness;
};

/* Constructor */
template <class T>
SinglePopulationController<T>::SinglePopulationController (const Population<T>& population)
  : _population      (population),
    _current_step    (0),
    _minimum_fitness (0.0),
    _maximum_fitness (0.0),
    _average_fitness (0.0)
{
}

/* Returns current execution step */
template<class T>
uint SinglePopulationController<T>::getCurrentStep () const
{
  return _current_step;
}

/* Returns current fitness value */
template <class T>
double SinglePopulationController<T>::getCurrentFitness (Controller::FitnessType_t type) const
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
template <class T>
void SinglePopulationController<T>::initialize ()
{
  Q_ASSERT (StandardController<T>::_fitness_operator != 0);
  Q_ASSERT (StandardController<T>::_selection_operator != 0);
  Q_ASSERT (StandardController<T>::_crossover_operator != 0);
  Q_ASSERT (StandardController<T>::_mutation_operator != 0);
  Q_ASSERT (StandardController<T>::_termination_operator != 0);

  _current_step = 0;
  StandardController<T>::_fitness_operator->initialize (_population);
}

/* Execute algorithm */
template <class T>
bool SinglePopulationController<T>::executeStep ()
{
  //
  // Compute single step
  //
  StandardController<T>::_selection_operator->compute (_population);
  StandardController<T>::_crossover_operator->compute (_population);
  StandardController<T>::_mutation_operator->compute (_population);
  StandardController<T>::_fitness_operator->initialize (_population);

  //
  // Compute fitness values
  //
  _minimum_fitness = std::numeric_limits<double>::max ();
  _maximum_fitness = 0.0;
  _average_fitness = 0.0;

  for (typename Population<T>::ConstIterator i = _population.begin (); i != _population.end (); ++i)
    {
      const Individual<T>& individual = *i;
      double fitness = StandardController<T>::_fitness_operator->compute (individual);

      _minimum_fitness = std::min (_minimum_fitness, fitness);
      _maximum_fitness = std::max (_maximum_fitness, fitness);
      _average_fitness += fitness;
    }

  _average_fitness /= _population.getSize ();

  return StandardController<T>::_termination_operator->compute (_population, ++_current_step);
}

}
}

#endif
