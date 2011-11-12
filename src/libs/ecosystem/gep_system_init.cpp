/*
 * gep_system_init.cpp - Initialize system library
 *
 * Frank Cieslok, Nov. 2011
 */

#define GEP_DEBUG

#include "GEPSystemInit.h"
#include "GEPSystemNotifier.h"
#include "GEPSystemObject.h"
#include "GEPSystemDebug.h"

namespace GEP {
namespace System {

/*
 * Initialize library
 */
void InitLibrary ()
{
  qRegisterMetaType<GEP::System::Object::Id> ("GEP::System::Object::Id");

  qRegisterMetaType<GEP::System::SelectionNotificationList> ("GEP::System::SelectionNotificationList");
  qRegisterMetaType<GEP::System::MutationNotificationList> ("GEP::System::MutationNotificationList");
  qRegisterMetaType<GEP::System::CrossoverNotificationList> ("GEP::System::CrossoverNotificationList");
}

}
}
