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
TerminationOperator::TerminationOperator (World* world)
: Operator (world)
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
FixedStepTerminationOperator::FixedStepTerminationOperator (World* world, int steps)
  : TerminationOperator (world),
    _steps              (steps)
{
}

/* Destructor */
FixedStepTerminationOperator::~FixedStepTerminationOperator ()
{
}

/*
 * Compute if the algorithm in done
 */
bool FixedStepTerminationOperator::compute (const Population& population, int step)
{
  Q_UNUSED (population);
  return step >= _steps;
}



}
}
