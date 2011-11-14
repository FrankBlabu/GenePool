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

INCLUDEPATH += /local/applications/boost/include

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
    gep_system_init.cpp

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
    GEPSystemInit.h
















