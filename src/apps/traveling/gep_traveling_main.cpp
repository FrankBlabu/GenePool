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
#include <GEPSystemMutationOperator.h>
#include <GEPSystemSelectionOperator.h>
#include <GEPSystemShuffleComparator.h>
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
const int POPULATION_SIZE = 1000;

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

    //
    // Create world
    //
    GEP::Traveling::World world (NUMBER_OF_CITIES);
    GEP::System::Population population;

    QVariantList sequence;
    for (int i=0; i < NUMBER_OF_CITIES; ++i)
      sequence.push_back (QVariant (i));

    for (int i=0; i < POPULATION_SIZE; ++i)
      {
        GEP::System::ShuffleComparator<QVariant> comparator (sequence);
        std::sort (sequence.begin (), sequence.end (), comparator);
        population.add (GEP::Traveling::Individual (sequence));
      }

    //
    // Setup controller
    //
    GEP::System::SinglePopulationController controller (&world, population);

    QSharedPointer<GEP::System::FitnessOperator> fitness_operator (new GEP::System::LinearDynamicScaledFitnessOperator (&world, 5.0));
    //QSharedPointer<GEP::System::SelectionOperator> selection_operator (new GEP::System::RemainderStochasticSamplingSelectionOperator (&world, fitness_operator));
    QSharedPointer<GEP::System::SelectionOperator> selection_operator (new GEP::System::RouletteWheelSelectionOperator (&world, fitness_operator));
    QSharedPointer<GEP::System::CrossoverOperator> crossover_operator (new GEP::System::PartiallyMatchedCrossoverOperator (&world));
    QSharedPointer<GEP::System::MutationOperator> mutation_operator (new GEP::System::SwappingMutationOperator (&world, 0.5 * 1.0 / NUMBER_OF_CITIES));
    QSharedPointer<GEP::System::TerminationOperator> termination_operator (new GEP::System::FixedStepTerminationOperator (&world, NUMBER_OF_STEPS));



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
