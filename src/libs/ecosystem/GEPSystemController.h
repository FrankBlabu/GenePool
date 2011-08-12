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

namespace GEP {
namespace System {

/*
 * Base class for all process controllers
 */
class Controller
{
public:
    Controller ();
    virtual ~Controller ();

    PopulationPtr run (PopulationPtr population);

    virtual bool isFinished (PopulationPtr population, double fitness, uint step);

    void setCrossoverOperator (CrossoverOperatorPtr crossover_operator);
    void setFitnessOperator (FitnessOperatorPtr fitness_operator);
    void setMutationOperator (MutationOperatorPtr mutation_operator);
    void setSelectionOperator (SelectionOperatorPtr selection_operator);

private:
    CrossoverOperatorPtr _crossover_operator;
    FitnessOperatorPtr _fitness_operator;
    MutationOperatorPtr _mutation_operator;
    SelectionOperatorPtr _selection_operator;
};

}
}

#endif
