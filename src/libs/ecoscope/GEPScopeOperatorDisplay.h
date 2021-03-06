/*
 * GEPScopeOperatorDisplay.h - Base class for all operator display classes
 *
 * Frank Cieslok, Sep. 2011
 */

#ifndef __GEP_SCOPE_OPERATOR_DISPLAY_H__
#define __GEP_SCOPE_OPERATOR_DISPLAY_H__

#include <GEPSystemObject.h>
#include <GEPSystemNotifier.h>

#include <QtGui/QColor>
#include <QtWidgets/QTreeWidget>

namespace GEP {

namespace System {
class Controller;
class IndividualInfo;
}

namespace Scope {

/*
 * Type represention for a color bar
 */
class OperatorDisplayColorBar
{
public:
  OperatorDisplayColorBar ();
  OperatorDisplayColorBar (double value, double max_value, const QColor& color);
  OperatorDisplayColorBar (const OperatorDisplayColorBar& toCopy);

  double getValue () const;
  double getMaximumValue () const;
  const QColor& getColor () const;

private:
  double _value;
  double _max_value;
  QColor _color;
};

/*
 * Type represention the difference of two individuals
 */
class OperatorDisplayIndividualDifference
{
public:
  OperatorDisplayIndividualDifference ();
  OperatorDisplayIndividualDifference (const System::IndividualInfo& before,
                                       const System::IndividualInfo& after);
  OperatorDisplayIndividualDifference (const OperatorDisplayIndividualDifference& toCopy);

  const System::IndividualInfo& getBefore () const;
  const System::IndividualInfo& getAfter () const;

private:
  System::IndividualInfo _before;
  System::IndividualInfo _after;
};

/*
 * Item for the operator displays
 */
class OperatorDisplayItem : public QTreeWidgetItem
{
public:
  OperatorDisplayItem (const System::Object::Id& id, QTreeWidget* widget);
  virtual ~OperatorDisplayItem ();

  const System::Object::Id& getId () const;

private:
  System::Object::Id _id;
};

/*
 * Base class for all operator display classes
 */
class OperatorDisplay : public QTreeWidget
{
  Q_OBJECT

public:
  OperatorDisplay (System::Controller* controller, QWidget* parent);
  virtual ~OperatorDisplay ();

  bool getActive () const;
  void setActive (bool active);

protected:
  System::Controller* getController () const;
  QString getFitnessRepresentation (const System::IndividualInfo& info) const;

private slots:
  void slotSelectionChanged ();

private:
  System::Controller* _controller;
  bool _active;
};

}
}

Q_DECLARE_METATYPE (GEP::Scope::OperatorDisplayColorBar);
Q_DECLARE_METATYPE (GEP::Scope::OperatorDisplayIndividualDifference);

#endif
