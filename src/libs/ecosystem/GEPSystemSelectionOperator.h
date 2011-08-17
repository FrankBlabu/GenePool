/*
 * GEPSystemSelectionOperator.h - Base class for selection operators
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_SELECTION_OPERATOR_H__
#define __GEP_SYSTEM_SELECTION_OPERATOR_H__

#include "GEPSystemOperator.h"
#include "GEPSystemFitnessOperator.h"
#include "GEPSystemPopulation.h"
#include "GEPSystemPopulationFitnessIndex.h"

#include <boost/shared_ptr.hpp>
#include <math.h>

#include <map>

namespace GEP {
namespace System {

//#**************************************************************************
// CLASS GEP::System::SelectionOperator
//#**************************************************************************

/*
 * Base class for selection operators
 */
template <class T>
class SelectionOperator : public Operator<T>
{
public:
  typedef boost::shared_ptr< FitnessOperator<T> > FitnessOperatorPtr;

public:
    SelectionOperator (World<T>* world, FitnessOperatorPtr fitness_operator);
    virtual ~SelectionOperator ();

    virtual void compute (const Population<T>& source, Population<T>* target) const = 0;

protected:
    FitnessOperatorPtr _fitness_operator;
};

/* Constructor */
template <class T>
SelectionOperator<T>::SelectionOperator (World<T>* world, FitnessOperatorPtr fitness_operator)
  : Operator<T>       (world),
    _fitness_operator (fitness_operator)
{
}

/* Destructor */
template <class T>
SelectionOperator<T>::~SelectionOperator ()
{
}


//#**************************************************************************
// CLASS GEP::System::RemainderStochasticSamplingSelectionOperator
//#**************************************************************************

/*
 * Selection operator based on remainder stochastic sampling
 */
template <class T>
class RemainderStochasticSamplingSelectionOperator : public SelectionOperator<T>
{
public:
    RemainderStochasticSamplingSelectionOperator (World<T>* world, typename SelectionOperator<T>::FitnessOperatorPtr fitness_operator);
    virtual ~RemainderStochasticSamplingSelectionOperator ();

    virtual void compute (const Population<T>& source, Population<T>* target) const;
};

/* Constructor */
template <class T>
RemainderStochasticSamplingSelectionOperator<T>::RemainderStochasticSamplingSelectionOperator (World<T>* world, typename SelectionOperator<T>::FitnessOperatorPtr fitness_operator)
  : SelectionOperator<T> (world, fitness_operator)
{
}

/* Destructor */
template <class T>
RemainderStochasticSamplingSelectionOperator<T>::~RemainderStochasticSamplingSelectionOperator ()
{
}

/* Perform selection */
template <class T>
void RemainderStochasticSamplingSelectionOperator<T>::compute (const Population<T>& source, Population<T>* target) const
{
  Q_UNUSED (target);

  //
  // Compute individual fitness and fitness sum
  //
  typedef std::map<Object::Id, double> FitnessMap;
  FitnessMap fitness_map;

  double fitness_sum = 0.0;
  for (typename Population<T>::ConstIterator i = source.begin (); i != source.end (); ++i)
    {
      const Individual<T>& individual = *i;

      double fitness = SelectionOperator<T>::_fitness_operator->compute (individual);

      fitness_map.insert (std::make_pair (individual.getId (), fitness));
      fitness_sum += fitness;
    }

  //
  // Step 1: Insert individuals according to their relativ selection probability
  //
  for (typename Population<T>::ConstIterator i = source.begin (); i != source.end (); ++i)
    {
      const Individual<T>& individual = *i;

      double p = fitness_map[individual.getId ()] / fitness_sum;
      uint n = static_cast<uint> (floor (p * source.getSize ()));

      fitness_map[individual.getId ()] = p * source.getSize () - floor (p * source.getSize ());

      for (uint i=0; i < n; ++i)
        target->add (Individual<T> (individual));
    }

  //
  // Step 2: The remaining space in the target population is filled using roulette wheel selection
  //
  fitness_sum = 0.0;
  for (FitnessMap::const_iterator i = fitness_map.begin (); i != fitness_map.end (); ++i)
    fitness_sum += i->second;

  PopulationFitnessIndex<T> fitness_index (source, fitness_map);

  while (source.getSize () > target->getSize ())
    {
      double value = Operator<T>::_world->getRandom ();

      double sum = 0.0;
      bool found = false;
      for (uint i=0; i < fitness_index.getSize () && !found; ++i)
        {
          const Individual<T>& individual = fitness_index.getIndividual (i);

          FitnessMap::const_iterator pos = fitness_map.find (individual.getId ());
          Q_ASSERT (pos != fitness_map.end ());

          sum += pos->second / fitness_sum;

          if (value <= sum)
            {
              target->add (individual);
              found = true;
            }
        }

      Q_ASSERT (found);
    }

}

}
}

#endif
