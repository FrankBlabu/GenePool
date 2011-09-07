/*
 * GEPSystemNotifier.h - Notifier class for algorithm events
 *
 * Frank Cieslok, Sep. 2011
 */

#ifndef __GEP_SYSTEM_NOTIFIER_H__
#define __GEP_SYSTEM_NOTIFIER_H__

#include <GEPSystemObject.h>

#include <QtCore/QObject>

namespace GEP {
namespace System {

/*
 * Notifier class for algorithm events
 */
class Notifier : public QObject
{
  Q_OBJECT

public:
  Notifier ();

  bool getEnabled () const;
  void setEnabled (bool enabled);

  void notifyControllerStep ();
  void notifyIndividualSelection (const Object::Id& before, const Object::Id& after);

signals:
  void signalControllerStep ();
  void signalIndividualSelection (const Object::Id& before, const Object::Id& after);

private:
  bool _enabled;
};

}
}

#endif
