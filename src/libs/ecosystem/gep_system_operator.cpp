/*
 * gep_system_operator.cpp - Base class for all operator classes
 *
 * Frank Cieslok, Aug. 2011
 */

#include "GEPSystemOperator.h"

#include <QtGlobal>

namespace GEP {
namespace System {

//#**************************************************************************
// CLASS GEP::System::Operator
//#**************************************************************************

/* Constructor */
Operator::Operator ()
: _random_number_generator ()
{
}

/* Destructor */
Operator::~Operator ()
{
}

/*
 * Generate random number in interval [0:1]
 */
double Operator::getRandom () const
{
  Q_ASSERT (_random_number_generator != 0);
  return _random_number_generator->generate ();
}

/* Sets the random number generator used by this operator */
void Operator::setRandomNumberGenerator (RandomNumberGeneratorPtr random_number_generator)
{
  _random_number_generator = random_number_generator;
}

}
}
