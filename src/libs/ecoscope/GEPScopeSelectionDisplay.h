/*
 * GEPSelectionDisplay.h - Display for selection steps in the current population
 *
 * Frank Cieslok, Sep. 2011
 */

#ifndef __GEP_SCOPE_SELECTION_DISPLAY_H__
#define __GEP_SCOPE_SELECTION_DISPLAY_H__

#include <GEPSystemObject.h>

#include <QtCore/QMap>
#include <QtGui/QTreeWidget>

namespace GEP {

namespace System {
class Controller;
}

namespace Scope {

/*
 * Display for selection steps in the current population
 */
class SelectionDisplay : public QTreeWidget
{
  Q_OBJECT

public:
  static const int COLUMN_ID               = 0;
  static const int COLUMN_CONTENT          = 1;
  static const int COLUMN_FITNESS_WORLD    = 2;
  static const int COLUMN_FITNESS_OPERATOR = 3;
  static const int COLUMN_TIMES_SELECTED   = 4;
  static const int COLUMN_NEW_IDS          = 5;

public:
  SelectionDisplay (System::Controller* controller, QWidget* parent);
  virtual ~SelectionDisplay ();

private slots:
  void slotControllerStep ();
  void slotIndividualSelection (const System::Object::Id& before,
                                const System::Object::Id& after);

private:
  System::Controller* _controller;

  typedef QMap<System::Object::Id, QTreeWidgetItem*> ItemMap;
  ItemMap _items;
};

}
}

#endif
