/*
 * GEPScopeFitnessStatisticsDialog.h - Dialog displaying the fitness statistics
 *
 * Frank Cieslok, Sep 2011
 */

#ifndef __GEP_SCOPE_FITNESS_STATISTICS_DIALOG_H__
#define __GEP_SCOPE_FITNESS_STATISTICS_DIALOG_H__

#include <QtGui/QDialog>

class QAbstractButton;

namespace GEP {

namespace System {
class Controller;
}

namespace Scope {

class FitnessStatisticsDialogContent;
class FitnessStatisticsDiagram;

/*
 * Dialog displaying the fitness statistics
 */
class FitnessStatisticsDialog : public QDialog
{
    Q_OBJECT

public:
  FitnessStatisticsDialog (const System::Controller* controller, QWidget* parent);
  virtual ~FitnessStatisticsDialog ();

private:
  FitnessStatisticsDialogContent* _content;
  FitnessStatisticsDiagram* _diagram;
};

}
}

#endif
