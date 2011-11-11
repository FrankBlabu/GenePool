/*
 * gep_system_init.cpp - Initialize system library
 *
 * Frank Cieslok, Nov. 2011
 */

#define GEP_DEBUG

#include "GEPSystemInit.h"
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
}

}
}
