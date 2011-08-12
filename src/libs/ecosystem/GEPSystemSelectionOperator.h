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
class SelectionOperator : public Operator
{
public:
    SelectionOperator ();
    virtual ~SelectionOperator ();

    virtual PopulationPtr compute (PopulationPtr population) = 0;
};

typedef boost::shared_ptr<SelectionOperator> SelectionOperatorPtr;

}
}

#endif
