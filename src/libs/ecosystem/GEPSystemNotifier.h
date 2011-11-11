/*
 * GEPSystemNotifier.h - Notifier class for algorithm events
 *
 * Frank Cieslok, Sep. 2011
 */

#ifndef __GEP_SYSTEM_NOTIFIER_H__
#define __GEP_SYSTEM_NOTIFIER_H__

#include <GEPSystemIndividual.h>
#include <GEPSystemObject.h>

#include <QtCore/QObject>

namespace GEP {
namespace System {

class Individual;

/*
 * Information about a single individual
 */
class IndividualInfo
{
public:
  IndividualInfo () {}
  IndividualInfo (const Individual& individual, double fitness)
    : _id (individual.getId ()), _representation (individual.toString ()), _fitness (fitness) {}

  const Object::Id& getId () const { return _id; }
  const QString& getRepresentation () const { return _representation; }
  double getFitness () const { return _fitness; }

private:
  Object::Id _id;
  QString _representation;
  double _fitness;
};

/*
 * Notification about a selection
 */
class SelectionNotification
{
public:
  SelectionNotification () {}
  SelectionNotification (const IndividualInfo& before, const IndividualInfo& after)
    : _before (before), _after (after) {}

  const IndividualInfo& getBefore () const { return _before; }
  const IndividualInfo& getAfter () const { return _after; }

private:
  IndividualInfo _before;
  IndividualInfo _after;
};

/*
 * Notification about a mutation
 */
class MutationNotification
{
public:
  MutationNotification () {}
  MutationNotification (const IndividualInfo& before, const IndividualInfo& after)
    : _before (before), _after (after) {}

  const IndividualInfo& getBefore () const { return _before; }
  const IndividualInfo& getAfter () const { return _after; }

private:
  IndividualInfo _before;
  IndividualInfo _after;
};

/*
 * Notification about a crossover
 */
class CrossoverNotification
{
public:
  CrossoverNotification () {}
  CrossoverNotification (const IndividualInfo& before_first,
                         const IndividualInfo& before_second,
                         const IndividualInfo& after_first,
                         const IndividualInfo& after_second)
    : _before_first (before_first), _before_second (before_second),
      _after_first (after_first), _after_second (after_second)
  {}

  const IndividualInfo& getBeforeFirst () const { return _before_first; }
  const IndividualInfo& getBeforeSecond () const { return _before_second; }
  const IndividualInfo& getAfterFirst () const { return _after_second; }
  const IndividualInfo& getAfterSecond () const { return _after_second; }

private:
  IndividualInfo _before_first;
  IndividualInfo _before_second;
  IndividualInfo _after_first;
  IndividualInfo _after_second;
};

/*
 * Notifier class for algorithm events
 */
class Notifier : public QObject
{
  Q_OBJECT

private:
  Notifier ();

public:
  static Notifier* getNotifier ();

  //
  // Configuration
  //
  bool getEnabled () const;
  void setEnabled (bool enabled);

  //
  // Individual creation
  //
  void notifyIndividualCreated (const Object::Id& id);

  //
  // Notifier calls for algorithm steps
  //
  void notifyControllerStep ();

  void notifySelection (const SelectionNotification& notification);
  void notifyCrossover (const CrossoverNotification& notification);
  void notifyMutation (const MutationNotification& notification);

  //
  // Notifier calls for GUI events
  //
  void notifyIndividualFocusChanged (const Object::Id& id);

signals:
  //
  // Individual creation
  //
  void signalIndividualCreated (const GEP::System::Object::Id& id);

  //
  // Notifier signals for algorithm steps
  //
  void signalControllerStep ();

  void signalSelection (GEP::System::SelectionNotification notification);
  void signalCrossover (GEP::System::CrossoverNotification notification);
  void signalMutation (GEP::System::MutationNotification notification);

  //
  // Notifier signales for GUI events
  //
  void signalIndividualFocusChanged (const GEP::System::Object::Id& id);


private:
  bool _enabled;
};

}
}

Q_DECLARE_METATYPE (GEP::System::SelectionNotification);
Q_DECLARE_METATYPE (GEP::System::MutationNotification);
Q_DECLARE_METATYPE (GEP::System::CrossoverNotification);


#endif
