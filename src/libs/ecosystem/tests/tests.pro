#
# tests.pro - Makefile for test cases
#
# Frank Cieslok, Aug. 2011
#

QT -= gui
QT += testlib

TARGET   = test_ecosystem
CONFIG  += thread qtestlib

SOURCES = test_random_number_generator.cpp

INCLUDEPATH = ..
LIBS += -L$$(HOME)/lib -lecosystem
