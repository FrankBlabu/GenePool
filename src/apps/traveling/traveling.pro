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
    traveling.cpp

HEADERS +=

LIBS += -L$$(HOME)/lib -lecosystem -lecoscope
