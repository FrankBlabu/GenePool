/*
 * GEPScopeWorldDisplay.h - Base class for displaying the worlds current content
 *
 * Frank Cieslok, Sep. 2011
 */

#ifndef __GEP_SCOPE_WORLD_DISPLAY_H__
#define __GEP_SCOPE_WORLD_DISPLAY_H__

#include <GEPSystemObject.h>
#include <QtGui/QWidget>

namespace GEP {

namespace System {
class Controller;
class World;
}

namespace Scope {

/*
 * Base class for displaying the worlds current content
 */
class WorldDisplay : public QWidget
{
  Q_OBJECT

public:
    WorldDisplay (const System::World* world, QWidget* parent);
    virtual ~WorldDisplay ();

    struct DisplayMode { enum Type_t { ALL, BEST, WORST, SELECTED }; };
    typedef DisplayMode::Type_t DisplayMode_t;

    virtual void updateDisplay (const GEP::System::Controller* controller, DisplayMode_t display_mode) = 0;

signals:
    void signalUpdate ();

protected:
    const System::Object::Id& getSelectedId () const;

private slots:
    void slotIndividualFocusChanged (const System::Object::Id& id);

private:
    const System::World* _world;
    System::Object::Id _selected_id;
};


}
}

#endif
