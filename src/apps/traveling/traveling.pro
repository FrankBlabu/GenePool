#
# traveling.pro - Solver for the traveling salesman problem via evolutionary algorithms
#
# Frank Cieslok, Aug. 2011
#

TARGET = traveling
TEMPLATE = app

CONFIG += qt
CONFIG += thread

QT += core
QT += gui
QT += widgets
QT += concurrent

DESTDIR = ..\..\lib

INCLUDEPATH += ../../libs/ecosystem
INCLUDEPATH += ../../libs/ecoscope

SOURCES += \
    gep_traveling_world_display.cpp \
    gep_traveling_world.cpp \
    gep_traveling_main.cpp

HEADERS += \
    GEPTravelingWorldDisplay.h \
    GEPTravelingWorld.h

LIBS += -L..\..\lib -lecosystem -lecoscope
