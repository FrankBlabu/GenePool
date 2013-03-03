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

#include <QtWidgets/QHeaderView>

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
    case CrossoverOperatorDisplay::COLUMN_MATE1_ID:
    case CrossoverOperatorDisplay::COLUMN_MATE1_INDIVIDUAL:
    case CrossoverOperatorDisplay::COLUMN_MATE2_ID:
    case CrossoverOperatorDisplay::COLUMN_MATE2_INDIVIDUAL:
    case CrossoverOperatorDisplay::COLUMN_CROSSED1_INDIVIDUAL:
    case CrossoverOperatorDisplay::COLUMN_CROSSED2_INDIVIDUAL:
      less = text (column) < other.text (column);
      break;

    case CrossoverOperatorDisplay::COLUMN_MATE1_FITNESS:
    case CrossoverOperatorDisplay::COLUMN_MATE2_FITNESS:
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
  header_names.append (tr ("Mate 1 (Id)"));
  header_names.append (tr ("Mate 1 (Individual)"));
  header_names.append (tr ("Mate 1 (Fitness)"));
  header_names.append (tr ("Mate 2 (Id)"));
  header_names.append (tr ("Mate 2 (individual)"));
  header_names.append (tr ("Mate 2 (Fitness)"));
  header_names.append (tr ("Crossed 1 (Individual)"));
  header_names.append (tr ("Crossed 2 (Individual)"));

  setHeaderLabels (header_names);

  header ()->setSectionResizeMode (COLUMN_MATE1_ID, QHeaderView::ResizeToContents);
  header ()->setSectionResizeMode (COLUMN_MATE1_INDIVIDUAL, QHeaderView::Stretch);
  header ()->setSectionResizeMode (COLUMN_MATE1_FITNESS, QHeaderView::ResizeToContents);
  header ()->setSectionResizeMode (COLUMN_MATE2_ID, QHeaderView::ResizeToContents);
  header ()->setSectionResizeMode (COLUMN_MATE2_INDIVIDUAL, QHeaderView::Stretch);
  header ()->setSectionResizeMode (COLUMN_MATE2_FITNESS, QHeaderView::ResizeToContents);
  header ()->setSectionResizeMode (COLUMN_CROSSED1_INDIVIDUAL, QHeaderView::Stretch);
  header ()->setSectionResizeMode (COLUMN_CROSSED2_INDIVIDUAL, QHeaderView::Stretch);

  connect (notifier, SIGNAL (signalControllerStepStart (GEP::System::ControllerStepNotification)), SLOT (slotReset ()));
  connect (notifier, SIGNAL (signalReset ()), SLOT (slotReset ()));
  connect (notifier, SIGNAL (signalCrossover (GEP::System::CrossoverNotificationList)),
           SLOT (slotCrossover (const GEP::System::CrossoverNotificationList&)));
}

/* Destructor */
CrossoverOperatorDisplay::~CrossoverOperatorDisplay ()
{
}

/*
 * Slot called on world reset
 */
void CrossoverOperatorDisplay::slotReset ()
{
  clear ();
}

/*
 * A crossover operation has been performed
 */
void CrossoverOperatorDisplay::slotCrossover (const System::CrossoverNotificationList& notifications)
{
  QColor bar_color = Qt::green;
  bar_color.setAlphaF (0.3);

  for (int i=0; i < notifications.size (); ++i)
    {
      const System::CrossoverNotification& notification = notifications[i];

      CrossoverOperatorDisplayItem* item = new CrossoverOperatorDisplayItem (notification.getBeforeFirst ().getId (), this);
      addTopLevelItem (item);

      item->setText (COLUMN_MATE1_ID, QString::number (notification.getBeforeFirst ().getId ()));
      item->setData (COLUMN_MATE1_INDIVIDUAL, Qt::DisplayRole, qVariantFromValue (notification.getBeforeFirst ()));
      item->setText (COLUMN_MATE1_FITNESS, getFitnessRepresentation (notification.getBeforeFirst ()));
      item->setData (COLUMN_MATE1_FITNESS, Qt::BackgroundRole,
                     qVariantFromValue (OperatorDisplayColorBar (notification.getBeforeFirst ().getFitness (), 1.0, bar_color)));

      item->setText (COLUMN_MATE2_ID, QString::number (notification.getBeforeSecond ().getId ()));
      item->setData (COLUMN_MATE2_INDIVIDUAL, Qt::DisplayRole, qVariantFromValue (notification.getBeforeSecond ()));
      item->setText (COLUMN_MATE2_FITNESS, getFitnessRepresentation (notification.getBeforeSecond ()));
      item->setData (COLUMN_MATE2_FITNESS, Qt::BackgroundRole,
                     qVariantFromValue (OperatorDisplayColorBar (notification.getBeforeSecond ().getFitness (), 1.0, bar_color)));

      item->setData (COLUMN_CROSSED1_INDIVIDUAL, Qt::DisplayRole,
                     qVariantFromValue (OperatorDisplayIndividualDifference (notification.getBeforeFirst (), notification.getAfterFirst ())));
      item->setData (COLUMN_CROSSED2_INDIVIDUAL, Qt::DisplayRole,
                     qVariantFromValue (OperatorDisplayIndividualDifference (notification.getBeforeSecond (), notification.getAfterSecond ())));
    }
}

}
}
