/*
 * GEPScopeSequentialDiagram.h - Diagram for sequential data
 *
 * Frank Cieslok, Sep. 2011
 */

#ifndef __GEP_SCOPE_SEQUENTIAL_DIAGRAM_H__
#define __GEP_SCOPE_SEQUENTIAL_DIAGRAM_H__

#include <QtCore/QPair>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtGui/QWidget>

namespace GEP {
namespace Scope {

/*
 * Diagram for sequential data
 */
class SequentialDiagram : public QWidget
{
public:
    SequentialDiagram (QWidget* parent);
    virtual ~SequentialDiagram ();

    void clear ();
    void addPoint (int id, const QPointF& point);

protected:
    virtual void paintEvent (QPaintEvent* event);

private:
    struct Line
    {
    public:
      Line ();

    public:
      QList<QPointF> _points;
      QColor _color;
    };

    typedef QMap<int, Line> LineMap;
    LineMap _lines;

    typedef QPair<double, double> Range;
    Range _range_x;
    Range _range_y;

    static QList<QColor> _default_colors;
};

}
}


#endif
