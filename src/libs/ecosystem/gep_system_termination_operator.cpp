/*
 * gep_system_termination_operator.cpp - Base class for termination operators
 *
 * Frank Cieslok, Aug. 2011
 */

#include "GEPSystemTerminationOperator.h"

namespace GEP {
namespace System {

//#**************************************************************************
// CLASS GEP::System::TerminationOperator
//#**************************************************************************

/* Constructor */
TerminationOperator::TerminationOperator ()
: Operator ()
{
}

/* Destructor */
TerminationOperator::~TerminationOperator ()
{
}

//#**************************************************************************
// CLASS GEP::System::FixedStepTerminationOperator
//#**************************************************************************

/* Constructor */
FixedStepTerminationOperator::FixedStepTerminationOperator (int steps)
  : TerminationOperator (),
    _steps              (steps)
{
}

/* Destructor */
FixedStepTerminationOperator::~FixedStepTerminationOperator ()
{
}

/*
 * Return the number of necessary steps
 */
int FixedStepTerminationOperator::getNumberOfSteps () const
{
  return _steps;
}

/*
 * Compute if the algorithm in done
 */
bool FixedStepTerminationOperator::compute (const Controller* controller, const Population& population, int step)
{
  Q_UNUSED (controller);
  Q_UNUSED (population);
  return step >= _steps;
}



}
}
