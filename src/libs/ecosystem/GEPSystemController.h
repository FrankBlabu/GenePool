/*
 * GEPSystemController.h - Base class for all process controllers
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_CONTROLLER_H__
#define __GEP_SYSTEM_CONTROLLER_H__

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

  virtual uint getStepCounter () const = 0;

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

  typedef boost::shared_ptr< CrossoverOperator<T> > CrossoverOperatorPtr;
  typedef boost::shared_ptr< FitnessOperator<T> > FitnessOperatorPtr;
  typedef boost::shared_ptr< MutationOperator<T> > MutationOperatorPtr;
  typedef boost::shared_ptr< SelectionOperator<T> > SelectionOperatorPtr;
  typedef boost::shared_ptr< TerminationOperator<T> > TerminationOperatorPtr;

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

  virtual uint getStepCounter () const;

  virtual void initialize ();
  virtual bool executeStep ();

private:
  Population<T> _population;

  uint _step_counter;
};

/* Constructor */
template <class T>
SinglePopulationController<T>::SinglePopulationController (const Population<T>& population)
  : _population   (population),
    _step_counter (0)
{
}

/* Returns current execution step */
template<class T>
uint SinglePopulationController<T>::getStepCounter () const
{
  return _step_counter;
}

/* Initialize algorithm */
template <class T>
void SinglePopulationController<T>::initialize ()
{
#if 0
  Q_ASSERT (StandardController<T>::_crossover_operator != 0);
#endif
  Q_ASSERT (StandardController<T>::_fitness_operator != 0);
#if 0
  Q_ASSERT (StandardController<T>::_mutation_operator != 0);
  Q_ASSERT (StandardController<T>::_selection_operator != 0);
#endif
  Q_ASSERT (StandardController<T>::_termination_operator != 0);

  _step_counter = 0;
}

/* Execute algorithm */
template <class T>
bool SinglePopulationController<T>::executeStep ()
{
  return StandardController<T>::_termination_operator->compute (_population, ++_step_counter);
}

}
}

#endif
