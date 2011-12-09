/*
 * gep_system_temperature_function.cpp - Temperature functions for the evolution process
 *
 * Frank Cieslok, Nov. 2011
 */

#define GEP_DEBUG

#include "GEPSystemTemperatureFunction.h"
#include "GEPSystemDebug.h"

namespace GEP {
namespace System {

//#**************************************************************************
// CLASS GEP::System::TemperatureFunction
//#**************************************************************************

/* Constructor */
TemperatureFunction::TemperatureFunction ()
{
}

/* Destructor */
TemperatureFunction::~TemperatureFunction ()
{
}

/*
 * Get system temperature
 *
 * \param step            Current evolution step
 * \param number_of_steps Number of overall evolution steps
 */
double TemperatureFunction::getTemperature (int step, int number_of_steps) const
{
  Q_ASSERT (number_of_steps > 0);
  Q_ASSERT (step < number_of_steps);

  double temperature = computeTemperature (static_cast<double> (step + 1) / static_cast<double> (number_of_steps));

  Q_ASSERT (temperature >= 0.0);
  Q_ASSERT (temperature <= 1.0);

  return temperature;
}


//#**************************************************************************
// CLASS GEP::System::LinearTemperatureFunction
//#**************************************************************************

/* Constructor */
LinearTemperatureFunction::LinearTemperatureFunction ()
{
}

/* Destructor */
LinearTemperatureFunction::~LinearTemperatureFunction ()
{
}

/*
 * Compute current system temperature
 *
 * \param percent Temperature within a certain percentage of complete evolution
 * \return Normalized temperature in the interval [0:1[
 */
double LinearTemperatureFunction::computeTemperature (double percent) const
{
  Q_ASSERT (percent >= 0.0);
  Q_ASSERT (percent <= 1.0);

  return 1.0 - percent;
}

//#**************************************************************************
// CLASS GEP::System::QuotientTemperatureFunction
//#**************************************************************************

/* Temperature scaling */
const double QuotientTemperatureFunction::SCALE = 5.0;

/* Constructor */
QuotientTemperatureFunction::QuotientTemperatureFunction ()
{
}

/* Destructor */
QuotientTemperatureFunction::~QuotientTemperatureFunction ()
{
}

/*
 * Compute current system temperature
 *
 * \param percent Temperature within a certain percentage of complete evolution
 * \return Normalized temperature in the interval [0:1[
 */
double QuotientTemperatureFunction::computeTemperature (double percent) const
{
  Q_ASSERT (percent >= 0.0);
  Q_ASSERT (percent <= 1.0);

  return 1 / ((1.0 + percent) * SCALE);
}

}
}
