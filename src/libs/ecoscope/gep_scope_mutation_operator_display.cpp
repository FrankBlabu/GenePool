/*
 * gep_scope_mutation_operator_display.cpp - Display for mutation steps of the current population
 *
 * Frank Cieslok, Sep. 2011
 */

#include "GEPScopeMutationOperatorDisplay.h"
#include "GEPScopeTools.h"
#include "GEPSystemController.h"
#include "GEPSystemNotifier.h"
#include "GEPSystemWorld.h"

#include <QtGui/QHeaderView>

namespace GEP {
namespace Scope {

//#**************************************************************************
// CLASS GEP::Scope::MutationOperatorDisplayItem
//#**************************************************************************

/*
 * Item for the selection display
 */
class MutationOperatorDisplayItem : public OperatorDisplayItem
{
public:
  MutationOperatorDisplayItem (const System::Object::Id& id, QTreeWidget* widget);
  virtual ~MutationOperatorDisplayItem ();

  virtual bool operator< (const QTreeWidgetItem& other) const;
};

/* Constructor */
MutationOperatorDisplayItem::MutationOperatorDisplayItem (const System::Object::Id& id, QTreeWidget* widget)
  : OperatorDisplayItem (id, widget)
{
}

/* Destructor */
MutationOperatorDisplayItem::~MutationOperatorDisplayItem ()
{
}

/* Comparison operator for item sorting */
bool MutationOperatorDisplayItem::operator< (const QTreeWidgetItem& other) const
{
  bool less = false;

  int column = treeWidget ()->sortColumn ();

  switch (column)
    {
    case MutationOperatorDisplay::COLUMN_ID:
    case MutationOperatorDisplay::COLUMN_BEFORE:
    case MutationOperatorDisplay::COLUMN_AFTER:
      less = text (column) < other.text (column);
      break;

    case MutationOperatorDisplay::COLUMN_FITNESS_BEFORE:
    case MutationOperatorDisplay::COLUMN_FITNESS_AFTER:
      less = text (column).toDouble () < other.text (column).toDouble ();
      break;
    }

  return less;
}


//#**************************************************************************
// CLASS GEP::Scope::MutationOperatorDisplay
//#**************************************************************************

/* Constructor */
MutationOperatorDisplay::MutationOperatorDisplay (System::Controller* controller, QWidget* parent)
  : OperatorDisplay (controller, parent)
{
  System::Notifier* notifier = System::Notifier::getNotifier ();

  QStringList header_names;
  header_names.push_back ("Id");
  header_names.push_back ("Before");
  header_names.push_back ("Fitness before");
  header_names.push_back ("After");
  header_names.push_back ("Fitness after");

  setHeaderLabels (header_names);

  header ()->setResizeMode (COLUMN_ID, QHeaderView::ResizeToContents);
  header ()->setResizeMode (COLUMN_BEFORE, QHeaderView::Stretch);
  header ()->setResizeMode (COLUMN_FITNESS_BEFORE, QHeaderView::ResizeToContents);
  header ()->setResizeMode (COLUMN_AFTER, QHeaderView::Stretch);
  header ()->setResizeMode (COLUMN_FITNESS_AFTER, QHeaderView::ResizeToContents);

  connect (notifier, SIGNAL (signalControllerStep ()), SLOT (slotControllerStep ()));
  connect (notifier, SIGNAL (signalMutation (GEP::System::MutationNotification)),
           SLOT (slotMutation (const GEP::System::MutationNotification&)));
}

/* Destructor */
MutationOperatorDisplay::~MutationOperatorDisplay ()
{
}

/*
 * Slot called when the controller advances one step
 */
void MutationOperatorDisplay::slotControllerStep ()
{
  clear ();
}

/*
 * Slot called when an individual has been mutated
 */
void MutationOperatorDisplay::slotMutation (const System::MutationNotification& notification)
{
  const System::IndividualInfo& before = notification.getBefore ();
  const System::IndividualInfo& after = notification.getAfter ();

  MutationOperatorDisplayItem* item = new MutationOperatorDisplayItem (before.getId (), this);
  addTopLevelItem (item);

  item->setText (COLUMN_ID, QString::number (before.getId ()));
  item->setText (COLUMN_BEFORE, before.getRepresentation ());
  item->setText (COLUMN_FITNESS_BEFORE, QString::number (before.getFitness (), 'g', 8));
  item->setText (COLUMN_AFTER, after.getRepresentation ());
  item->setText (COLUMN_FITNESS_AFTER, QString::number (after.getFitness (), 'g', 8));
}

}
}
