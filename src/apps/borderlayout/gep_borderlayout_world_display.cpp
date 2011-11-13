/*
 * gep_borderlayout_world_display.cpp - Class for displaying the world
 *
 * Frank Cieslok, Nov. 2011
 */

#define GEP_DEBUG

#include "GEPBorderLayoutWorldDisplay.h"
#include "GEPBorderLayoutWorld.h"
#include "GEPSystemController.h"
#include "GEPSystemDebug.h"

#include <QtCore/QPair>
#include <QtGui/QPainter>

#include <limits>


namespace GEP {
namespace BorderLayout {

//#**************************************************************************
// CLASS GEP::BorderLayout::WorldDisplay
//#**************************************************************************

/* Constructor */
WorldDisplay::WorldDisplay (const World* world, QWidget* parent)
  : GEP::Scope::WorldDisplay (world, parent),
    _world (world)
{
}

/* Destructor */
WorldDisplay::~WorldDisplay()
{
}

/* Update world display */
void WorldDisplay::updateDisplay (const GEP::System::Controller* controller, DisplayMode_t display_mode)
{
  const GEP::System::Population& population = controller->getPopulation ();

  double minimum_fitness = std::numeric_limits<double>::max ();
  double maximum_fitness = -std::numeric_limits<double>::max ();

  for (GEP::System::Population::ConstIterator i = population.begin (); i != population.end (); ++i)
    {
      const GEP::System::Individual& individual = *i;

      switch (display_mode)
        {
        case GEP::Scope::WorldDisplay::DisplayMode::ALL:
          _individuals.append (individual);
          break;

        case GEP::Scope::WorldDisplay::DisplayMode::BEST:
          {
            double fitness = _world->computeFitness (individual);
            if (fitness > maximum_fitness)
              {
                _individuals.clear ();
                _individuals.append (individual);
                maximum_fitness = fitness;
              }
          }
          break;

        case GEP::Scope::WorldDisplay::DisplayMode::WORST:
          {
            double fitness = _world->computeFitness (individual);
            if (fitness < minimum_fitness)
              {
                _individuals.clear ();
                _individuals.append (individual);
                minimum_fitness = fitness;
              }
          }
          break;

        case GEP::Scope::WorldDisplay::DisplayMode::SELECTED:
          {
            if (individual.getId () == getSelectedId ())
              _individuals.append (individual);
          }
          break;
        }
    }

  repaint ();
}

/* Repaint widget */
void WorldDisplay::paintEvent (QPaintEvent* event)
{
  QWidget::paintEvent (event);

  //
  // Step 1: Fill background
  //
  QPainter painter (this);
  painter.fillRect (rect (), Qt::white);

  //
  // Step 2: Paint world content
  //
  painter.setPen (Qt::black);
  painter.setBrush (Qt::white);

  for (int i=0; i < _individuals.size (); ++i)
    {
      const System::Individual& individual = _individuals[i];
      QList<World::Area> areas = _world->getAreas ();

      _world->layoutAreas (individual, &areas);

      for (int j=0; j < areas.size (); ++j)
        {
          const World::Area& area = areas[j];

          painter.drawLine (getPixelLine (QLineF (area.getConnectorPoint (), area.getRect ().center ())));
          painter.drawRect (getPixelRect (area.getRect ()));
        }
    }
}

/* Return point in pixel coordinates */
QPointF WorldDisplay::getPixelPoint (const QPointF& point) const
{
  return QPointF (point.x () * width () / _world->getFieldSize ().width (),
                  point.y () * height () / _world->getFieldSize ().height ());
}

/* Return a line in pixel coordinates */
QLineF WorldDisplay::getPixelLine (const QLineF& line) const
{
  return QLineF (getPixelPoint (line.p1 ()), getPixelPoint (line.p2 ()));
}

/* Return a rectangle in pixel coordinates */
QRectF WorldDisplay::getPixelRect (const QRectF& rect) const
{
  return QRectF (getPixelPoint (rect.topLeft ()), getPixelPoint (rect.bottomRight ()));
}


}
}


