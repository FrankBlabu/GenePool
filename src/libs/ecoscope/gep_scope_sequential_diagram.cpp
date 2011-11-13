/*
 * gep_scope_sequentual_diagram.cpp - Diagram for displaying sequential data
 *
 * Frank Cieslok, Sep. 2011
 */

#include "GEPScopeSequentialDiagram.h"

#include <limits>

#include <QtGui/QPainter>

namespace GEP {
namespace Scope {

//#**************************************************************************
// CLASS GEP::Scope::SequentialDiagram::Line
//#**************************************************************************

SequentialDiagram::Line::Line ()
  : _points  (),
    _color   (Qt::red)
{
}

//#**************************************************************************
// CLASS GEP::Scope::SequentialDiagram
//#**************************************************************************

/* Default line colors [STATIC] */
QList<QColor> SequentialDiagram::_default_colors;

/* Constructor */
SequentialDiagram::SequentialDiagram (QWidget* parent)
  : QWidget (parent),
    _lines (),
    _range_x (std::numeric_limits<double>::max (), -std::numeric_limits<double>::max ()),
    _range_y (std::numeric_limits<double>::max (), -std::numeric_limits<double>::max ())
{
  if (_default_colors.isEmpty ())
    {
      _default_colors.append (Qt::red);
      _default_colors.append (Qt::green);
      _default_colors.append (Qt::blue);
      _default_colors.append (Qt::yellow);
      _default_colors.append (Qt::cyan);
    }
}

/* Destructor */
SequentialDiagram::~SequentialDiagram ()
{
}

/*
 * Clear diagram
 */
void SequentialDiagram::clear ()
{
  _lines.clear ();
  _range_x = Range (std::numeric_limits<double>::max (), -std::numeric_limits<double>::max ());
  _range_y = Range (std::numeric_limits<double>::max (), -std::numeric_limits<double>::max ());
}

/*
 * Add point to the diagram
 *
 * \param id    Id of the line the point is added to
 * \param point Point to be added. The added points must form a sequence in terms
 *              of the x axis
 */
void SequentialDiagram::addPoint (int id, const QPointF& point)
{
  if (_lines.find (id) == _lines.end ())
    {
      Line line;
      line._color = _default_colors[id % _default_colors.size ()];
      _lines.insert (id, line);
    }

  Line& line = _lines[id];

  Q_ASSERT (line._points.isEmpty () || point.x () > line._points.back ().x ());

  line._points.append (point);
  _range_x.first = qMin (_range_x.first, point.x ());
  _range_x.second = qMax (_range_x.second, point.x ());
  _range_y.first = qMin (_range_y.first, point.y ());
  _range_y.second = qMax (_range_y.second, point.y ());
}

/*
 * Draw diagram content
 */
void SequentialDiagram::paintEvent (QPaintEvent* event)
{
  QWidget::paintEvent (event);

  QPainter painter (this);
  painter.fillRect (rect (), Qt::white);

  double scale_x = rect ().width () / (_range_x.second - _range_x.first);
  double scale_y = rect ().height () / (_range_y.second - _range_y.first);

  for (LineMap::const_iterator i = _lines.begin (); i != _lines.end (); ++i)
    {
      const Line& line = i.value ();

      if (!line._points.isEmpty ())
        {
          QPolygonF polyline;

          for (int i=0; i < line._points.size (); ++i)
            {
              const QPointF& point = line._points[i];

              polyline.append (QPointF ((point.x () - _range_x.first) * scale_x,
                                        height () - (point.y () - _range_y.first) * scale_y));
            }

          painter.setPen (line._color);
          painter.drawPolyline (polyline);
        }
    }
}


}
}
