/*
 * GEPSystemMutationOperator.h - Base class for mutation operators
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_MUTATION_OPERATOR_H__
#define __GEP_SYSTEM_MUTATION_OPERATOR_H__

#include "GEPSystemOperator.h"
#include "GEPSystemIndividual.h"
#include "GEPSystemPopulation.h"
#include "GEPSystemDebug.h"

#include <QtCore/QMutex>

namespace GEP {
namespace System {

class Controller;
class MutationNotification;

/*
 * Base class for Mutation operators
 */
class MutationOperator : public Operator
{
public:
    MutationOperator ();
    virtual ~MutationOperator ();

    virtual void compute (const Controller* controller, Population& population) = 0;
};

typedef QSharedPointer<MutationOperator> MutationOperatorPtr;


/*
 * Base class for Mutation operators
 */
class SwappingMutationOperator : public MutationOperator
{
public:
    SwappingMutationOperator (double probability);
    virtual ~SwappingMutationOperator ();

    virtual void compute (const Controller* controller, Population& population);

private:
    void executeMutation (const Controller* controller,
                          QList<MutationNotification>* notifications,
                          Individual& individual);

private:
    QMutex _mutex;
    double _probability;
};

}
}

#endif
