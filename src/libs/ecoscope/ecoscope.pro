#
# ecoscope.pro - qmake file for the scope library
#
# Frank Cieslok, Aug. 2011
#

TARGET   = ecoscope
TEMPLATE = lib

CONFIG += qt
CONFIG += static
CONFIG += thread

QT += core
QT += gui
QT += widgets

DESTDIR = ..\..\lib

INCLUDEPATH += .
INCLUDEPATH += ..\ecosystem
INCLUDEPATH += C:\Users\Frank\Applications\boost\boost_1_53_0

SOURCES += \
    gep_scope_main_window.cpp \
    gep_scope_tools.cpp \
    gep_scope_sequential_diagram.cpp \
    gep_scope_world_display.cpp \
    gep_scope_selection_operator_display.cpp \
    gep_scope_operator_display.cpp \
    gep_scope_crossover_operator_display.cpp \
    gep_scope_mutation_operator_display.cpp \
    gep_scope_init.cpp

HEADERS += \
    GEPScopeMainWindow.h \
    GEPScopeTools.h \
    GEPScopeSequentialDiagram.h \
    GEPScopeWorldDisplay.h \
    GEPScopeSelectionOperatorDisplay.h \
    GEPScopeOperatorDisplay.h \
    GEPScopeCrossoverOperatorDisplay.h \
    GEPScopeMutationOperatorDisplay.h \
    GEPScopeInit.h

FORMS += \
    gep_scope_main_window.ui


























































