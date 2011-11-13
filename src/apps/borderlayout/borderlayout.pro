#
# traveling.pro - Solver for the traveling salesman problem via evolutionary algorithms
#
# Frank Cieslok, Aug. 2011
#

QT += core gui

TARGET   = borderlayout
TEMPLATE = app
CONFIG  += thread
INCLUDEPATH += ../../libs/ecosystem
INCLUDEPATH += ../../libs/ecoscope

SOURCES += \
    gep_borderlayout_world_display.cpp \
    gep_borderlayout_world.cpp \
    gep_borderlayout_main.cpp

HEADERS += \
    GEPBorderLayoutWorldDisplay.h \
    GEPBorderLayoutWorld.h

LIBS += -L$$(HOME)/lib -lecosystem -lecoscope
