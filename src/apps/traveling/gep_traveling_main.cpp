/*
 * gep_traveling_main.cpp - Evolutionary algorithm solving the traveling salesman problem
 *
 * Frank Cieslok, Aug. 2011
 */

#include "GEPTravelingWorld.h"
#include "GEPTravelingWorldDisplay.h"

#include <QtGlobal>
#include <QtGui/QApplication>

#include <GEPSystemController.h>
#include <GEPSystemFitnessOperator.h>
#include <GEPSystemInit.h>
#include <GEPSystemMutationOperator.h>
#include <GEPSystemSelectionOperator.h>
#include <GEPSystemShuffleComparator.h>
#include <GEPScopeInit.h>
#include <GEPScopeMainWindow.h>

//#**************************************************************************
// Computation parameters
//#**************************************************************************

namespace {

//
// Number of cities to be visited
//
const int NUMBER_OF_CITIES = 10;

//
// Number of individuals in initial population
//
const int POPULATION_SIZE = 100;

//
// Number of steps until termination
//
const int NUMBER_OF_STEPS = 100;

}

//#**************************************************************************
// MAIN
//#**************************************************************************

int main(int argc, char *argv[])
{
    QApplication app (argc, argv);

    GEP::System::InitLibrary ();
    GEP::Scope::InitLibrary ();

    //
    // Setup world and controller
    //
    GEP::Traveling::World world;

    world.setNumberOfCities (NUMBER_OF_CITIES);
    world.setPopulationSize (POPULATION_SIZE);
    world.generateWorld ();

    QSharedPointer<GEP::System::FitnessOperator> fitness_operator (new GEP::System::LinearDynamicScaledFitnessOperator (5.0));
    //QSharedPointer<GEP::System::SelectionOperator> selection_operator (new GEP::System::RemainderStochasticSamplingSelectionOperator ());
    QSharedPointer<GEP::System::SelectionOperator> selection_operator (new GEP::System::RouletteWheelSelectionOperator ());
    QSharedPointer<GEP::System::CrossoverOperator> crossover_operator (new GEP::System::PartiallyMatchedCrossoverOperator ());
    QSharedPointer<GEP::System::MutationOperator> mutation_operator (new GEP::System::SwappingMutationOperator (0.5 * 1.0 / NUMBER_OF_CITIES));
    QSharedPointer<GEP::System::TerminationOperator> termination_operator (new GEP::System::FixedStepTerminationOperator (NUMBER_OF_STEPS));

    GEP::System::SinglePopulationController controller (&world);

    controller.setFitnessOperator (fitness_operator);
    controller.setSelectionOperator (selection_operator);
    controller.setCrossoverOperator (crossover_operator);
    controller.setMutationOperator (mutation_operator);
    controller.setTerminationOperator (termination_operator);

    //
    // Show main window and start computation
    //
    GEP::Scope::MainWindow main_window (&controller);
    main_window.setWorldDisplay (new GEP::Traveling::WorldDisplay (&world, 0));
    main_window.show ();

    return app.exec();
}
