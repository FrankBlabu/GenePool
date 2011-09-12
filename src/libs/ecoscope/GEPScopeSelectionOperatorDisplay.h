/*
 * GEPScopeSelectionOperatorDisplay.h - Display for selection steps in the current population
 *
 * Frank Cieslok, Sep. 2011
 */

#ifndef __GEP_SCOPE_SELECTION_OPERATOR_DISPLAY_H__
#define __GEP_SCOPE_SELECTION_OPERATOR_DISPLAY_H__

#include <GEPSystemObject.h>
#include "GEPScopeOperatorDisplay.h"

#include <QtCore/QMap>

namespace GEP {

namespace System {
class Controller;
}

namespace Scope {

/*
 * Display for selection steps in the current population
 */
class SelectionOperatorDisplay : public OperatorDisplay
{
  Q_OBJECT

public:
  static const int COLUMN_ID             = 0;
  static const int COLUMN_CONTENT        = 1;
  static const int COLUMN_FITNESS        = 2;
  static const int COLUMN_TIMES_SELECTED = 3;
  static const int COLUMN_NEW_IDS        = 4;

public:
  SelectionOperatorDisplay (System::Controller* controller, QWidget* parent);
  virtual ~SelectionOperatorDisplay ();

private slots:
  void slotControllerStep ();
  void slotSelection (const System::Object::Id& before,
                      const System::Object::Id& after);

private:
  System::Controller* _controller;

  typedef QMap<System::Object::Id, QTreeWidgetItem*> ItemMap;
  ItemMap _items;
};

}
}

#endif
