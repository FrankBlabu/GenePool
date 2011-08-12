/*
 * GEPScopeTools.h - Tools for the GenePool scope library
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SCOPE_TOOLS_H__
#define __GEP_SCOPE_TOOLS_H__

#include <QtGui/QBoxLayout>

namespace GEP {
namespace Scope {

/*
 * Tools for the GenePool scope library
 */
namespace Tools
{

/*
 * Add widget to parent so that it fills the whole layout
 */
template <class T>
T* addWidgetToParent (T* widget)
{
  Q_ASSERT (widget != 0);
  Q_ASSERT (widget->parent () != 0);
  Q_ASSERT (dynamic_cast<QWidget*> (widget->parent ()) != 0);

  QBoxLayout* layout = new QHBoxLayout (dynamic_cast<QWidget*> (widget->parent ()));
  layout->setMargin (0);
  layout->setSpacing (0);
  layout->addWidget  (widget);

  return widget;
}

}

}
}

#endif
