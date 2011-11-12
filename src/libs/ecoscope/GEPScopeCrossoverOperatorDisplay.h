/*
 * GEPScopeCrossoverOperatorDisplay.h - Display for crossover steps in the current population
 *
 * Frank Cieslok, Sep. 2011
 */

#ifndef __GEP_SCOPE_CROSSOVER_OPERATOR_DISPLAY_H__
#define __GEP_SCOPE_CROSSOVER_OPERATOR_DISPLAY_H__

#include <GEPSystemObject.h>
#include <GEPSystemNotifier.h>
#include "GEPScopeOperatorDisplay.h"

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
  void slotControllerStep (const GEP::System::ControllerStepNotification& notification);
  void slotCrossover (const GEP::System::CrossoverNotificationList& notifications);

private:
  System::Controller* _controller;
};

}
}

#endif
