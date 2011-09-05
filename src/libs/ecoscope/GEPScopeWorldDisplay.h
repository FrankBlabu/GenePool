/*
 * GEPScopeWorldDisplay.h - Base class for displaying the worlds current content
 *
 * Frank Cieslok, Sep. 2011
 */

#ifndef __GEP_SCOPE_WORLD_DISPLAY_H__
#define __GEP_SCOPE_WORLD_DISPLAY_H__

#include <QtGui/QWidget>

namespace GEP {

namespace System {
class Controller;
}

namespace Scope {

/*
 * Base class for displaying the worlds current content
 */
class WorldDisplay : public QWidget
{
public:
    WorldDisplay (QWidget* parent);
    virtual ~WorldDisplay ();

    struct DisplayMode { enum Type_t { ALL, BEST, WORST }; };
    typedef DisplayMode::Type_t DisplayMode_t;

    virtual void updateDisplay (const GEP::System::Controller* controller, DisplayMode_t display_mode) = 0;
};


}
}

#endif
