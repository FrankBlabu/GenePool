#
# ecosystem.pro - Base class library
#
# Frank Cieslok, Aug. 2011
#

TARGET = ecosystem
TEMPLATE = lib

CONFIG += qt
CONFIG += thread
CONFIG += static

QT += core
QT -= gui
QT += concurrent

DESTDIR = ..\..\lib

INCLUDEPATH += .
INCLUDEPATH += C:\Users\Frank\Applications\boost\boost_1_53_0

SOURCES += \
    gep_system_controller.cpp \
    gep_system_crossover_operator.cpp \
    gep_system_fitness_operator.cpp \
    gep_system_individual.cpp \
    gep_system_mutation_operator.cpp \
    gep_system_operator.cpp \
    gep_system_population.cpp \
    gep_system_selection_operator.cpp \
    gep_system_termination_operator.cpp \
    gep_system_object.cpp \
    gep_system_population_fitness_index.cpp \
    gep_system_debug.cpp \
    gep_system_world.cpp \
    gep_system_shuffle_comparator.cpp \
    gep_system_notifier.cpp \
    gep_system_random_number_generator.cpp \
    gep_system_controller_thread.cpp \
    gep_system_init.cpp \
    gep_system_temperature_function.cpp

HEADERS += \
    GEPSystemController.h \
    GEPSystemCrossoverOperator.h \
    GEPSystemFitnessOperator.h \
    GEPSystemIndividual.h \
    GEPSystemMutationOperator.h \
    GEPSystemOperator.h \
    GEPSystemPopulation.h \
    GEPSystemSelectionOperator.h \
    GEPSystemTerminationOperator.h \
    GEPSystemObject.h \
    GEPSystemPopulationFitnessIndex.h \
    GEPSystemDebug.h \
    GEPSystemWorld.h \
    GEPSystemShuffleComparator.h \
    GEPSystemNotifier.h \
    GEPSystemRandomNumberGenerator.h \
    GEPSystemControllerThread.h \
    GEPSystemInit.h \
    GEPSystemTemperatureFunction.h
