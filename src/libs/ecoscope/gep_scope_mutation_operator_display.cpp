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
  header_names.append ("Id");
  header_names.append ("Before");
  header_names.append ("Fitness before");
  header_names.append ("After");
  header_names.append ("Fitness after");

  setHeaderLabels (header_names);

  header ()->setResizeMode (COLUMN_ID, QHeaderView::ResizeToContents);
  header ()->setResizeMode (COLUMN_BEFORE, QHeaderView::Stretch);
  header ()->setResizeMode (COLUMN_FITNESS_BEFORE, QHeaderView::ResizeToContents);
  header ()->setResizeMode (COLUMN_AFTER, QHeaderView::Stretch);
  header ()->setResizeMode (COLUMN_FITNESS_AFTER, QHeaderView::ResizeToContents);

  connect (notifier, SIGNAL (signalControllerStep (GEP::System::ControllerStepNotification)),
           SLOT (slotControllerStep (const GEP::System::ControllerStepNotification&)));
  connect (notifier, SIGNAL (signalMutation (GEP::System::MutationNotificationList)),
           SLOT (slotMutation (const GEP::System::MutationNotificationList&)));
}

/* Destructor */
MutationOperatorDisplay::~MutationOperatorDisplay ()
{
}

/*
 * Slot called when the controller advances one step
 */
void MutationOperatorDisplay::slotControllerStep (const GEP::System::ControllerStepNotification& notification)
{
  Q_UNUSED (notification);
  clear ();
}

/*
 * Slot called when an individual has been mutated
 */
void MutationOperatorDisplay::slotMutation (const System::MutationNotificationList& notifications)
{
  for (int i=0; i < notifications.size (); ++i)
    {
      const System::MutationNotification& notification = notifications[i];

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
}
