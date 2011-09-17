/*
 * GEPTravelingWorldDisplay.h - Class for displaying the world
 *
 * Frank Cieslok, Sep. 2011
 */

#ifndef __GEP_TRAVELING_WORLD_DISPLAY_H__
#define __GEP_TRAVELING_WORLD_DISPLAY_H__

#include <GEPSystemIndividual.h>
#include "GEPScopeWorldDisplay.h"

namespace GEP {
namespace Traveling {

class World;

/*
 * Class for displaying the world
 */
class WorldDisplay : public GEP::Scope::WorldDisplay
{
  Q_OBJECT

public:
    WorldDisplay (const World* world, QWidget* parent);
    virtual ~WorldDisplay ();

    virtual void updateDisplay (const GEP::System::Controller* controller, DisplayMode_t display_mode);

protected:
    virtual void paintEvent (QPaintEvent* event);

private slots:
    void slotClear ();
    void slotAddIndividual (const System::Individual& individual);

private:
    const World* _world;

    QList<QPointF> _cities;
    QList<QPolygonF> _individuals;
};


}
}

#endif
