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
class MutationNotification;
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
  static const int COLUMN_ID             = 0;
  static const int COLUMN_BEFORE         = 1;
  static const int COLUMN_FITNESS_BEFORE = 2;
  static const int COLUMN_AFTER          = 3;
  static const int COLUMN_FITNESS_AFTER  = 4;

public:
  MutationOperatorDisplay (System::Controller* controller, QWidget* parent);
  virtual ~MutationOperatorDisplay ();

private slots:
  void slotControllerStep ();

  void slotMutation (const GEP::System::MutationNotification& notification);

private:
  System::Controller* _controller;
};

}
}

#endif
