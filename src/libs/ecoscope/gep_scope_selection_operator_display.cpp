/*
 * gep_scope_selection_operator_display.cpp - Display for selection steps of the current population
 *
 * Frank Cieslok, Sep. 2011
 */

#include "GEPScopeSelectionOperatorDisplay.h"
#include "GEPScopeTools.h"
#include "GEPSystemController.h"
#include "GEPSystemNotifier.h"
#include "GEPSystemWorld.h"

#include <QtGui/QHeaderView>

namespace GEP {
namespace Scope {

//#**************************************************************************
// CLASS GEP::Scope::SelectionOperatorDisplayItem
//#**************************************************************************

/*
 * Item for the selection display
 */
class SelectionOperatorDisplayItem : public OperatorDisplayItem
{
public:
  SelectionOperatorDisplayItem (const System::Object::Id& id, QTreeWidget* widget);
  virtual ~SelectionOperatorDisplayItem ();

  virtual bool operator< (const QTreeWidgetItem& other) const;
};

/* Constructor */
SelectionOperatorDisplayItem::SelectionOperatorDisplayItem (const System::Object::Id& id, QTreeWidget* widget)
  : OperatorDisplayItem (id, widget)
{
}

/* Destructor */
SelectionOperatorDisplayItem::~SelectionOperatorDisplayItem ()
{
}

/* Comparison operator for item sorting */
bool SelectionOperatorDisplayItem::operator< (const QTreeWidgetItem& other) const
{
  bool less = false;

  int column = treeWidget ()->sortColumn ();

  switch (column)
    {
    case SelectionOperatorDisplay::COLUMN_ID:
    case SelectionOperatorDisplay::COLUMN_NEW_IDS:
    case SelectionOperatorDisplay::COLUMN_CONTENT:
      less = text (column) < other.text (column);
      break;

    case SelectionOperatorDisplay::COLUMN_FITNESS:
      less = text (column).toDouble () < other.text (column).toDouble ();
      break;

    case SelectionOperatorDisplay::COLUMN_TIMES_SELECTED:
      less = text (column).toInt () < other.text (column).toInt ();
      break;
    }

  return less;
}


//#**************************************************************************
// CLASS GEP::Scope::SelectionOperatorDisplay
//#**************************************************************************

/* Constructor */
SelectionOperatorDisplay::SelectionOperatorDisplay (System::Controller* controller, QWidget* parent)
  : OperatorDisplay (controller, parent)
{
  System::Notifier* notifier = System::Notifier::getNotifier ();

  QStringList header_names;
  header_names.push_back ("Id");
  header_names.push_back ("Content");
  header_names.push_back ("Fitness");
  header_names.push_back ("Times selected");
  header_names.push_back ("New ids");

  setHeaderLabels (header_names);

  header ()->setResizeMode (COLUMN_ID, QHeaderView::ResizeToContents);
  header ()->setResizeMode (COLUMN_CONTENT, QHeaderView::Stretch);
  header ()->setResizeMode (COLUMN_FITNESS, QHeaderView::ResizeToContents);
  header ()->setResizeMode (COLUMN_TIMES_SELECTED, QHeaderView::ResizeToContents);
  header ()->setResizeMode (COLUMN_NEW_IDS, QHeaderView::ResizeToContents);

  connect (notifier, SIGNAL (signalControllerStep ()), SLOT (slotControllerStep ()));
  connect (notifier, SIGNAL (signalSelection (const GEP::System::Object::Id&, const GEP::System::Object::Id&)),
           SLOT (slotSelection (const GEP::System::Object::Id&, const GEP::System::Object::Id&)));
}

/* Destructor */
SelectionOperatorDisplay::~SelectionOperatorDisplay ()
{
}

/*
 * Slot called when the controller advances one step
 */
void SelectionOperatorDisplay::slotControllerStep ()
{
  clear ();
}

/*
 * Slot called when an individual is selected
 */
void SelectionOperatorDisplay::slotSelection (const System::Object::Id& before,
                                              const System::Object::Id& after)
{
  const System::Population& population = getController ()->getPopulation ();

  QTreeWidgetItem* item = 0;

  ItemMap::const_iterator pos = _items.find (before);
  if (pos == _items.end ())
    {
      item = new SelectionOperatorDisplayItem (before, this);
      addTopLevelItem (item);
      _items.insert (before, item);
    }
  else
    item = pos.value ();

  const System::Individual& individual = population[before];

  item->setText (COLUMN_ID, QString::number (before));
  item->setText (COLUMN_CONTENT, individual.toString ());
  item->setText (COLUMN_FITNESS, QString::number (getController ()->getFitnessOperator ()->compute (individual), 'g', 2));

  QString selected_text = item->text (COLUMN_NEW_IDS);
  if (selected_text.isEmpty ())
    {
      item->setText (COLUMN_TIMES_SELECTED, QString::number (1));
      item->setText (COLUMN_NEW_IDS, QString::number (after));
    }
  else
    {
      item->setText (COLUMN_TIMES_SELECTED, QString::number (selected_text.count (",") + 2));
      item->setText (COLUMN_NEW_IDS, selected_text + "," + QString::number (after));
    }
}


}
}
