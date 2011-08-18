/*
 * GEPSystemCrossoverOperator.h - Base class for crossover operators
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_CROSSOVER_OPERATOR_H__
#define __GEP_SYSTEM_CROSSOVER_OPERATOR_H__

#include "GEPSystemOperator.h"
#include "GEPSystemPopulation.h"
#include "GEPSystemShuffleComparator.h"
#include "GEPSystemDebug.h"

#include <algorithm>
#include <vector>

namespace GEP {
namespace System {

//#**************************************************************************
// CLASS GEP::System::CrossoverOperator
//#**************************************************************************

/*
 * Base class for Crossover operators
 */
template <class T>
class CrossoverOperator : public Operator<T>
{
public:
    CrossoverOperator (World<T>* world);
    virtual ~CrossoverOperator () {}

    virtual void compute (Population<T>& population) = 0;
};

/* Constructor */
template <class T>
CrossoverOperator<T>::CrossoverOperator (World<T>* world)
  : Operator<T> (world)
{
}

//#**************************************************************************
// CLASS GEP::System::PartiallyMatchedCrossoverOperator
//#**************************************************************************

/*
 * Base class for Crossover operators
 */
template <class T>
class PartiallyMatchedCrossoverOperator : public CrossoverOperator<T>
{
public:
    PartiallyMatchedCrossoverOperator (World<T>* world);
    virtual ~PartiallyMatchedCrossoverOperator () {}

    virtual void compute (Population<T>& population);
};

/* Constructor */
template <class T>
PartiallyMatchedCrossoverOperator<T>::PartiallyMatchedCrossoverOperator (World<T>* world)
  : CrossoverOperator<T> (world)
{
}

/*
 * Compute crossover set */
template <class T>
void PartiallyMatchedCrossoverOperator<T>::compute (Population<T>& population)
{
  //
  // Shuffle population index for random crossover pairs
  //
  std::vector<uint> shuffled_index;
  for (uint i=0; i < population.getSize (); ++i)
    shuffled_index.push_back (i);

  std::sort (shuffled_index.begin (), shuffled_index.end (), ShuffleComparator<uint> (Operator<T>::_world));

  //
  // Crossover of individual pairs
  //
  for (uint i=0; i < population.getSize () / 2; ++i)
    {
      Individual<T>& individual1 = population[shuffled_index[i * 2]];
      Individual<T>& individual2 = population[shuffled_index[i * 2 + 1]];

      Q_ASSERT (individual1.getSize () == individual2.getSize ());
      Q_ASSERT (individual1.getSize () > 2);

      uint size = individual1.getSize ();

      uint index1 = static_cast<uint> (floor (Operator<T>::_world->getRandom () * size)) % size;
      uint index2 = index1 + 1 + static_cast<uint> (floor (Operator<T>::_world->getRandom () * (size - 2))) % (size - 2);

      typedef std::map<T, T> IndexMap;
      IndexMap indices1;
      IndexMap indices2;

      for (uint j = index1; j <= index2; ++j)
        {
          const T& allel1 = individual1[j % size];
          const T& allel2 = individual2[j % size];

          indices1.insert (std::make_pair (allel2, allel1));
          indices2.insert (std::make_pair (allel1, allel2));

          std::swap (individual1[j % size], individual2[j % size]);
        }

      for (uint j=index2+1; j % size > index2 || j % size < index1; ++j)
        {
          uint pos = j % size;

          T value1 = individual1[pos];
          T value2 = individual2[pos];

          for (typename IndexMap::const_iterator s = indices1.find (value1); s != indices1.end (); s = indices1.find (value1))
            value1 = s->second;

          for (typename IndexMap::const_iterator s = indices2.find (value2); s != indices2.end (); s = indices2.find (value2))
            value2 = s->second;

          individual1[pos] = value1;
          individual2[pos] = value2;
        }
    }
}

}
}

#endif
