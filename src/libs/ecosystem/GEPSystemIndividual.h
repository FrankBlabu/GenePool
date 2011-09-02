/*
 * GEPSystemIndividual.h - Base class for single individuals
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_INDIVIDUAL_H__
#define __GEP_SYSTEM_INDIVIDUAL_H__

#include "GEPSystemObject.h"

#include <vector>

#include <QtGlobal>
#include <QtCore/QVariant>


namespace GEP {
namespace System {

/*
 * Base class for single individuals
 */
class Individual : public Object
{
public:
    Individual (const std::vector<QVariant>& genes);
    Individual (const Individual& toCopy);

    uint getSize () const;

    QVariant& operator[] (uint index);
    const QVariant& operator[] (uint index) const;

protected:
    std::vector<QVariant> _genes;
};


}
}

#endif
