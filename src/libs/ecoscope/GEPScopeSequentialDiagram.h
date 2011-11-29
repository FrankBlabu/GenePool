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
  class Properties
  {
  public:
    Properties ();
    Properties (const Properties& toCopy);

    bool getShowTendency () const;
    void setShowTendency (bool show);

    const QColor& getLineColor () const;
    void setLineColor (const QColor& line_color);

    const QString& getLegendText () const;
    void setLegendText (const QString& legend_text);

  private:
    bool _show_tendency;
    QColor _line_color;
    QString _legend_text;
  };

public:
    SequentialDiagram (QWidget* parent);
    virtual ~SequentialDiagram ();

    Properties getProperties (int id) const;
    void setProperties (int id, const Properties& properties);

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
    };

    typedef QMap<int, Line> LineMap;
    LineMap _lines;

    typedef QMap<int, Properties> PropertiesMap;
    PropertiesMap _properties;

    typedef QPair<double, double> Range;
    Range _range_x;
    Range _range_y;
};

}
}


#endif
