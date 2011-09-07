/*
 * GEPLogSelectionDisplay.h - Log display for selection steps
 *
 * Frank Cieslok, Sep. 2011
 */

#ifndef __GEP_LOG_SELECTION_DISPLAY_H__
#define __GEP_LOG_SELECTION_DISPLAY_H__

#include <QtGui/QWidget>

namespace GEP {

namespace System {
class Log;
class World;
}

namespace Scope {

class LogSelectionDisplayImpl;

/*
 * Log display for selection steps
 */
class LogSelectionDisplay : public QWidget
{
  Q_OBJECT

public:
  LogSelectionDisplay (System::World* world, QWidget* parent );
  virtual ~LogSelectionDisplay ();

private:
  LogSelectionDisplayImpl* _content;
  System::Log* _log;
};

}
}

#endif
