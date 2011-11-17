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
  static const int COLUMN_MATE1_ID            = 0;
  static const int COLUMN_MATE1_INDIVIDUAL    = 1;
  static const int COLUMN_MATE1_FITNESS       = 2;
  static const int COLUMN_MATE2_ID            = 3;
  static const int COLUMN_MATE2_INDIVIDUAL    = 4;
  static const int COLUMN_MATE2_FITNESS       = 5;
  static const int COLUMN_CROSSED1_INDIVIDUAL = 6;
  static const int COLUMN_CROSSED2_INDIVIDUAL = 7;

public:
  CrossoverOperatorDisplay (System::Controller* controller, QWidget* parent);
  virtual ~CrossoverOperatorDisplay ();

private slots:
  void slotReset ();
  void slotCrossover (const GEP::System::CrossoverNotificationList& notifications);

private:
  System::Controller* _controller;
};

}
}

#endif
