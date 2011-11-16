/*
 * gep_scope_init.cpp - Initialize scope library
 *
 * Frank Cieslok, Nov. 2011
 */

#define GEP_DEBUG

#include "GEPScopeInit.h"
#include "GEPScopeOperatorDisplay.h"
#include "GEPSystemDebug.h"

namespace GEP {
namespace Scope {

/*
 * Initialize library
 */
void InitLibrary ()
{
  qRegisterMetaType<GEP::Scope::OperatorDisplayIndividualDifference> ("GEP::Scope::OperatorDisplayIndividualDifference");
}

}
}
