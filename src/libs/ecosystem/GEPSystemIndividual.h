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
#include <QtCore/QVariant>


namespace GEP {
namespace System {

/*
 * Base class for single individuals
 */
class Individual : public Object
{
public:
    Individual (const QVariantList& genes);
    Individual (const Individual& toCopy);

    int getSize () const;

    QVariant& operator[] (int index);
    const QVariant& operator[] (int index) const;

    QString toString () const;

protected:
    QVariantList _genes;
};


}
}

#endif
