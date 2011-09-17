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
    case MutationOperatorDisplay::COLUMN_CONTENT:
    case MutationOperatorDisplay::COLUMN_MUTATED:
      less = text (column) < other.text (column);
      break;

    case MutationOperatorDisplay::COLUMN_FITNESS:
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
  header_names.push_back ("Content");
  header_names.push_back ("Fitness");
  header_names.push_back ("Mutated");

  setHeaderLabels (header_names);

  header ()->setResizeMode (COLUMN_ID, QHeaderView::ResizeToContents);
  header ()->setResizeMode (COLUMN_CONTENT, QHeaderView::Stretch);
  header ()->setResizeMode (COLUMN_FITNESS, QHeaderView::ResizeToContents);
  header ()->setResizeMode (COLUMN_MUTATED, QHeaderView::Stretch);

  connect (notifier, SIGNAL (signalControllerStep ()), SLOT (slotControllerStep ()));
  connect (notifier, SIGNAL (signalPreMutation (const System::Object::Id&)),
           SLOT (slotPreMutation (const System::Object::Id&)));
  connect (notifier, SIGNAL (signalMutation (const System::Object::Id&)),
           SLOT (slotMutation (const System::Object::Id&)));
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
 * Slot called when an individual is going to be mutated
 */
void MutationOperatorDisplay::slotPreMutation (const System::Object::Id& id)
{
  MutationOperatorDisplayItem* item = new MutationOperatorDisplayItem (id, this);
  addTopLevelItem (item);
  _items.insert (id, item);

  const System::Population& population = getController ()->getPopulation ();
  const System::Individual& individual = population[id];

  item->setText (COLUMN_ID, QString::number (id));
  item->setText (COLUMN_CONTENT, individual.toString ());
  item->setText (COLUMN_FITNESS, QString::number (getController ()->getFitnessOperator ()->compute (individual), 'g', 2));
}

/*
 * Slot called when an individual has been mutated
 */
void MutationOperatorDisplay::slotMutation (const System::Object::Id& id)
{
  ItemMap::const_iterator pos = _items.find (id);
  Q_ASSERT (pos != _items.end ());

  MutationOperatorDisplayItem* item = pos.value ();

  const System::Population& population = getController ()->getPopulation ();
  const System::Individual& individual = population[id];

  item->setText (COLUMN_MUTATED, individual.toString ());
}

}
}
