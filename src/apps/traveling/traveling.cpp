/*
 * traveling.cpp - Evolutionary algorithm solving the traveling salesman problem
 *
 * Frank Cieslok, Aug. 2011
 */

#include <QtGlobal>
#include <QtGui/QApplication>

#include <GEPSystemController.h>
#include <GEPSystemIndividual.h>
#include <GEPSystemFitnessOperator.h>
#include <GEPSystemMutationOperator.h>
#include <GEPSystemSelectionOperator.h>
#include <GEPSystemShuffleComparator.h>
#include <GEPScopeMainWindow.h>

//#**************************************************************************
// Computation parameters
//#**************************************************************************

//
// Number of cities to be visited
//
const uint NUMBER_OF_CITIES = 10;

//
// Number of individuals in initial population
//
const uint POPULATION_SIZE = 100;


//#**************************************************************************
// CLASS TravelingIndividual
//#**************************************************************************

/*
 * Individual: Single path
 */
typedef GEP::System::Individual TravelingIndividual;


//#**************************************************************************
// CLASS World
//#**************************************************************************

/*
 * World layout
 */
class TravelingWorld : public GEP::System::World
{
public:
  TravelingWorld (uint number_of_cities);

  uint getSize () const;
  const QPointF& operator[] (uint index) const;

  virtual double getFitness (const TravelingIndividual& individual);

private:
  double getDistance (uint city1, uint city2) const;

private:
  std::vector<QPointF> _cities;
  double _fitness_bias;
};

/* Constructor */
TravelingWorld::TravelingWorld (uint number_of_cities)
  : GEP::System::World (),
    _fitness_bias (0.0)
{
  //
  // Randomly place cities
  //
  for (uint i=0; i < number_of_cities; ++i)
    _cities.push_back (QPointF (getRandom (), getRandom ()));

  //
  // Compute largest city distance to get a fitness bias
  //
  double max_distance = 0.0;

  for (uint i=0; i < _cities.size (); ++i)
    for (uint j=i+1; j < _cities.size (); ++j)
      max_distance = std::max (max_distance, getDistance (i, j));

  _fitness_bias = _cities.size () * max_distance;

}

/* Return number of cities */
uint TravelingWorld::getSize () const
{
  return _cities.size ();
}

/* Return city coordinate */
const QPointF& TravelingWorld::operator[] (uint index) const
{
  Q_ASSERT (index < _cities.size ());
  return _cities[index];
}

/* Compute fitness of a single individual */
double TravelingWorld::getFitness (const TravelingIndividual& individual)
{
  double fitness = 0.0;

  for (uint i=0; i + 1 < individual.getSize (); ++i)
    fitness += getDistance (individual[i].toUInt (), individual[i + 1].toUInt ());

  return _fitness_bias - fitness;
}

/* Compute distance between two cities */
double TravelingWorld::getDistance (uint city1, uint city2) const
{
  return (_cities[city2] - _cities[city1]).manhattanLength ();
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
    TravelingWorld world (NUMBER_OF_CITIES);
    GEP::System::Population population;

    std::vector<QVariant> sequence;
    for (uint i=0; i < NUMBER_OF_CITIES; ++i)
      sequence.push_back (QVariant (i));

    for (uint i=0; i < POPULATION_SIZE; ++i)
      {
        GEP::System::ShuffleComparator<QVariant> comparator (&world, sequence);
        std::sort (sequence.begin (), sequence.end (), comparator);
        population.add (TravelingIndividual (sequence));
      }

    //
    // Setup controller
    //
    GEP::System::SinglePopulationController controller (population);

    QSharedPointer<GEP::System::FitnessOperator> fitness_operator (new GEP::System::LinearDynamicScaledFitnessOperator (&world, 1.05));
    QSharedPointer<GEP::System::SelectionOperator> selection_operator (new GEP::System::RemainderStochasticSamplingSelectionOperator (&world, fitness_operator));
    QSharedPointer<GEP::System::CrossoverOperator> crossover_operator (new GEP::System::PartiallyMatchedCrossoverOperator (&world));
    QSharedPointer<GEP::System::MutationOperator> mutation_operator (new GEP::System::SwappingMutationOperator (&world, 1.0 / NUMBER_OF_CITIES));
    QSharedPointer<GEP::System::TerminationOperator> termination_operator (new GEP::System::FixedStepTerminationOperator (&world, 1000));

    controller.setFitnessOperator (fitness_operator);
    controller.setSelectionOperator (selection_operator);
    controller.setCrossoverOperator (crossover_operator);
    controller.setMutationOperator (mutation_operator);
    controller.setTerminationOperator (termination_operator);

    //
    // Show main window and start computation
    //
    GEP::Scope::MainWindow main_window (&controller);
    main_window.show();

    return app.exec();

}
