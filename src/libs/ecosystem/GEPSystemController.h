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

/*
 * Base class for all process controllers
 */
class Controller
{
public:
  Controller ();

  void setCrossoverOperator (CrossoverOperatorPtr crossover_operator);
  void setFitnessOperator (FitnessOperatorPtr fitness_operator);
  void setMutationOperator (MutationOperatorPtr mutation_operator);
  void setSelectionOperator (SelectionOperatorPtr selection_operator);
  void setTerminationOperator (TerminationOperatorPtr termination_operator);

  struct FitnessType { enum Type_t { MINIMUM, MAXIMUM, AVERAGE }; };
  typedef FitnessType::Type_t FitnessType_t;

  virtual double getCurrentFitness (FitnessType_t type) const = 0;
  virtual uint getCurrentStep () const = 0;

  virtual void initialize ();
  virtual bool executeStep () = 0;

  virtual const Population& getPopulation () const = 0;

protected:
  CrossoverOperatorPtr _crossover_operator;
  FitnessOperatorPtr _fitness_operator;
  MutationOperatorPtr _mutation_operator;
  SelectionOperatorPtr _selection_operator;
  TerminationOperatorPtr _termination_operator;
};


/*
 * Single population standard controller
 */
class SinglePopulationController : public Controller
{
public:
  SinglePopulationController (const Population& population);

  virtual double getCurrentFitness (Controller::FitnessType_t type) const;
  virtual uint getCurrentStep () const;

  virtual void initialize ();
  virtual bool executeStep ();

  virtual const Population& getPopulation () const;

private:
  void updateFitness ();

private:
  Population _population;

  uint _current_step;

  double _minimum_fitness;
  double _maximum_fitness;
  double _average_fitness;
};


}
}

#endif
