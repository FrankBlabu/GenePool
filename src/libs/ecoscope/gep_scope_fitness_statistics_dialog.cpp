/*
 * gep_scope_fitness_statistics_dialog.cpp - Dialog displaying the fitness statistics
 *
 * Frank Cieslok, Sep 2011
 */

#define GEP_DEBUG

#include "GEPScopeFitnessStatisticsDialog.h"
#include "GEPScopeTools.h"

#include <GEPSystemController.h>
#include <GEPSystemDebug.h>

#include <QtGui/QDialogButtonBox>
#include <QtGui/QPainter>

#include "ui_gep_scope_fitness_statistics_dialog.h"

namespace GEP {
namespace Scope {

//#**************************************************************************
// CLASS GEP::Scope::FitnessStatisticsDiagram
//#**************************************************************************

/*
 * Frame displaying the fitness statistics
 */
class FitnessStatisticsDiagram : public QWidget
{
public:
  FitnessStatisticsDiagram (QWidget* parent);
  virtual ~FitnessStatisticsDiagram ();

protected:
  virtual void paintEvent (QPaintEvent* event);
};

/* Constructor */
FitnessStatisticsDiagram::FitnessStatisticsDiagram (QWidget* parent)
  : QWidget (parent)
{
}

/* Destructor */
FitnessStatisticsDiagram::~FitnessStatisticsDiagram ()
{
}

/* Paint diagram */
void FitnessStatisticsDiagram::paintEvent (QPaintEvent* event)
{
  QWidget::paintEvent (event);

  QPainter painter (this);
  painter.fillRect (rect (), Qt::white);
}


//#**************************************************************************
// CLASS GEP::Scope::FitnessStatisticsDialogContent
//#**************************************************************************

/*
 * Dialog content
 */
class FitnessStatisticsDialogContent : public QWidget, public Ui::FitnessStatisticsDialog
{
public:
  FitnessStatisticsDialogContent (QWidget* parent);
  virtual ~FitnessStatisticsDialogContent ();
};

/* Constructor */
FitnessStatisticsDialogContent::FitnessStatisticsDialogContent (QWidget* parent)
  : QWidget (parent)
{
  setupUi (this);
}

/* Destructor */
FitnessStatisticsDialogContent::~FitnessStatisticsDialogContent ()
{
}


//#**************************************************************************
// CLASS GEP::Scope::FitnessStatisticsDialog
//#**************************************************************************

/* Constructor */
FitnessStatisticsDialog::FitnessStatisticsDialog (const System::Controller* controller, QWidget* parent)
  : QDialog (parent),
    _content (0),
    _diagram (0)
{
  Q_UNUSED (controller);

  setWindowTitle ("Fitness function statistics");

  _content = Tools::addWidgetToParent (new FitnessStatisticsDialogContent (this));
  _diagram = Tools::addWidgetToParent (new FitnessStatisticsDiagram (_content->_frame));

  connect (_content->_buttons, SIGNAL (rejected ()), SLOT (reject ()));
}

/* Destructor */
FitnessStatisticsDialog::~FitnessStatisticsDialog ()
{
}

}
}

