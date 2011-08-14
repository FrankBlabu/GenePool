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
#include <GEPScopeMainWindow.h>

namespace {

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
  ShuffleComparator (GEP::System::RandomNumberGeneratorPtr random_number_generator, uint size);

  bool operator () (uint value1, uint value2) const;

private:
  QMap<uint, double> _order;
};

/* Constructor */
ShuffleComparator::ShuffleComparator (GEP::System::RandomNumberGeneratorPtr random_number_generator, uint size)
{
  for (uint i=0; i < size; ++i)
    _order.insert (i, random_number_generator->generate ());
}

/* Compare operator */
bool ShuffleComparator::operator () (uint value1, uint value2) const
{
  Q_ASSERT (value1 < static_cast<uint> (_order.size ()));
  Q_ASSERT (value2 < static_cast<uint> (_order.size ()));

  return _order[value1] < _order[value2];
}


//#**************************************************************************
// CLASS World
//#**************************************************************************

/*
 * World layout
 */
class World
{
public:
  World (GEP::System::RandomNumberGeneratorPtr random_number_generator, uint number_of_cities);

  uint getSize () const;

  const QPointF& operator[] (uint index) const;

private:
  std::vector<QPointF> _cities;
};

/* Constructor */
World::World (GEP::System::RandomNumberGeneratorPtr random_number_generator, uint number_of_cities)
{
  for (uint i=0; i < number_of_cities; ++i)
    _cities.push_back (QPointF (random_number_generator->generate (), random_number_generator->generate ()));
}

/* Return number of cities */
uint World::getSize () const
{
  return _cities.size ();
}

/* Return city coordinate */
const QPointF& World::operator[] (uint index) const
{
  Q_ASSERT (index < _cities.size ());
  return _cities[index];
}


//#**************************************************************************
// CLASS TravelingIndividual
//#**************************************************************************

/*
 * Individual: Single path
 */
typedef GEP::System::Individual<uint> TravelingIndividual;

//#**************************************************************************
// CLASS TravelingFitnessOperator
//#**************************************************************************

/*
 * Fitness function operator for a TravelingIndividual
 */
template <class T>
class TravelingFitnessOperator : public GEP::System::LinearDynamicScaledFitnessOperator<T>
{
public:
  TravelingFitnessOperator (const World* world);
  virtual ~TravelingFitnessOperator ();

protected:
  virtual double getFitness (const GEP::System::Individual<T>& individual) const;

private:
  double getDistance (uint city1, uint city2) const;

private:
  const World* _world;
  double _bias;
};

/* Constructor */
template <class T>
TravelingFitnessOperator<T>::TravelingFitnessOperator (const World* world)
  : GEP::System::LinearDynamicScaledFitnessOperator<T> (1.05),
    _world (world),
    _bias  (0.0)
{
  //
  // Compute largest city distance to get a fitness bias
  //
  double max_distance = 0.0;

  for (uint i=0; i < _world->getSize (); ++i)
    for (uint j=i+1; j < _world->getSize (); ++j)
      max_distance = std::max (max_distance, getDistance (i, j));

  _bias = _world->getSize () * max_distance;
}

/* Destructor */
template <class T>
TravelingFitnessOperator<T>::~TravelingFitnessOperator ()
{
}

/* Compute fitness for a single individual */
template <class T>
double TravelingFitnessOperator<T>::getFitness (const GEP::System::Individual<T>& individual) const
{
  double fitness = 0.0;

  for (uint i=0; i + 1 < individual.getNumberOfGenes (); ++i)
    fitness += getDistance (individual[i], individual[i + 1]);

  return _bias - fitness;
}

/* Compute distance between two cities */
template <class T>
double TravelingFitnessOperator<T>::getDistance (uint city1, uint city2) const
{
  return ((*_world)[city2] - (*_world)[city1]).manhattanLength ();
}

}


//#**************************************************************************
// MAIN
//#**************************************************************************

int main(int argc, char *argv[])
{
    QApplication app (argc, argv);

    GEP::System::RandomNumberGeneratorPtr random_number_generator (new GEP::System::MersenneTwisterRandomNumberGenerator ());

    //
    // Create world
    //
    World world (random_number_generator, NUMBER_OF_CITIES);
    GEP::System::Population<uint> population;

    QList<uint> sequence;
    for (uint i=0; i < NUMBER_OF_CITIES; ++i)
      sequence.push_back (i);

    for (uint i=0; i < POPULATION_SIZE; ++i)
      {
        std::sort (sequence.begin (), sequence.end (), ShuffleComparator (random_number_generator, POPULATION_SIZE));
        population.add (TravelingIndividual (sequence));
      }

    //
    // Setup controller
    //
    GEP::System::SinglePopulationController<uint> controller (population);
    controller.setFitnessOperator (boost::shared_ptr< GEP::System::FitnessOperator<uint> > (new TravelingFitnessOperator<uint> (&world)));
    controller.setTerminationOperator (boost::shared_ptr< GEP::System::TerminationOperator<uint> > (new GEP::System::FixedStepTerminationOperator<uint> (100000)));

    //
    // Show main window and start computation
    //
    GEP::Scope::MainWindow main_window (&controller);
    main_window.show();

    return app.exec();
}
