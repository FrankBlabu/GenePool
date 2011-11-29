/*
 * GEPSystemTemperatureFunction.h - Temperature functions for the evolution process
 *
 * Frank Cieslok, Nov. 2011
 */

#ifndef __GEP_SYSTEM_TEMPERATURE_FUNCTION_H__
#define __GEP_SYSTEM_TEMPERATURE_FUNCTION_H__

#include <QtCore/QSharedPointer>

namespace GEP {
namespace System {

/*
 * Base class for all temperature functions
 *
 * Each temperature function decreases the system temperature
 * from 1.0 down to 0.0
 */
class TemperatureFunction
{
public:
    TemperatureFunction ();
    virtual ~TemperatureFunction ();

    double getTemperature (int step, int number_of_steps) const;

protected:
    virtual double computeTemperature (double percent) const = 0;
};

typedef QSharedPointer<TemperatureFunction> TemperatureFunctionPtr;

/*
 * Linear temperature function
 */
class LinearTemperatureFunction : public TemperatureFunction
{
public:
    LinearTemperatureFunction ();
    virtual ~LinearTemperatureFunction ();

protected:
    virtual double computeTemperature (double percent) const;
};

/*
 * Quotient temperature function
 */
class QuotientTemperatureFunction : public TemperatureFunction
{
public:
    QuotientTemperatureFunction ();
    virtual ~QuotientTemperatureFunction ();

protected:
    virtual double computeTemperature (double percent) const;
};

}
}

#endif
