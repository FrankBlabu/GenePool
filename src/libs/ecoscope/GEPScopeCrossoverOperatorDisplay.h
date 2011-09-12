/*
 * GEPScopeCrossoverOperatorDisplay.h - Display for crossover steps in the current population
 *
 * Frank Cieslok, Sep. 2011
 */

#ifndef __GEP_SCOPE_CROSSOVER_OPERATOR_DISPLAY_H__
#define __GEP_SCOPE_CROSSOVER_OPERATOR_DISPLAY_H__

#include <GEPSystemObject.h>
#include "GEPScopeOperatorDisplay.h"

#include <QtCore/QMap>

namespace GEP {

namespace System {
class Controller;
}

namespace Scope {

class CrossoverOperatorDisplayItem;

/*
 * Display for crossover steps in the current population
 */
class CrossoverOperatorDisplay : public OperatorDisplay
{
  Q_OBJECT

public:
  static const int COLUMN_ID             = 0;
  static const int COLUMN_CONTENT        = 1;
  static const int COLUMN_MATE           = 2;
  static const int COLUMN_FITNESS_BEFORE = 3;
  static const int COLUMN_CROSSED        = 4;
  static const int COLUMN_FITNESS_AFTER  = 5;

public:
  CrossoverOperatorDisplay (System::Controller* controller, QWidget* parent);
  virtual ~CrossoverOperatorDisplay ();

private slots:
  void slotControllerStep ();

  void slotPreCrossover (const System::Object::Id& object1,
                         const System::Object::Id& object2);
  void slotCrossover (const System::Object::Id& object1,
                      const System::Object::Id& object2);

private:
  CrossoverOperatorDisplayItem* getItem (const System::Object::Id& id);

  void setupItem(const System::Object::Id& object1,
                 const System::Object::Id& object2);
  void completeItem (const System::Object::Id& object);

private:
  System::Controller* _controller;

  typedef QMap<System::Object::Id, CrossoverOperatorDisplayItem*> ItemMap;
  ItemMap _items;
};

}
}

#endif
