/*
 * traveling.cpp - Evolutionary algorithm solving the traveling salesman problem
 *
 * Frank Cieslok, Aug. 2011
 */

#include <QtGui/QApplication>

#include <GEPSystemController.h>
#include <GEPSystemIndividual.h>
#include <GEPSystemFitnessOperator.h>
#include <GEPScopeMainWindow.h>

typedef GEP::System::Individual<uint> TravelingIndividual;

int main(int argc, char *argv[])
{
    QApplication app (argc, argv);

    GEP::System::Population<uint> initial_population;

    GEP::System::SinglePopulationController<uint> controller (initial_population);
    controller.setFitnessOperator (boost::shared_ptr< GEP::System::FitnessOperator<uint> > (new GEP::System::LinearDynamicScaledFitnessOperator<uint> (1.0)));

    GEP::Scope::MainWindow main_window (&controller);
    main_window.show();

    return app.exec();
}
