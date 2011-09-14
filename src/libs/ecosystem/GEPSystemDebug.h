/*
 * GEPSystemDebug.h - Debug functions for GenePool classes
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_DEBUG_H__
#define __GEP_SYSTEM_DEBUG_H__

#include <QtDebug>

#ifdef GEP_DEBUG
#define DOUT(CONTENT) (qDebug () << CONTENT)
#else
#define DOUT(CONTENT)
#endif

namespace GEP {
namespace System {

class Individual;
class Population;

/*
 * Debug output operators
 */
QDebug operator<< (QDebug out, const Individual& individual);
QDebug operator<< (QDebug out, const Population& population);

}
}

#endif
