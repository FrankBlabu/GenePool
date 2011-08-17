/*
 * GEPSystemTerminationOperator.h - Base class for termination operators
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_TERMINATION_OPERATOR_H__
#define __GEP_SYSTEM_TERMINAATION_OPERATOR_H__

#include "GEPSystemOperator.h"
#include "GEPSystemPopulation.h"

namespace GEP {
namespace System {

//#**************************************************************************
// CLASS GEP::System::TerminationOperator
//#**************************************************************************

/*
 * Base class for termination operators
 */
template <class T>
class TerminationOperator : public Operator<T>
{
public:
    TerminationOperator (World<T>* world);
    virtual ~TerminationOperator () {}

    virtual bool compute (const Population<T>& population, uint step) = 0;
};

/* Constructor */
template <class T>
TerminationOperator<T>::TerminationOperator (World<T>* world)
: Operator<T> (world)
{
}

//#**************************************************************************
// CLASS GEP::System::FixedStepTerminationOperator
//#**************************************************************************

/*
 * Base class for termination operators
 */
template <class T>
class FixedStepTerminationOperator : public TerminationOperator<T>
{
public:
    FixedStepTerminationOperator (World<T>* world, uint steps);
    virtual ~FixedStepTerminationOperator ();

    virtual bool compute (const Population<T>& population, uint step);

private:
    uint _steps;
};

/* Constructor */
template <class T>
FixedStepTerminationOperator<T>::FixedStepTerminationOperator (World<T>* world, uint steps)
  : TerminationOperator<T> (world),
    _steps                 (steps)
{
}

/* Destructor */
template <class T>
FixedStepTerminationOperator<T>::~FixedStepTerminationOperator ()
{
}

/*
 * Compute if the algorithm in done */
template <class T>
bool FixedStepTerminationOperator<T>::compute (const Population<T>& population, uint step)
{
  Q_UNUSED (population);
  return step >= _steps;
}


}
}

#endif
