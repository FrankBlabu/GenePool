/*
 * gep_scope_crossover_operator_display.cpp - Display for crossover steps of the current population
 *
 * Frank Cieslok, Sep. 2011
 */

#include "GEPScopeCrossoverOperatorDisplay.h"
#include "GEPScopeTools.h"
#include "GEPSystemController.h"
#include "GEPSystemNotifier.h"
#include "GEPSystemWorld.h"

#include <QtGui/QHeaderView>

namespace GEP {
namespace Scope {

//#**************************************************************************
// CLASS GEP::Scope::CrossoverOperatorDisplayItem
//#**************************************************************************

/*
 * Item for the crossover display
 */
class CrossoverOperatorDisplayItem : public OperatorDisplayItem
{
public:
  CrossoverOperatorDisplayItem (const System::Object::Id& id, QTreeWidget* widget);
  virtual ~CrossoverOperatorDisplayItem ();

  virtual bool operator< (const QTreeWidgetItem& other) const;
};

/* Constructor */
CrossoverOperatorDisplayItem::CrossoverOperatorDisplayItem (const System::Object::Id& id, QTreeWidget* widget)
  : OperatorDisplayItem (id, widget)
{
}

/* Destructor */
CrossoverOperatorDisplayItem::~CrossoverOperatorDisplayItem ()
{
}

/* Comparison operator for item sorting */
bool CrossoverOperatorDisplayItem::operator< (const QTreeWidgetItem& other) const
{
  bool less = false;

  int column = treeWidget ()->sortColumn ();

  switch (column)
    {
    case CrossoverOperatorDisplay::COLUMN_ID:
    case CrossoverOperatorDisplay::COLUMN_CONTENT:
    case CrossoverOperatorDisplay::COLUMN_MATE:
    case CrossoverOperatorDisplay::COLUMN_CROSSED:
      less = text (column) < other.text (column);
      break;

    case CrossoverOperatorDisplay::COLUMN_FITNESS_BEFORE:
    case CrossoverOperatorDisplay::COLUMN_FITNESS_AFTER:
      less = text (column).toDouble () < other.text (column).toDouble ();
      break;
    }

  return less;
}


//#**************************************************************************
// CLASS GEP::Scope::CrossoverOperatorDisplay
//#**************************************************************************

/* Constructor */
CrossoverOperatorDisplay::CrossoverOperatorDisplay (System::Controller* controller, QWidget* parent)
  : OperatorDisplay (controller, parent)
{
  System::Notifier* notifier = System::Notifier::getNotifier ();

  QStringList header_names;
  header_names.push_back ("Id");
  header_names.push_back ("Content");
  header_names.push_back ("Mate");
  header_names.push_back ("Fitness (before)");
  header_names.push_back ("Crossed");
  header_names.push_back ("Fitness (after)");

  setHeaderLabels (header_names);

  header ()->setResizeMode (COLUMN_ID, QHeaderView::ResizeToContents);
  header ()->setResizeMode (COLUMN_CONTENT, QHeaderView::Stretch);
  header ()->setResizeMode (COLUMN_MATE, QHeaderView::ResizeToContents);
  header ()->setResizeMode (COLUMN_FITNESS_BEFORE, QHeaderView::ResizeToContents);
  header ()->setResizeMode (COLUMN_CROSSED, QHeaderView::Stretch);
  header ()->setResizeMode (COLUMN_FITNESS_AFTER, QHeaderView::ResizeToContents);

  connect (notifier, SIGNAL (signalControllerStep ()), SLOT (slotControllerStep ()));
  connect (notifier, SIGNAL (signalCrossover (GEP::System::CrossoverNotification)),
           SLOT (slotCrossover (const GEP::System::CrossoverNotification&)));
}

/* Destructor */
CrossoverOperatorDisplay::~CrossoverOperatorDisplay ()
{
}

/*
 * Slot called when the controller advances one step
 */
void CrossoverOperatorDisplay::slotControllerStep ()
{
  clear ();
}

/*
 * A crossover operation has been performed
 */
void CrossoverOperatorDisplay::slotCrossover (const System::CrossoverNotification& notification)
{
  CrossoverOperatorDisplayItem* item1 = new CrossoverOperatorDisplayItem (notification.getBeforeFirst ().getId (), this);
  addTopLevelItem (item1);

  item1->setText (COLUMN_ID, QString::number (notification.getBeforeFirst ().getId ()));
  item1->setText (COLUMN_CONTENT, notification.getBeforeFirst ().getRepresentation ());
  item1->setText (COLUMN_MATE, QString::number (notification.getBeforeSecond ().getId ()));
  item1->setText (COLUMN_FITNESS_BEFORE, QString::number (notification.getBeforeFirst ().getFitness ()));
  item1->setText (COLUMN_CROSSED, notification.getAfterFirst ().getRepresentation ());
  item1->setText (COLUMN_FITNESS_AFTER, QString::number (notification.getAfterFirst ().getFitness (), 'g', 2));

  CrossoverOperatorDisplayItem* item2 = new CrossoverOperatorDisplayItem (notification.getBeforeSecond ().getId (), this);
  addTopLevelItem (item2);

  item2->setText (COLUMN_ID, QString::number (notification.getBeforeSecond ().getId ()));
  item2->setText (COLUMN_CONTENT, notification.getBeforeSecond ().getRepresentation ());
  item2->setText (COLUMN_MATE, QString::number (notification.getBeforeFirst ().getId ()));
  item2->setText (COLUMN_FITNESS_BEFORE, QString::number (notification.getBeforeSecond ().getFitness ()));
  item2->setText (COLUMN_CROSSED, notification.getAfterSecond ().getRepresentation ());
  item2->setText (COLUMN_FITNESS_AFTER, QString::number (notification.getAfterSecond ().getFitness (), 'g', 2));
}

}
}
