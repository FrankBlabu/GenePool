/*
 * GEPSystemSelectionOperator.h - Base class for selection operators
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_SYSTEM_SELECTION_OPERATOR_H__
#define __GEP_SYSTEM_SELECTION_OPERATOR_H__

#include "GEPSystemOperator.h"
#include "GEPSystemPopulation.h"

namespace GEP {
namespace System {

/*
 * Base class for selection operators
 */
template <class T>
class SelectionOperator : public Operator
{
public:
    SelectionOperator () {}
    virtual ~SelectionOperator () {}

    virtual void compute (const Population<T>& source, Population<T>* target) = 0;
};

}
}

#endif
