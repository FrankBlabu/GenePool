/*
 * GEPScopeOperatorDisplay.h - Base class for all operator display classes
 *
 * Frank Cieslok, Sep. 2011
 */

#ifndef __GEP_SCOPE_OPERATOR_DISPLAY_H__
#define __GEP_SCOPE_OPERATOR_DISPLAY_H__

#include <QtGui/QTreeWidget>

namespace GEP {
namespace Scope {

/*
 * Base class for all operator display classes
 */
class OperatorDisplay : public QTreeWidget
{
  Q_OBJECT

public:
  OperatorDisplay (QWidget* parent);
  virtual ~OperatorDisplay ();
};

}
}

#endif
