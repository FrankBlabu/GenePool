/*
 * GEPScopeMutationOperatorDisplay.h - Display for mutation steps in the current population
 *
 * Frank Cieslok, Sep. 2011
 */

#ifndef __GEP_SCOPE_MUTATION_OPERATOR_DISPLAY_H__
#define __GEP_SCOPE_MUTATION_OPERATOR_DISPLAY_H__

#include <GEPSystemObject.h>
#include "GEPScopeOperatorDisplay.h"

#include <QtCore/QMap>

namespace GEP {

namespace System {
class Controller;
}

namespace Scope {

class MutationOperatorDisplayItem;

/*
 * Display for Mutation steps in the current population
 */
class MutationOperatorDisplay : public OperatorDisplay
{
  Q_OBJECT

public:
  static const int COLUMN_ID      = 0;
  static const int COLUMN_CONTENT = 1;
  static const int COLUMN_FITNESS = 2;
  static const int COLUMN_MUTATED = 3;

public:
  MutationOperatorDisplay (System::Controller* controller, QWidget* parent);
  virtual ~MutationOperatorDisplay ();

private slots:
  void slotControllerStep ();

  void slotPreMutation (const GEP::System::Object::Id& object);
  void slotMutation (const GEP::System::Object::Id& object);

private:
  System::Controller* _controller;

  typedef QMap<System::Object::Id, MutationOperatorDisplayItem*> ItemMap;
  ItemMap _items;
};

}
}

#endif
