/*
 * gep_traveling_world_display.cpp - Class for displaying the world
 *
 * Frank Cieslok, Sep. 2011
 */

#include "GEPTravelingWorldDisplay.h"
#include "GEPTravelingWorld.h"
#include "GEPSystemController.h"

#include <QtCore/QPair>
#include <QtGui/QPainter>

#include <limits>

namespace GEP {
namespace Traveling {

//#**************************************************************************
// CLASS GEP::Traveling::WorldDisplay
//#**************************************************************************

/* Constructor */
WorldDisplay::WorldDisplay(const World* world, QWidget* parent)
  : GEP::Scope::WorldDisplay (parent),
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
  Q_ASSERT (_world->getSize () > 0);

  _individuals.clear ();

  //
  // Step 1: Compute coordinate range
  //
  typedef QPair<double, double> Range;
  Range range_x (std::numeric_limits<double>::max (), -std::numeric_limits<double>::max ());
  Range range_y (std::numeric_limits<double>::max (), -std::numeric_limits<double>::max ());

  for (uint i=0; i < _world->getSize (); ++i)
    {
      const QPointF& city = (*_world)[i];

      range_x.first = std::min (range_x.first, city.x ());
      range_x.second = std::max (range_x.second, city.x ());
      range_y.first = std::min (range_y.first, city.y ());
      range_y.second = std::max (range_y.second, city.y ());
    }

  double scale_x = width () / (range_x.second - range_x.first);
  double scale_y = height () / (range_y.second - range_y.first);

  //
  // Step 2: Compute lines representing the individuals
  //
  Range range_fitness (std::numeric_limits<double>::max (), -std::numeric_limits<double>::max ());

  const GEP::System::Population& population = controller->getPopulation ();
  for (GEP::System::Population::ConstIterator i = population.begin (); i != population.end (); ++i)
    {
      const GEP::System::Individual& individual = *i;

      QPolygonF line;

      for (uint i=0; i < individual.getSize (); ++i)
        {
          QPointF pos = (*_world)[individual[i].toUInt ()];

          line.push_back (QPointF ((pos.x () - range_x.first) * scale_x,
                                   (pos.y () - range_y.first) * scale_y));
        }

      switch (display_mode)
        {
        case GEP::Scope::WorldDisplay::DisplayMode::ALL:
          _individuals.push_back (line);
          break;

        case GEP::Scope::WorldDisplay::DisplayMode::BEST:
          {
            double fitness = _world->getFitness (individual);
            if (fitness > range_fitness.second)
              {
                _individuals.clear ();
                _individuals.push_back (line);
                range_fitness.second = fitness;
              }
          }
          break;

        case GEP::Scope::WorldDisplay::DisplayMode::WORST:
          {
            double fitness = _world->getFitness (individual);
            if (fitness < range_fitness.first)
              {
                _individuals.clear ();
                _individuals.push_back (line);
                range_fitness.first = fitness;
              }
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

  QPainter painter (this);
  painter.fillRect (rect (), Qt::white);

  painter.setPen (Qt::red);

  qDebug () << _individuals.size ();

  for (int i=0; i < _individuals.size (); ++i)
    painter.drawPolyline (_individuals[i]);
}


}
}


