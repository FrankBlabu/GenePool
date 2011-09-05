/*
 * GEPTravelingWorldDisplay.h - Class for displaying the world
 *
 * Frank Cieslok, Sep. 2011
 */

#ifndef __GEP_TRAVELING_WORLD_DISPLAY_H__
#define __GEP_TRAVELING_WORLD_DISPLAY_H__

#include "GEPScopeWorldDisplay.h"

namespace GEP {
namespace Traveling {

class World;

/*
 * Class for displaying the world
 */
class WorldDisplay : public GEP::Scope::WorldDisplay
{
public:
    WorldDisplay (const World* world, QWidget* parent);
    virtual ~WorldDisplay ();

    virtual void updateDisplay (const GEP::System::Controller* controller, DisplayMode_t display_mode);

protected:
    virtual void paintEvent (QPaintEvent* event);

private:
    const World* _world;

    QList<QPolygonF> _individuals;
};


}
}

#endif
