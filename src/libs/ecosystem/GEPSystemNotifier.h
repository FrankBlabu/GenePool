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

  void notifySelection (const Object::Id& before,
                        const Object::Id& after);

  void notifyPreCrossover (const Object::Id& object1,
                           const Object::Id& object2);
  void notifyCrossover (const Object::Id& object1,
                        const Object::Id& object2);

  void notifyPreMutation (const Object::Id& id);
  void notifyMutation (const Object::Id& id);

signals:
  void signalControllerStep ();

  void signalSelection (const System::Object::Id& before,
                        const System::Object::Id& after);

  void signalPreCrossover (const System::Object::Id& object1,
                           const System::Object::Id& object2);
  void signalCrossover (const System::Object::Id& object1,
                        const System::Object::Id& object2);

  void signalPreMutation (const System::Object::Id& id);
  void signalMutation (const System::Object::Id& id);

private:
  bool _enabled;
};

}
}

#endif
