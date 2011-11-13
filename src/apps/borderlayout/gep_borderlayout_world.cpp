/*
 * gep_borderlayout_world.cpp - The world of the border layout problem
 *
 * Frank Cieslok, Nov. 2011
 */

#define GEP_DEBUG

#include <GEPSystemPopulation.h>
#include <GEPSystemShuffleComparator.h>
#include <GEPSystemDebug.h>

#include "GEPBorderLayoutWorld.h"

#include <algorithm>

#include <QtCore/QLineF>
#include <QtCore/QRectF>

namespace GEP {
namespace BorderLayout {


//#**************************************************************************
// CLASS GEP::BorderLayout::World::Area
//#**************************************************************************

/* Constructor */
World::Area::Area ()
  : _position        (),
    _size            (),
    _connector_point ()
{
}

/* Copy-Constructor */
World::Area::Area (const Area& toCopy)
  : _position        (toCopy._position),
    _size            (toCopy._size),
    _connector_point (toCopy._connector_point)
{
}

/* Gets the position */
const QPointF& World::Area::getPosition () const
{
  return _position;
}

/* Sets the position */
void World::Area::setPosition (const QPointF& position)
{
  _position = position;
}

/* Gets the size */
const QSizeF& World::Area::getSize () const
{
  return _size;
}

/* Sets the size */
void World::Area::setSize (const QSizeF& size)
{
  _size = size;
}

/* Gets the connector point position */
const QPointF& World::Area::getConnectorPoint () const
{
  return _connector_point;
}

/* Sets the connector point position */
void World::Area::setConnectorPoint (const QPointF& connector_point)
{
  _connector_point = connector_point;
}

/* Get the rectangle occupied by this area */
QRectF World::Area::getRect () const
{
  return QRectF (_position - QPointF (_size.width () / 2, _size.height () / 2), _size);
}

/* Debug output */
QDebug operator<< (QDebug out, const World::Area& area)
{
  out.nospace () << "Area { position=" << area.getPosition () << ", "
                 << "size=" << area.getSize () << ", "
                 << "connector=" << area.getConnectorPoint () << " }";
  return out;
}


//#**************************************************************************
// CLASS GEP::BorderLayout::World
//#**************************************************************************

/* Constructor */
World::World ()
  : GEP::System::World (),
    _random_number_generator (),
    _field_size              (),
    _connector_field_size    (),
    _number_of_areas         (0),
    _minimum_area_size       (0.0),
    _maximum_area_size       (0.0),
    _population_size         (0),
    _areas                   ()
{
}

/* Gets the field size */
const QSizeF& World::getFieldSize () const
{
  return _field_size;
}

/* Sets the field size */
void World::setFieldSize (const QSizeF& field_size)
{
  _field_size = field_size;
}

/* Gets the inner connector field size */
const QSizeF& World::getConnectorFieldSize () const
{
  return _connector_field_size;
}

/* Sets the inner connector field size */
void World::setConnectorFieldSize (const QSizeF& connector_field_size)
{
  _connector_field_size = connector_field_size;
}

/* Gets the number of areas */
int World::getNumberOfAreas () const
{
  return _number_of_areas;
}

/* Sets the number of areas */
void World::setNumberOfAreas (int number_of_areas)
{
  _number_of_areas = number_of_areas;
}

/* Gets the minimum area size */
double World::getMinimumAreaSize () const
{
  return _minimum_area_size;
}

/* Sets the minimum area size */
void World::setMinimumAreaSize (double minimum_area_size)
{
  _minimum_area_size = minimum_area_size;
}

/* Gets the maximum area size */
double World::getMaximumAreaSize () const
{
  return _maximum_area_size;
}

/* Sets the maximum area size */
void World::setMaximumAreaSize (double maximum_area_size)
{
  _maximum_area_size = maximum_area_size;
}

/* Gets the population size */
int World::getPopulationSize () const
{
  return _population_size;
}

/* Sets the population size */
void World::setPopulationSize (int population_size)
{
  _population_size = population_size;
}

/* Return the areas contained in this world */
const QList<World::Area>& World::getAreas () const
{
  return _areas;
}

/* Generate world */
void World::generateWorld ()
{
  Q_ASSERT (_field_size.isValid ());
  Q_ASSERT (_connector_field_size.isValid ());
  Q_ASSERT (_connector_field_size.width () <= _field_size.width ());
  Q_ASSERT (_connector_field_size.height () <= _field_size.height ());
  Q_ASSERT (_number_of_areas > 0);
  Q_ASSERT (_minimum_area_size > 0);
  Q_ASSERT (_maximum_area_size > 0);
  Q_ASSERT (_population_size > 0);

  //
  // Clear current world
  //
  _areas.clear ();

  //
  // Create random areas to be layouted
  //
  for (int i=0; i < _number_of_areas; ++i)
    {
      Area area;

      area.setSize (QSizeF (getRandom (_minimum_area_size, _maximum_area_size),
                            getRandom (_minimum_area_size, _maximum_area_size)));
      area.setPosition (QPointF (area.getSize ().width () / 2 + getRandom (0, _field_size.width () - area.getSize ().width ()),
                                 area.getSize ().height () / 2 + getRandom (0, _field_size.height () - area.getSize ().height ())));
      area.setConnectorPoint (QPointF ((_field_size.width () - _connector_field_size.width ()) / 2 + getRandom (0, _connector_field_size.width ()),
                                       (_field_size.height () - _connector_field_size.height ()) / 2 + getRandom (0, _connector_field_size.height ())));

      _areas.append (area);
    }
}

/* Generate random world population */
GEP::System::Population World::generatePopulation ()
{
  GEP::System::Population population;

  //
  // Build individual gene sequence consiisting of the area indices plus
  // three boundary separators
  //
  GEP::System::Individual::Chromosome chromosome;
  for (int i=0; i < _areas.size (); ++i)
    chromosome.append (i);

  chromosome.append (-1);
  chromosome.append (-2);
  chromosome.append (-3);

  //
  // Build a population of randomly shuffled initial gene sequences. Each single individual
  // in this sequence
  //
  for (int i=0; i < _population_size; ++i)
    {
      GEP::System::ShuffleComparator<GEP::System::Individual::Gene> comparator (chromosome);
      qSort (chromosome.begin (), chromosome.end (), comparator);
      population.add (GEP::System::Individual (chromosome));
    }

  return population;
}

/*
 * Layout a given set of areas according to an individual
 */
void World::layoutAreas (const System::Individual& individual, QList<Area>* areas) const
{
  Q_ASSERT (_field_size.isValid ());

  QRectF field (QPointF (0, 0), _field_size);

  struct Side { enum Type_t { TOP=0, BOTTOM=1, LEFT=2, RIGHT=3 }; };
  typedef Side::Type_t Side_t;

  QList<Area*> side_areas;
  double offset = 0;
  double max_top_border_offset = 0;
  double max_bottom_border_offset = 0;
  Side_t side = Side::TOP;

  //
  // The individual encodes both order and breaking points of the area distribution.
  //
  // Example: [3, 2, -1, 1, 7, 4, -2, 5, 8, -3, 6] means that areas '3' and '2' are
  //          distributed at the top border, than a break happens '-1' so that areas
  //          '1', '7' and '4' are distributed at the next border.
  //
  for (int i=0; i < individual.getSize (); ++i)
    {
      System::Individual::Gene gene = individual[i];

      //
      // Gene encodes an area index
      //
      if (gene >= 0)
        {
          Area& area = (*areas)[gene];
          side_areas.append (&area);

          //
          // Process individual side by side. The concret side order does not need to match the
          // individual gen splice order. That way, processing top and bottom border first the
          // necessary spaces for the remaining side border areas can easily be computed.
          //
          switch (side)
            {
            case Side::TOP:
              area.setPosition (QPointF (field.left () + offset + area.getSize ().width () / 2,
                                         field.top () + area.getSize ().height () / 2));
              offset += area.getSize ().width ();
              max_top_border_offset = qMax (max_top_border_offset, area.getSize ().height ());
              break;

            case Side::BOTTOM:
              area.setPosition (QPointF (field.right () - offset - area.getSize ().width () / 2,
                                         field.bottom () - area.getSize ().height () / 2));
              offset += area.getSize ().width ();
              max_bottom_border_offset = qMax (max_bottom_border_offset, area.getSize ().height ());
              break;

            case Side::LEFT:
              area.setPosition (QPointF (field.left () + area.getSize ().width () / 2,
                                         field.bottom () - offset - area.getSize ().height () / 2));
              offset += area.getSize ().height ();
              break;

            case Side::RIGHT:
              area.setPosition (QPointF (field.right () - area.getSize ().width () / 2,
                                         field.top () + offset + area.getSize ().height () / 2));
              offset += area.getSize ().height ();
              break;
            }
        }

      //
      // Gene encodes a side break. The areas placed so far are now moved for maximum
      // space efficiency.
      //
      else
        {
          switch (side)
            {
            case Side::TOP:
              {
                double space = (field.width () - offset) / (side_areas.size () + 1);

                for (int j=0; j < side_areas.size (); ++j)
                  {
                    Area* side_area = side_areas[j];
                    side_area->setPosition (QPointF (side_area->getPosition ().x () + (j + 1) * space,
                                                     side_area->getPosition ().y ()));
                  }

                side = Side::BOTTOM;
              }
              break;

            case Side::BOTTOM:
              {
                double space = (field.width () - offset) / (side_areas.size () + 1);

                for (int j=0; j < side_areas.size (); ++j)
                  {
                    Area* side_area = side_areas[j];
                    side_area->setPosition (QPointF (side_area->getPosition ().x () - (j + 1) * space,
                                                     side_area->getPosition ().y ()));
                  }

                side = Side::LEFT;
              }
              break;

            case Side::LEFT:
              {
                double space = (field.width () - offset - max_top_border_offset - max_bottom_border_offset) / (side_areas.size () + 1);

                for (int j=0; j < side_areas.size (); ++j)
                  {
                    Area* side_area = side_areas[j];
                    side_area->setPosition (QPointF (side_area->getPosition ().x (),
                                                     side_area->getPosition ().y () - (j + 1) * space));
                  }

                side = Side::RIGHT;
              }
              break;

            case Side::RIGHT:
              Q_ASSERT (false && "Side separator index corrupted");
              break;
            }

          offset = 0;
          side_areas.clear ();
        }
    }

  double space = (field.width () - offset - max_top_border_offset - max_bottom_border_offset) / (side_areas.size () + 1);

  for (int i=0; i < side_areas.size (); ++i)
    {
      Area* side_area = side_areas[i];
      side_area->setPosition (QPointF (side_area->getPosition ().x (),
                                       side_area->getPosition ().y () + (i + 1) * space));
    }
}

/* Compute fitness of a single individual */
double World::computeFitness (const Individual& individual) const
{
  QList<Area> areas (_areas);
  layoutAreas (individual, &areas);

  //
  // Criterion 1: Line crosses
  //
  int number_of_intersections = 0;

  for (int i=0; i < areas.size (); ++i)
    {
      const Area& area1 = areas[i];
      for (int j=i+1; j < areas.size (); ++j)
        {
          const Area& area2 = areas[j];

          QLineF line1 (area1.getConnectorPoint (), area1.getPosition ());
          QLineF line2 (area2.getConnectorPoint (), area2.getPosition ());

          QPointF intersection_point;
          if (line1.intersect (line2, &intersection_point) == QLineF::BoundedIntersection)
            ++number_of_intersections;
        }
    }

  return 1000 - number_of_intersections;
}

/*
 * Generate random number
 *
 * \param minimum Minimum value
 * \param maximum Maximum value
 */
double World::getRandom (double minimum, double maximum) const
{
  return minimum + (maximum - minimum) * _random_number_generator.generate () ;
}

}
}


