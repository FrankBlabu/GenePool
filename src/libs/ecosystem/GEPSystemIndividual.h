/*
 * GEPSystemIndividual.h - Base class for single individuals
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_INDIVIDUAL_H__
#define __GEP_SYSTEM_INDIVIDUAL_H__

#include "GEPSystemObject.h"

#include <QtGlobal>
#include <QtCore/QList>
#include <QtCore/QMetaType>


namespace GEP {
namespace System {

/*
 * Base class for single individuals
 */
class Individual : public Object
{
public:
  typedef int Gene;
  typedef QList<Gene> Chromosome;

public:
    Individual (const Chromosome& chromosome);
    Individual (const Individual& toCopy);

    int getNumberOfGenes () const;
    const Chromosome& getChromosome () const;

    Gene& operator[] (int index);
    Gene operator[] (int index) const;

protected:
    Chromosome _chromosome;
};


}
}

#endif
