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

SOURCES += main.cpp \
    gep_traveling_individual.cpp

HEADERS += \
    GEPTravelingIndividual.h

LIBS += -L$$(HOME)/lib -lecosystem -lecoscope
