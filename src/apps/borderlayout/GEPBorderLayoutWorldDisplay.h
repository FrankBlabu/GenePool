/*
 * GEPBorderLayoutWorldDisplay.h - Class for displaying the world
 *
 * Frank Cieslok, Nov. 2011
 */

#ifndef __GEP_BORDERLAYOUT_WORLD_DISPLAY_H__
#define __GEP_BORDERLAYOUT_WORLD_DISPLAY_H__

#include <GEPSystemIndividual.h>
#include "GEPScopeWorldDisplay.h"

#include <QtCore/QLineF>
#include <QtCore/QRectF>

namespace GEP {
namespace BorderLayout {

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

private:
    QPointF getPixelPoint (const QPointF& point) const;
    QLineF getPixelLine (const QLineF& line) const;
    QRectF getPixelRect (const QRectF& rect) const;

private:
    const World* _world;
    QList<System::Individual> _individuals;
};


}
}

#endif
