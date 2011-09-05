#
# traveling.pro - Solver for the traveling salesman problem via evolutionary algorithms
#
# Frank Cieslok, Aug. 2011
#

QT += core gui

TARGET   = traveling
TEMPLATE = app
CONFIG  += thread
INCLUDEPATH += ../../libs/ecosystem
INCLUDEPATH += ../../libs/ecoscope

SOURCES += \
    gep_traveling_world_display.cpp \
    gep_traveling_world.cpp \
    gep_traveling_main.cpp

HEADERS += \
    GEPTravelingWorldDisplay.h \
    GEPTravelingWorld.h

LIBS += -L$$(HOME)/lib -lecosystem -lecoscope
