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

#include <QDebug>

namespace GEP {
namespace Scope {

//#**************************************************************************
// CLASS GEP::Scope::CrossoverOperatorDisplayItem
//#**************************************************************************

/*
 * Item for the crossover display
 */
class CrossoverOperatorDisplayItem : public QTreeWidgetItem
{
public:
  CrossoverOperatorDisplayItem (QTreeWidget* widget);

  virtual bool operator< (const QTreeWidgetItem& other) const;
};

/* Constructor */
CrossoverOperatorDisplayItem::CrossoverOperatorDisplayItem (QTreeWidget* widget)
  : QTreeWidgetItem (widget)
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
  : OperatorDisplay (parent),
    _controller (controller)
{
  System::Notifier* notifier = _controller->getWorld ()->getNotifier ();

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
  connect (notifier, SIGNAL (signalPreCrossover (const System::Object::Id&, const System::Object::Id&)),
           SLOT (slotPreCrossover (const System::Object::Id&, const System::Object::Id&)));
  connect (notifier, SIGNAL (signalCrossover (const System::Object::Id&, const System::Object::Id&)),
           SLOT (slotCrossover (const System::Object::Id&, const System::Object::Id&)));
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
 * A crossover operation is going to be performed
 */
void CrossoverOperatorDisplay::slotPreCrossover (const System::Object::Id& object1,
                                                 const System::Object::Id& object2)
{
  setupItem (object1, object2);
  setupItem (object2, object1);
}

/*
 * A crossover operation has been performed
 */
void CrossoverOperatorDisplay::slotCrossover (const System::Object::Id& object1,
                                              const System::Object::Id& object2)
{
  completeItem (object1);
  completeItem (object2);
}

/*
 * Setup item for pre crossover
 */
void CrossoverOperatorDisplay::setupItem (const System::Object::Id& object1,
                                          const System::Object::Id& object2)
{
  CrossoverOperatorDisplayItem* item = getItem (object1);

  const System::Population& population = _controller->getPopulation ();
  const System::Individual& individual = population[object1];

  item->setText (COLUMN_ID, QString::number (object1));
  item->setText (COLUMN_CONTENT, individual.toString ());
  item->setText (COLUMN_MATE, QString::number (object2));

  item->setText (COLUMN_FITNESS_BEFORE, QString::number (_controller->getFitnessOperator ()->compute (individual), 'g', 2));
}

/*
 * Complete item for a performed crossover
 */
void CrossoverOperatorDisplay::completeItem (const System::Object::Id& object)
{
  CrossoverOperatorDisplayItem* item = getItem (object);

  const System::Population& population = _controller->getPopulation ();
  const System::Individual& individual = population[object];

  item->setText (COLUMN_CROSSED, individual.toString ());
  item->setText (COLUMN_FITNESS_AFTER, QString::number (_controller->getFitnessOperator ()->compute (individual), 'g', 2));
}

/*
 * Get or create item belonging to a given object id
 */
CrossoverOperatorDisplayItem* CrossoverOperatorDisplay::getItem (const System::Object::Id& id)
{
  CrossoverOperatorDisplayItem* item = 0;

  ItemMap::const_iterator pos = _items.find (id);
  if (pos == _items.end ())
    {
      item = new CrossoverOperatorDisplayItem (this);
      addTopLevelItem (item);
      _items.insert (id, item);
    }
  else
    item = pos.value ();

  return item;
}

}
}
