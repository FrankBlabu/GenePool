/*
 * GEPSystemSelectionOperator.h - Base class for selection operators
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_SELECTION_OPERATOR_H__
#define __GEP_SYSTEM_SELECTION_OPERATOR_H__

#include "GEPSystemOperator.h"
#include "GEPSystemFitnessOperator.h"
#include "GEPSystemPopulation.h"
#include "GEPSystemPopulationFitnessIndex.h"
#include "GEPSystemRandomNumberGenerator.h"

#include <math.h>
#include <map>

namespace GEP {
namespace System {

class Controller;

/*
 * Base class for selection operators
 */
class SelectionOperator : public Operator
{
public:
  SelectionOperator ();
  virtual ~SelectionOperator ();

  virtual void compute (const Controller* controller, Population& population) = 0;
};

typedef QSharedPointer<SelectionOperator> SelectionOperatorPtr;

/*
 * Roulette wheel selection operator
 */
class RouletteWheelSelectionOperator : public SelectionOperator
{
public:
  RouletteWheelSelectionOperator ();
  virtual ~RouletteWheelSelectionOperator ();

  virtual void compute (const Controller* controller, Population& population);

private:
  struct WheelSegment
  {
    WheelSegment (const Object::Id& id, double fitness);
    WheelSegment (const WheelSegment& toCopy);

    Object::Id _id;
    double _fitness;
  };

  RandomNumberGenerator _random_number_generator;
};


/*
 * Selection operator based on remainder stochastic sampling
 */
class RemainderStochasticSamplingSelectionOperator : public SelectionOperator
{
public:
  RemainderStochasticSamplingSelectionOperator ();
  virtual ~RemainderStochasticSamplingSelectionOperator ();

  struct SelectionMode { enum Type_t { TAKE_AWAY, PUT_BACK }; };
  typedef SelectionMode::Type_t SelectionMode_t;

  SelectionMode_t getSelectionMode () const;
  void setSelectionMode (SelectionMode_t selection_mode);

  virtual void compute (const Controller* controller, Population& population);

private:
  SelectionMode_t _selection_mode;
  RandomNumberGenerator _random_number_generator;
};

}
}

#endif
