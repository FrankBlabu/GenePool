/*
 * gep_scope_selection_operator_display.cpp - Display for selection steps of the current population
 *
 * Frank Cieslok, Sep. 2011
 */

#define GEP_DEBUG

#include "GEPScopeSelectionOperatorDisplay.h"
#include "GEPScopeTools.h"
#include "GEPSystemController.h"
#include "GEPSystemNotifier.h"
#include "GEPSystemWorld.h"
#include "GEPSystemDebug.h"

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
    case SelectionOperatorDisplay::COLUMN_INDIVIDUAL:
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
  header_names.append (tr ("Id"));
  header_names.append (tr ("Individual"));
  header_names.append (tr ("Fitness"));
  header_names.append (tr ("Times selected"));
  header_names.append (tr ("New ids"));

  setHeaderLabels (header_names);

  header ()->setResizeMode (COLUMN_ID, QHeaderView::ResizeToContents);
  header ()->setResizeMode (COLUMN_INDIVIDUAL, QHeaderView::Stretch);
  header ()->setResizeMode (COLUMN_FITNESS, QHeaderView::ResizeToContents);
  header ()->setResizeMode (COLUMN_TIMES_SELECTED, QHeaderView::ResizeToContents);
  header ()->setResizeMode (COLUMN_NEW_IDS, QHeaderView::ResizeToContents);

  connect (notifier, SIGNAL (signalControllerStep (GEP::System::ControllerStepNotification)),
           SLOT (slotControllerStep (const GEP::System::ControllerStepNotification&)));
  connect (notifier, SIGNAL (signalSelection (GEP::System::SelectionNotificationList)),
           SLOT (slotSelection (GEP::System::SelectionNotificationList)));
}

/* Destructor */
SelectionOperatorDisplay::~SelectionOperatorDisplay ()
{
}

/*
 * Slot called when the controller advances one step
 */
void SelectionOperatorDisplay::slotControllerStep (const GEP::System::ControllerStepNotification& notification)
{
  Q_UNUSED (notification);

  clear ();
  _items.clear ();
}

/*
 * Slot called when an individual is selected
 */
void SelectionOperatorDisplay::slotSelection (const System::SelectionNotificationList& notifications)
{
  //
  // Add notifications to items
  //
  for (int i=0; i < notifications.size (); ++i)
    {
      const System::SelectionNotification& notification = notifications[i];

      QTreeWidgetItem* item = 0;

      const System::IndividualInfo& selected = notification.getBefore ();

      ItemMap::const_iterator pos = _items.find (selected.getId ());
      if (pos == _items.end ())
        {
          item = new SelectionOperatorDisplayItem (selected.getId (), this);
          addTopLevelItem (item);
          _items.insert (selected.getId (), item);
        }
      else
        item = pos.value ();

      item->setText (COLUMN_ID, QString::number (selected.getId ()));
      item->setData (COLUMN_INDIVIDUAL, Qt::DisplayRole, qVariantFromValue (selected));
      item->setText (COLUMN_FITNESS, getFitnessRepresentation (selected));

      QString selected_text = item->text (COLUMN_NEW_IDS);
      if (selected_text.isEmpty ())
        {
          item->setText (COLUMN_TIMES_SELECTED, QString::number (1));
          item->setText (COLUMN_NEW_IDS, QString::number (notification.getAfter ().getId ()));
        }
      else
        {
          item->setText (COLUMN_TIMES_SELECTED, QString::number (selected_text.count (",") + 2));
          item->setText (COLUMN_NEW_IDS, selected_text + "," + QString::number (notification.getAfter ().getId ()));
        }
    }

  //
  // Determine maximum number of selections and generate color bars
  //
  int max_selections = 0;

  for (ItemMap::ConstIterator i = _items.begin (); i != _items.end (); ++i)
    {
      const QTreeWidgetItem* item = i.value ();
      max_selections = qMax (max_selections, item->text (COLUMN_NEW_IDS).count (",") + 1);
    }

  QColor bar_color = Qt::green;
  bar_color.setAlphaF (0.3);

  for (ItemMap::ConstIterator i = _items.begin (); i != _items.end (); ++i)
    {
      QTreeWidgetItem* item = i.value ();
      item->setData (COLUMN_TIMES_SELECTED, Qt::BackgroundRole,
                     qVariantFromValue (OperatorDisplayColorBar (item->text (COLUMN_NEW_IDS).count (",") + 1, max_selections, bar_color)));
    }
}


}
}
