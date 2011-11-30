/*
 * GEPBorderLayoutWorld.h - The world of the border layout problem
 *
 * Frank Cieslok, Nov. 2011
 */

#ifndef __GEP_BORDERLAYOUT_WORLD__H__
#define __GEP_BORDERLAYOUT_WORLD__H__

#include <GEPSystemWorld.h>
#include <GEPSystemIndividual.h>
#include <GEPSystemRandomNumberGenerator.h>
#include <GEPSystemDebug.h>

#include <QtCore/QList>
#include <QtCore/QPointF>
#include <QtCore/QSizeF>

namespace GEP {
namespace BorderLayout {

//#**************************************************************************
// CLASS GEP::BorderLayout::Individual
//#**************************************************************************

/*
 * Individual: Single layout
 */
typedef GEP::System::Individual Individual;


//#**************************************************************************
// CLASS GEP::BorderLayout::World
//#**************************************************************************

/*
 * World of the border layout problem
 */
class World : public GEP::System::World
{
public:
  class Area
  {
  public:
    Area ();
    Area (const Area& toCopy);

    const QPointF& getPosition () const;
    void setPosition (const QPointF& position);

    const QSizeF& getSize () const;
    void setSize (const QSizeF& size);

    const QPointF& getConnectorPoint () const;
    void setConnectorPoint (const QPointF& connector_point);

    QRectF getRect () const;

  private:
    QPointF _position;
    QSizeF _size;
    QPointF _connector_point;
  };

public:
  World ();

  const QList<Area>& getAreas ()  const;

  const QSizeF& getFieldSize () const;
  void setFieldSize (const QSizeF& field_size);

  const QSizeF& getConnectorFieldSize () const;
  void setConnectorFieldSize (const QSizeF& connector_field_size);

  int getNumberOfAreas () const;
  void setNumberOfAreas (int number_of_areas);

  double getMinimumAreaSize () const;
  void setMinimumAreaSize (double minimum_area_size);

  double getMaximumAreaSize () const;
  void setMaximumAreaSize (double maximum_area_size);

  int getPopulationSize () const;
  void setPopulationSize (int population_size);

  virtual void generateWorld ();
  virtual GEP::System::Population generatePopulation ();

  virtual int getNumberOfFitnessValues () const;
  virtual FitnessType_t getFitnessType (int index) const;
  virtual double getFitnessWeight (int index) const;
  virtual double computeFitness (int index, const Individual& individual) const;

  void layoutAreas (const System::Individual& individual, QList<Area>* areas) const;

private:
  double getRandom (double minimum, double maximum) const;

private:
  mutable System::RandomNumberGenerator _random_number_generator;

  //
  // Configuration
  //
  QSizeF _field_size;
  QSizeF _connector_field_size;
  int _number_of_areas;
  double _minimum_area_size;
  double _maximum_area_size;
  int _population_size;

  //
  // Areas
  //
  QList<Area> _areas;

  //
  // Constants
  //
  static const int FITNESS_INDEX_INTERSECTIONS    = 0;
  static const int FITNESS_INDEX_CONNECTOR_LENGTH = 1;
};

QDebug operator<< (QDebug out, const World::Area& area);

}
}

#endif
