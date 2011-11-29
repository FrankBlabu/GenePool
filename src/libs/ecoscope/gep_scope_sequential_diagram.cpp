/*
 * gep_scope_sequentual_diagram.cpp - Diagram for displaying sequential data
 *
 * Frank Cieslok, Sep. 2011
 */

#define GEP_DEBUG

#include "GEPScopeSequentialDiagram.h"
#include <GEPSystemDebug.h>

#include <limits>

#include <QtGui/QFontMetrics>
#include <QtGui/QPainter>

namespace GEP {
namespace Scope {

//#**************************************************************************
// CLASS GEP::Scope::SequentialDiagram::Properties
//#**************************************************************************

/* Constructor */
SequentialDiagram::Properties::Properties ()
  : _show_tendency (false),
    _line_color    (Qt::blue),
    _legend_text   ()
{
}

/* Copy constructor */
SequentialDiagram::Properties::Properties (const Properties& toCopy)
  : _show_tendency (toCopy._show_tendency),
    _line_color    (toCopy._line_color),
    _legend_text   (toCopy._legend_text)
{
}

/* Get if the tendency line should be shown */
bool SequentialDiagram::Properties::getShowTendency () const
{
  return _show_tendency;
}

/* Set if the tendency line should be shown */
void SequentialDiagram::Properties::setShowTendency (bool show)
{
  _show_tendency = show;
}

/* Get line color */
const QColor& SequentialDiagram::Properties::getLineColor () const
{
  return _line_color;
}

/* Set line color */
void SequentialDiagram::Properties::setLineColor (const QColor& line_color)
{
  _line_color = line_color;
}

/* Get legend text */
const QString& SequentialDiagram::Properties::getLegendText () const
{
  return _legend_text;
}

/* Set legend text */
void SequentialDiagram::Properties::setLegendText (const QString& legend_text)
{
  _legend_text = legend_text;
}


//#**************************************************************************
// CLASS GEP::Scope::SequentialDiagram::Line
//#**************************************************************************

SequentialDiagram::Line::Line ()
  : _points ()
{
}


//#**************************************************************************
// CLASS GEP::Scope::SequentialDiagram
//#**************************************************************************

/* Constructor */
SequentialDiagram::SequentialDiagram (QWidget* parent)
  : QWidget (parent),
    _lines (),
    _range_x (std::numeric_limits<double>::max (), -std::numeric_limits<double>::max ()),
    _range_y (std::numeric_limits<double>::max (), -std::numeric_limits<double>::max ())
{
}

/* Destructor */
SequentialDiagram::~SequentialDiagram ()
{
}

/*
 * Get properties for a line
 *
 * \param id Id of the line
 * \return Properties of this line
 */
SequentialDiagram::Properties SequentialDiagram::getProperties (int id) const
{
  Properties properties;

  PropertiesMap::ConstIterator pos = _properties.find (id);
  if (pos != _properties.end ())
    properties = pos.value ();

  return properties;
}

/*
 * Set properties for a line
 *
 * \param id         Id of the line
 * \param properties Properties to be set
 */
void SequentialDiagram::setProperties (int id, const Properties& properties)
{
  _properties[id] = properties;
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

  //
  // Setup painter and background
  //
  QPainter painter (this);
  painter.fillRect (rect (), Qt::white);

  //
  // Compute value scaling
  //
  double scale_x = rect ().width () / (_range_x.second - _range_x.first);
  double scale_y = rect ().height () / (_range_y.second - _range_y.first);

  //
  // Draw diagram lines
  //
  QStringList legend_texts;

  for (LineMap::const_iterator i = _lines.begin (); i != _lines.end (); ++i)
    {
      int id = i.key ();
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

          Properties properties;

          PropertiesMap::ConstIterator pos = _properties.find (id);
          if (pos != _properties.end ())
            properties = pos.value ();

          if (!properties.getLegendText ().isEmpty ())
            legend_texts.append (properties.getLegendText ());

          painter.setPen (properties.getLineColor ());
          painter.drawPolyline (polyline);

          if (properties.getShowTendency () && polyline.size () >= 10)
            {
              painter.setPen (QPen (properties.getLineColor (), 1.0, Qt::DotLine));
              painter.drawLine (polyline.first (), polyline.last ());
            }
        }
    }

  //
  // Draw diagram legend
  //
  int offset = 0;

  for (int i=0; i < legend_texts.size (); ++i)
    {
      const QString& text = legend_texts[i];

      QRect rect = fontMetrics ().boundingRect (text);
      rect.moveTo (0, offset);

      painter.drawText (rect, Qt::AlignLeft | Qt::AlignHCenter | Qt::TextSingleLine, text);
      offset = rect.bottom ();
    }
}


}
}
