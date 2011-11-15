/*
 * GEPScopeOperatorDisplay.h - Base class for all operator display classes
 *
 * Frank Cieslok, Sep. 2011
 */

#ifndef __GEP_SCOPE_OPERATOR_DISPLAY_H__
#define __GEP_SCOPE_OPERATOR_DISPLAY_H__

#include <GEPSystemObject.h>

#include <QtGui/QTreeWidget>

namespace GEP {

namespace System {
class Controller;
class IndividualInfo;
}

namespace Scope {

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

#endif
