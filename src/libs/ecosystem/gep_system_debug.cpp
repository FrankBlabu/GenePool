/*
 * gep_system_debug.cpp - Debug functions for GenePool classes
 *
 * Frank Cieslok, Aug. 2011
 */

#include "GEPSystemDebug.h"
#include "GEPSystemIndividual.h"
#include "GEPSystemPopulation.h"

#include <QtCore/QPointF>
#include <QtCore/QSizeF>
#include <QtCore/QRectF>

/*
 * Print point
 */
QDebug operator<< (QDebug out, const QPointF& point)
{
  out.nospace () << "(" << point.x () << ", " << point.y () << ")";
  return out;
}

/*
 * Print size
 */
QDebug operator<< (QDebug out, const QSizeF& size)
{
  out.nospace () << "(" << size.width () << ", " << size.height () << ")";
  return out;
}

/*
 * Print rectangle
 */
QDebug operator<< (QDebug out, const QRectF& rect)
{
  out.nospace () << "[" << rect.topLeft () << ", " << rect.bottomRight () << "]";
  return out;
}

namespace GEP {
namespace System {

/*
 * Print single individual
 */
QDebug operator<< (QDebug out, const Individual& individual)
{
  QVector<Individual::Gene> alleles;
  for (int i=0; i < individual.getSize (); ++i)
    alleles.append (individual[i]);

  out.nospace () << "Individual {" << alleles << "}";
  return out;
}

/*
 * Print population
 */
QDebug operator<< (QDebug out, const Population& population)
{
  out.nospace () << "Population {\n";

  for (Population::ConstIterator i = population.begin (); i != population.end (); ++i)
    out << *i << "\n";

  out << "}\n";

  return out;
}

}
}
