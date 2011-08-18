#
# ecotest.pro - Makefile for test case library
#

QT       += testlib

TARGET = test_main
CONFIG   += thread console qtestlib
CONFIG   -= app_bundle

INCLUDEPATH += ../ecosystem
INCLUDEPATH += ../ecoscope

SOURCES += test_main.cpp \
    test_random_number_generator.cpp \
    test_population_fitness_index.cpp \
    test_selection_operator.cpp \
    test_crossover_operator.cpp \
    test_mutation_operator.cpp

HEADERS += \
    TestMain.h

LIBS += -L$$(HOME)/lib -lecosystem -lecoscope
