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
#define DOUT(CONTENT) while (false) {}
#endif

class QPointF;
class QSizeF;
class QRectF;

/*
 * Debug output operators
 */
QDebug operator<< (QDebug out, const QPointF& point);
QDebug operator<< (QDebug out, const QSizeF& size);
QDebug operator<< (QDebug out, const QRectF& rect);

namespace GEP {
namespace System {

class Individual;
class Population;

QDebug operator<< (QDebug out, const Individual& individual);
QDebug operator<< (QDebug out, const Population& population);

}
}

#endif
