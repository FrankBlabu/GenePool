/*
 * GEPSystemControllerThread.h - Thread executing the controller
 *
 * Frank Cieslok, Nov. 2011
 */

#ifndef __GEP_SYSTEM_CONTROLLER_THREAD_H__
#define __GEP_SYSTEM_CONTROLLER_THREAD_H

#include <QtCore/QThread>

namespace GEP {
namespace System {

class Controller;

/*
 * Thread executing the controller
 */
class ControllerThread : public QThread
{
  Q_OBJECT;

public:
    ControllerThread (Controller* controller);

    virtual void run ();

signals:
    void signalStep (int step);
    void signalDone ();

public slots:
    void slotAbort ();

private:
    Controller* _controller;
    bool _abort;
};

}
}

#endif
