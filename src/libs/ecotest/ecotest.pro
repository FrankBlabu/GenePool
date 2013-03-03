#
# ecotest.pro - Makefile for test case library
#

TARGET = ecoscope
TEMPLATE = lib

CONFIG += qt
CONFIG += static
CONFIG += thread
CONFIG += testlib

QT += core
QT += gui
QT += widgets

DESTDIR = ..\..\lib

INCLUDEPATH += .
INCLUDEPATH += ..\ecosystem
INCLUDEPATH += ..\ecoscope
INCLUDEPATH += C:\Users\Frank\Applications\boost\boost_1_53_0

SOURCES += test_main.cpp \
    test_random_number_generator.cpp \
    test_population_fitness_index.cpp \
    test_selection_operator.cpp \
    test_crossover_operator.cpp \
    test_mutation_operator.cpp \
    test_shuffle_comparator.cpp

HEADERS += \
    TestMain.h

LIBS += -L$$(HOME)/lib -lecosystem -lecoscope
