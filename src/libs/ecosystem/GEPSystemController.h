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

class World;

/*
 * Base class for all process controllers
 */
class Controller
{
public:
  Controller (World* world);

  World* getWorld () const;

  CrossoverOperatorPtr getCrossoverOperator () const;
  void setCrossoverOperator (CrossoverOperatorPtr crossover_operator);

  FitnessOperatorPtr getFitnessOperator () const;
  void setFitnessOperator (FitnessOperatorPtr fitness_operator);

  MutationOperatorPtr getMutationOperator () const;
  void setMutationOperator (MutationOperatorPtr mutation_operator);

  SelectionOperatorPtr getSelectionOperator () const;
  void setSelectionOperator (SelectionOperatorPtr selection_operator);

  TerminationOperatorPtr getTerminationOperator () const;
  void setTerminationOperator (TerminationOperatorPtr termination_operator);

  struct FitnessType { enum Type_t { MINIMUM, MAXIMUM, AVERAGE }; };
  typedef FitnessType::Type_t FitnessType_t;

  virtual double getCurrentFitness (FitnessType_t type) const = 0;
  virtual int getCurrentStep () const = 0;
  virtual int getNumberOfSteps () const = 0;

  virtual void initialize ();
  virtual bool executeNextStep () = 0;

  virtual const Population& getPopulation () const = 0;

protected:
  World* _world;

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
  SinglePopulationController (World* world);

  virtual double getCurrentFitness (Controller::FitnessType_t type) const;
  virtual int getCurrentStep () const;
  virtual int getNumberOfSteps () const;

  virtual void initialize ();
  virtual bool executeNextStep ();

  virtual const Population& getPopulation () const;
  void setPopulation (const Population& population);

private:
  void updateFitness ();

private:
  Population _population;

  int _current_step;

  double _minimum_fitness;
  double _maximum_fitness;
  double _average_fitness;
};


}
}

#endif
