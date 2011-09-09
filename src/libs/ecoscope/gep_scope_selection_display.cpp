/*
 * gep_selection_display.cpp - Display for selection step of the current population
 *
 * Frank Cieslok, Sep. 2011
 */

#include "GEPScopeSelectionDisplay.h"
#include "GEPScopeTools.h"
#include "GEPSystemController.h"
#include "GEPSystemNotifier.h"
#include "GEPSystemWorld.h"

#include <QtGui/QHeaderView>

#include <QDebug>

namespace GEP {
namespace Scope {

//#**************************************************************************
// CLASS GEP::Scope::SelectionDisplayItem
//#**************************************************************************

/*
 * Item for the selection display
 */
class SelectionDisplayItem : public QTreeWidgetItem
{
public:
  SelectionDisplayItem (QTreeWidget* widget);

  virtual bool operator< (const QTreeWidgetItem& other) const;
};

/* Constructor */
SelectionDisplayItem::SelectionDisplayItem (QTreeWidget* widget)
  : QTreeWidgetItem (widget)
{
}

/* Comparison operator for item sorting */
bool SelectionDisplayItem::operator< (const QTreeWidgetItem& other) const
{
  bool less = false;

  int column = treeWidget ()->sortColumn ();

  switch (column)
    {
    case SelectionDisplay::COLUMN_ID:
    case SelectionDisplay::COLUMN_NEW_IDS:
    case SelectionDisplay::COLUMN_CONTENT:
      less = text (column) < other.text (column);
      break;

    case SelectionDisplay::COLUMN_FITNESS_WORLD:
    case SelectionDisplay::COLUMN_FITNESS_OPERATOR:
      less = text (column).toDouble () < other.text (column).toDouble ();
      break;

    case SelectionDisplay::COLUMN_TIMES_SELECTED:
      less = text (column).toInt () < other.text (column).toInt ();
      break;
    }

  return less;
}


//#**************************************************************************
// CLASS GEP::Scope::SelectionDisplay
//#**************************************************************************

/* Constructor */
SelectionDisplay::SelectionDisplay (System::Controller* controller, QWidget* parent)
  : QTreeWidget (parent),
    _controller (controller)
{
  System::Notifier* notifier = _controller->getWorld ()->getNotifier ();

  QStringList header_names;
  header_names.push_back ("Id");
  header_names.push_back ("Content");
  header_names.push_back ("Fitness (world)");
  header_names.push_back ("Fitness (operator)");
  header_names.push_back ("Times selected");
  header_names.push_back ("New ids");

  setColumnCount (5);
  setHeaderLabels (header_names);
  setAllColumnsShowFocus (true);
  setRootIsDecorated (false);
  setSortingEnabled (true);

  header ()->setResizeMode (COLUMN_ID, QHeaderView::ResizeToContents);
  header ()->setResizeMode (COLUMN_CONTENT, QHeaderView::Stretch);
  header ()->setResizeMode (COLUMN_FITNESS_WORLD, QHeaderView::ResizeToContents);
  header ()->setResizeMode (COLUMN_FITNESS_OPERATOR, QHeaderView::ResizeToContents);
  header ()->setResizeMode (COLUMN_TIMES_SELECTED, QHeaderView::ResizeToContents);
  header ()->setResizeMode (COLUMN_NEW_IDS, QHeaderView::ResizeToContents);

  connect (notifier, SIGNAL (signalControllerStep ()), SLOT (slotControllerStep ()));
  connect (notifier, SIGNAL (signalIndividualSelection (const System::Object::Id&, const System::Object::Id&)),
           SLOT (slotIndividualSelection (const System::Object::Id&, const System::Object::Id&)));
}

/* Destructor */
SelectionDisplay::~SelectionDisplay ()
{
}

/*
 * Slot called when the controller advances one step
 */
void SelectionDisplay::slotControllerStep ()
{
  clear ();
}

/*
 * Slot called when an individual is selected
 */
void SelectionDisplay::slotIndividualSelection (const System::Object::Id& before,
                                                const System::Object::Id& after)
{
  const System::Population& population = _controller->getPopulation ();

  QTreeWidgetItem* item = 0;

  ItemMap::const_iterator pos = _items.find (before);
  if (pos == _items.end ())
    {
      item = new SelectionDisplayItem (this);
      addTopLevelItem (item);
      _items.insert (before, item);
    }
  else
    item = pos.value ();

  const System::Individual& individual = population[before];

  item->setText (COLUMN_ID, QString::number (before));
  item->setText (COLUMN_CONTENT, individual.toString ());

  item->setText (COLUMN_FITNESS_WORLD, QString::number (_controller->getWorld ()->getFitness (individual), 'g', 2));
  item->setText (COLUMN_FITNESS_OPERATOR, QString::number (_controller->getFitnessOperator ()->compute (individual), 'g', 2));

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
