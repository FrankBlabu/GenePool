/*
 * gep_system_controller_thread.cpp - Thread executing the controller
 *
 * Frank Cieslok, Nov. 2011
 */

#include "GEPSystemControllerThread.h"
#include "GEPSystemController.h"

namespace GEP {
namespace System {

//#**************************************************************************
// CLASS GEP::System::ControllerThread
//#**************************************************************************

/* Constructor */
ControllerThread::ControllerThread (Controller* controller)
  : _controller (controller),
    _abort      (false)
{
}

/* Execute computation */
void ControllerThread::run ()
{
  bool done = false;

  while (!done && !_abort)
    {
      int step = _controller->getCurrentStep ();

      done = _controller->executeStep  ();

      emit signalStep (step);
    }

  emit signalDone ();
}

/* Abort computation */
void ControllerThread::slotAbort ()
{
  _abort = true;
}

}
}
