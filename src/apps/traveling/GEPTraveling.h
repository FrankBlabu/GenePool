/*
 * GEPTraveling.h - Solver for the traveling salesman problem via evolutionary algorithms
 *
 * Frank Cieslok, Aug. 2011
 */

#ifndef __GEP_TRAVELING_H__
#define __GEP_TRAVELING_H__

#include "ui_gep_traveling.h"

namespace GEP {

/*
 * Solver for the traveling salesman problem via evolutionary algorithms
 */
class Traveling : public QMainWindow, private Ui::Traveling
{
    Q_OBJECT

public:
    Traveling ();
};

}

#endif
