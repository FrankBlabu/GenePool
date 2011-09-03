/*
 * gep_system_crossover_operator.cpp - Base class for crossover operators
 *
 * Frank Cieslok, Aug. 2011
 */

#include "GEPSystemCrossoverOperator.h"
#include "GEPSystemWorld.h"

namespace GEP {
namespace System {

#include <QtCore/QHash>
#include <math.h>



//#**************************************************************************
// CLASS GEP::System::CrossoverOperator
//#**************************************************************************

/* Constructor */
CrossoverOperator::CrossoverOperator (World* world)
  : Operator (world)
{
}

/* Destructor */
CrossoverOperator::~CrossoverOperator ()
{
}


//#**************************************************************************
// CLASS GEP::System::PartiallyMatchedCrossoverOperator
//#**************************************************************************

/* Constructor */
PartiallyMatchedCrossoverOperator::PartiallyMatchedCrossoverOperator (World* world)
  : CrossoverOperator (world)
{
}

/* Destructor */
PartiallyMatchedCrossoverOperator::~PartiallyMatchedCrossoverOperator ()
{
}

/*
 * Compute crossover set
*/
void PartiallyMatchedCrossoverOperator::compute (Population& population)
{
  //
  // Shuffle population index for random crossover pairs
  //
  std::vector<uint> shuffled_index;
  for (uint i=0; i < population.getSize (); ++i)
    shuffled_index.push_back (i);

  ShuffleComparator<uint> comparator (_world, shuffled_index);
  std::sort (shuffled_index.begin (), shuffled_index.end (), comparator);

  //
  // Crossover of individual pairs
  //
  for (uint i=0; i < population.getSize () / 2; ++i)
    {
      Individual& individual1 = population[shuffled_index[i * 2]];
      Individual& individual2 = population[shuffled_index[i * 2 + 1]];

      Q_ASSERT (individual1.getSize () == individual2.getSize ());
      Q_ASSERT (individual1.getSize () > 2);

      uint size = individual1.getSize ();

      uint index1 = static_cast<uint> (floor (_world->getRandom () * size)) % size;
      uint index2 = index1 + 1 + static_cast<uint> (floor (_world->getRandom () * (size - 2))) % (size - 2);

      typedef QHash<QVariant, QVariant> IndexMap;
      IndexMap indices1;
      IndexMap indices2;

      for (uint j = index1; j <= index2; ++j)
        {
          const QVariant& allel1 = individual1[j % size];
          const QVariant& allel2 = individual2[j % size];

          indices1.insert (allel2, allel1);
          indices2.insert (allel1, allel2);

          std::swap (individual1[j % size], individual2[j % size]);
        }

      for (uint j=index2+1; j % size > index2 || j % size < index1; ++j)
        {
          uint pos = j % size;

          QVariant value1 = individual1[pos];
          QVariant value2 = individual2[pos];

          for (IndexMap::const_iterator s = indices1.find (value1); s != indices1.end (); s = indices1.find (value1))
            value1 = s.value ();

          for (IndexMap::const_iterator s = indices2.find (value2); s != indices2.end (); s = indices2.find (value2))
            value2 = s.value ();

          individual1[pos] = value1;
          individual2[pos] = value2;
        }
    }
}


}
}
