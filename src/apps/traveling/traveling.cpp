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
#include <GEPSystemRandomNumberGenerator.h>
#include <GEPSystemSelectionOperator.h>
#include <GEPScopeMainWindow.h>

//#**************************************************************************
// Computation parameters
//#**************************************************************************

//
// Number of cities to be visited
//
const uint NUMBER_OF_CITIES = 20;

//
// Number of individuals in initial population
//
const uint POPULATION_SIZE = 100;


//#**************************************************************************
// CLASS ShuffleComparator
//#**************************************************************************

/*
 * Comparator class for shuffling a sequence
 */
class ShuffleComparator
{
public:
  ShuffleComparator (uint size);

  bool operator () (uint value1, uint value2) const;

private:
  QMap<uint, double> _order;
};

/* Constructor */
ShuffleComparator::ShuffleComparator (uint size)
{
    GEP::System::MersenneTwisterRandomNumberGenerator random_number_generator;

  for (uint i=0; i < size; ++i)
    _order.insert (i, random_number_generator.generate ());
}

/* Compare operator */
bool ShuffleComparator::operator () (uint value1, uint value2) const
{
  Q_ASSERT (value1 < static_cast<uint> (_order.size ()));
  Q_ASSERT (value2 < static_cast<uint> (_order.size ()));

  return _order[value1] < _order[value2];
}


//#**************************************************************************
// CLASS TravelingIndividual
//#**************************************************************************

/*
 * Individual: Single path
 */
typedef GEP::System::Individual<uint> TravelingIndividual;


//#**************************************************************************
// CLASS World
//#**************************************************************************

/*
 * World layout
 */
class TravelingWorld : public GEP::System::World<uint>
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
  : GEP::System::World<uint> (GEP::System::RandomNumberGeneratorPtr (new GEP::System::MersenneTwisterRandomNumberGenerator ())),
    _fitness_bias (0.0)
{
  //
  // Randomly place cities
  //
  for (uint i=0; i < number_of_cities; ++i)
    _cities.push_back (QPointF (GEP::System::World<uint>::getRandom (), GEP::System::World<uint>::getRandom ()));

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
    fitness += getDistance (individual[i], individual[i + 1]);

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
    GEP::System::Population<uint> population;

    std::vector<uint> sequence;
    for (uint i=0; i < NUMBER_OF_CITIES; ++i)
      sequence.push_back (i);

    for (uint i=0; i < POPULATION_SIZE; ++i)
      {
        std::sort (sequence.begin (), sequence.end (), ShuffleComparator (POPULATION_SIZE));
        population.add (TravelingIndividual (sequence));
      }

    //
    // Setup controller
    //
    GEP::System::SinglePopulationController<uint> controller (population);

    boost::shared_ptr< GEP::System::FitnessOperator<uint> > fitness_operator (new GEP::System::LinearDynamicScaledFitnessOperator<uint> (&world, 1.05));
    boost::shared_ptr< GEP::System::SelectionOperator<uint> > selection_operator (new GEP::System::RemainderStochasticSamplingSelectionOperator<uint> (&world, fitness_operator));
    boost::shared_ptr< GEP::System::TerminationOperator<uint> > termination_operator (new GEP::System::FixedStepTerminationOperator<uint> (&world, 100000));

    controller.setFitnessOperator (fitness_operator);
    controller.setSelectionOperator (selection_operator);
    controller.setTerminationOperator (termination_operator);

    //
    // Show main window and start computation
    //
    GEP::Scope::MainWindow main_window (&controller);
    main_window.show();

    return app.exec();
}
