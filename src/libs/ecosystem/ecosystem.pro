#
# ecosystem.pro - Base class library
#
# Frank Cieslok, Aug. 2011
#

QT -= gui

TARGET   = ecosystem
TEMPLATE = lib
CONFIG  += sharedlib thread
DESTDIR = $$(HOME)/lib

SOURCES += \
    gep_system_controller.cpp \
    gep_system_crossover_operator.cpp \
    gep_system_fitness_operator.cpp \
    gep_system_individual.cpp \
    gep_system_mutation_operator.cpp \
    gep_system_operator.cpp \
    gep_system_population.cpp \
    gep_system_random_number_generator.cpp \
    gep_system_selection_operator.cpp \
    gep_system_termination_operator.cpp

HEADERS += \
    GEPSystemController.h \
    GEPSystemCrossoverOperator.h \
    GEPSystemFitnessOperator.h \
    GEPSystemIndividual.h \
    GEPSystemMutationOperator.h \
    GEPSystemOperator.h \
    GEPSystemPopulation.h \
    GEPSystemRandomNumberGenerator.h \
    GEPSystemSelectionOperator.h \
    GEPSystemTerminationOperator.h
