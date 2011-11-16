/*
 * gep_scope_operator_display.cpp - Base class for alle operator displays
 *
 * Frank Cieslok, Sep. 2011
 */

#define GEP_DEBUG

#include "GEPScopeOperatorDisplay.h"
#include "GEPScopeTools.h"

#include <GEPSystemController.h>
#include <GEPSystemNotifier.h>
#include <GEPSystemDebug.h>

#include <QtGui/QHeaderView>
#include <QtGui/QItemDelegate>

namespace GEP {
namespace Scope {

//#**************************************************************************
// CLASS GEP::Scope::OperatorDisplayIndividualDifference
//#**************************************************************************

/* Constructor */
OperatorDisplayIndividualDifference::OperatorDisplayIndividualDifference ()
{
}

/* Constructor */
OperatorDisplayIndividualDifference::OperatorDisplayIndividualDifference (const System::IndividualInfo& before,
                                                                          const System::IndividualInfo& after)
  : _before (before),
    _after  (after)
{
}

/* Get 'before' individual */
const System::IndividualInfo& OperatorDisplayIndividualDifference::getBefore () const
{
  return _before;
}

/* Get 'after' individual */
const System::IndividualInfo& OperatorDisplayIndividualDifference::getAfter () const
{
  return _after;
}


//#**************************************************************************
// CLASS GEP::Scope::OperatorDisplayItem
//#**************************************************************************

/* Constructor */
OperatorDisplayItem::OperatorDisplayItem (const System::Object::Id& id, QTreeWidget* widget)
  : QTreeWidgetItem (widget),
    _id (id)
{
}

/* Destructor */
OperatorDisplayItem::~OperatorDisplayItem ()
{
}

/* Get object id this item represents */
const System::Object::Id& OperatorDisplayItem::getId () const
{
  return _id;
}

//#**************************************************************************
// CLASS GEP::Scope::OperatorDisplayItemDelegate
//#**************************************************************************

/*
 * Delegate for the items of a operator display
 */
class OperatorDisplayItemDelegate : public QItemDelegate
{
public:
  OperatorDisplayItemDelegate (QObject* parent);
  virtual ~OperatorDisplayItemDelegate ();

  virtual void paint (QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

private:
  QString toString (const System::Individual::Chromosome& chromosome) const;
};

/* Constructor */
OperatorDisplayItemDelegate::OperatorDisplayItemDelegate (QObject* parent)
  : QItemDelegate (parent)
{
}

/* Destructor */
OperatorDisplayItemDelegate::~OperatorDisplayItemDelegate ()
{
}

/* Paint item */
void OperatorDisplayItemDelegate::paint (QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
  drawBackground (painter, option, index);

  QString text;
  QVariant data = index.data (Qt::DisplayRole);

  if (data.userType () == qMetaTypeId<System::IndividualInfo> ())
    {
      System::IndividualInfo info = data.value<System::IndividualInfo> ();
      text = toString (info.getChromosome ());
    }
  else if (data.userType () == qMetaTypeId<OperatorDisplayIndividualDifference> ())
    {
      OperatorDisplayIndividualDifference diff = data.value<OperatorDisplayIndividualDifference> ();
      text = toString (diff.getAfter ().getChromosome ());

    }
  else
    text = data.toString ();

  drawDisplay (painter, option, option.rect, text);
}

/* Convert a chromosome into a string representation */
QString OperatorDisplayItemDelegate::toString (const System::Individual::Chromosome& chromosome) const
{
  QString text;

  QString separator = "";
  for (int i=0; i < chromosome.size (); ++i)
    {
      text += separator + QString::number (chromosome[i]);
      separator = ",";
    }

  return text;
}


//#**************************************************************************
// CLASS GEP::Scope::OperatorDisplay
//#**************************************************************************

/* Constructor */
OperatorDisplay::OperatorDisplay (System::Controller* controller, QWidget* parent)
  : QTreeWidget (parent),
    _controller (controller),
    _active (false)
{
  setAllColumnsShowFocus (true);
  setRootIsDecorated (false);
  setSortingEnabled (true);
  setSelectionMode (SingleSelection);
  setItemDelegate (new OperatorDisplayItemDelegate (this));

  connect (this, SIGNAL (itemSelectionChanged ()), SLOT (slotSelectionChanged ()));
}

/* Destructor */
OperatorDisplay::~OperatorDisplay ()
{
}

/* Get if this display is currently active */
bool OperatorDisplay::getActive () const
{
  return _active;
}

/* Set if this display is currently active */
void OperatorDisplay::setActive (bool active)
{
  _active = active;

  if (_active)
    slotSelectionChanged ();
}

/* Returns the controller instance belonging to this display */
System::Controller* OperatorDisplay::getController () const
{
  return _controller;
}

/* Create representation for an individuals fitness value */
QString OperatorDisplay::getFitnessRepresentation (const System::IndividualInfo& info) const
{
  return info.getFitness () != System::IndividualInfo::UNKNOWN_FITNESS ?
        QString::number (info.getFitness (), 'g', 8) : QString ("-");
}

/* Called if the item selection changed */
void OperatorDisplay::slotSelectionChanged ()
{
  System::Notifier* notifier = System::Notifier::getNotifier ();

  if (_active)
    {
      if (selectedItems ().size () == 1)
        {
          OperatorDisplayItem* item = dynamic_cast<OperatorDisplayItem*> (selectedItems ().front ());
          Q_ASSERT (item != 0);

          notifier->notifyIndividualFocusChanged (item->getId ());
        }
      else
        notifier->notifyIndividualFocusChanged (System::Object::INVALID);
    }
}



}
}
