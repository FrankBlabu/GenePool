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
#include <QtGui/QPainter>


namespace GEP {
namespace Scope {

//#**************************************************************************
// CLASS GEP::Scope::OperatorDisplayIndividualDifference
//#**************************************************************************

/* Constructor */
OperatorDisplayColorBar::OperatorDisplayColorBar ()
  : _value     (0),
    _max_value (0),
    _color     (Qt::black)
{
}

/* Constructor */
OperatorDisplayColorBar::OperatorDisplayColorBar (double value, double max_value, const QColor& color)
  : _value     (value),
    _max_value (max_value),
    _color     (color)
{
}

/* Copy constructor */
OperatorDisplayColorBar::OperatorDisplayColorBar (const OperatorDisplayColorBar& toCopy)
  : _value     (toCopy._value),
    _max_value (toCopy._max_value),
    _color     (toCopy._color)
{
}

/* Get current value */
double OperatorDisplayColorBar::getValue () const
{
  return _value;
}

/* Get current maximum value */
double OperatorDisplayColorBar::getMaximumValue () const
{
  return _max_value;
}

/* Get current color */
const QColor& OperatorDisplayColorBar::getColor () const
{
  return _color;
}


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

/* Copy constructor */
OperatorDisplayIndividualDifference::OperatorDisplayIndividualDifference (const OperatorDisplayIndividualDifference& toCopy)
  : _before (toCopy._before),
    _after  (toCopy._after)
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
  virtual QSize sizeHint (const QStyleOptionViewItem& option, const QModelIndex& index) const;

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
  //
  // Step 1: Background
  //
  drawBackground (painter, option, index);

  QVariant background = index.data (Qt::BackgroundRole);
  if (background.userType () == qMetaTypeId<OperatorDisplayColorBar> ())
    {
      OperatorDisplayColorBar color_bar = background.value<OperatorDisplayColorBar> ();

      QRectF rect = option.rect;
      rect.setWidth (qMax ((rect.width () - 2), 0.0) * color_bar.getValue () / color_bar.getMaximumValue ());

      painter->fillRect (rect, color_bar.getColor ());
    }

  //
  // Step 2: Content
  //
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

      const System::Individual::Chromosome& before = diff.getBefore ().getChromosome ();
      const System::Individual::Chromosome& after = diff.getAfter ().getChromosome ();

      Q_ASSERT (before.length () == after.length ());

      QString separator;
      QColor marker_color = Qt::red;
      marker_color.setAlphaF (0.3);

      int start_offset = -1;

      for (int i=0; i < before.length (); ++i)
        {
          const System::Individual::Gene& gene_before = before[i];
          const System::Individual::Gene& gene_after = after[i];

          if (gene_before != gene_after)
            {
              text += separator;

              if (start_offset == -1)
                start_offset = option.fontMetrics.width (text);

              text += QString::number (gene_after);
            }
          else if (start_offset != -1)
            {
              int end_offset = option.fontMetrics.width (text);
              painter->fillRect (QRect (QPoint (option.rect.left () + start_offset, option.rect.top ()),
                                        QPoint (option.rect.left () + end_offset, option.rect.bottom ())),
                                 marker_color);

              start_offset = -1;
              text += separator + QString::number (gene_after);
            }
          else
            text += separator + QString::number (gene_after);

          separator = ",";
        }

      if (start_offset != -1)
        {
          int end_offset = option.fontMetrics.width (text);
          painter->fillRect (QRect (QPoint (option.rect.left () + start_offset, option.rect.top ()),
                                    QPoint (option.rect.left () + end_offset, option.rect.bottom ())),
                             marker_color);
        }
    }
  else
    text = data.toString ();

  painter->drawText (option.rect, Qt::AlignLeft | Qt::AlignVCenter | Qt::TextSingleLine, text);
}

/* Compute size hint */
QSize OperatorDisplayItemDelegate::sizeHint (const QStyleOptionViewItem& option, const QModelIndex& index) const
{
  QSize size;

  QVariant data = index.data (Qt::DisplayRole);

  if (data.userType () == qMetaTypeId<OperatorDisplayIndividualDifference> ())
    {
      OperatorDisplayIndividualDifference diff = data.value<OperatorDisplayIndividualDifference> ();
      QString text = toString (diff.getAfter ().getChromosome ());

      size = option.fontMetrics.size (Qt::TextSingleLine, text);
    }
  else
    size = QItemDelegate::sizeHint (option, index);

  return size;
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
