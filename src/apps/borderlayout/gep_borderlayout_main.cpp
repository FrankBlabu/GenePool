/*
 * gep_borderlayout_main.cpp - Evolutionary algorithm solving a border layout problem
 *
 * Frank Cieslok, Nov. 2011
 */

#include "GEPBorderLayoutWorld.h"
#include "GEPBorderLayoutWorldDisplay.h"

#include <QtGlobal>
#include <QtGui/QApplication>

#include <GEPSystemController.h>
#include <GEPSystemFitnessOperator.h>
#include <GEPSystemInit.h>
#include <GEPSystemMutationOperator.h>
#include <GEPSystemSelectionOperator.h>
#include <GEPSystemShuffleComparator.h>
#include <GEPScopeMainWindow.h>

//#**************************************************************************
// Computation parameters
//#**************************************************************************

namespace {

//
// Size of the layout area
//
const QSizeF FIELD_SIZE (1000, 1000);

//
// Size of the inner connector point area
//
const QSizeF CONNECTOR_FIELD_SIZE (750, 750);

//
// Number areas to be layouted
//
const int NUMBER_OF_AREAS = 10;


//
// Minimum/Maximum area size
//
const double MINIMUM_AREA_SIZE = 10.0;
const double MAXIMUM_AREA_SIZE = 100.0;

//
// Population size
//
const int POPULATION_SIZE = 50;

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

    //
    // Setup world and controller
    //
    GEP::BorderLayout::World world;

    world.setFieldSize (FIELD_SIZE);
    world.setConnectorFieldSize (CONNECTOR_FIELD_SIZE);
    world.setNumberOfAreas (NUMBER_OF_AREAS);
    world.setMinimumAreaSize (MINIMUM_AREA_SIZE);
    world.setMaximumAreaSize (MAXIMUM_AREA_SIZE);
    world.setPopulationSize (POPULATION_SIZE);
    world.generateWorld ();

    QSharedPointer<GEP::System::FitnessOperator> fitness_operator (new GEP::System::LinearDynamicScaledFitnessOperator (5.0));
    //QSharedPointer<GEP::System::SelectionOperator> selection_operator (new GEP::System::RemainderStochasticSamplingSelectionOperator ());
    QSharedPointer<GEP::System::SelectionOperator> selection_operator (new GEP::System::RouletteWheelSelectionOperator ());
    QSharedPointer<GEP::System::CrossoverOperator> crossover_operator (new GEP::System::PartiallyMatchedCrossoverOperator ());
    QSharedPointer<GEP::System::MutationOperator> mutation_operator (new GEP::System::SwappingMutationOperator (0.5 * 1.0 / NUMBER_OF_AREAS));
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
    main_window.setWorldDisplay (new GEP::BorderLayout::WorldDisplay (&world, 0));
    main_window.show ();

    return app.exec();
}
