#
# ecoscope.pro - qmake file for the scope library
#
# Frank Cieslok, Aug. 2011
#

TARGET   = ecoscope
TEMPLATE = lib
CONFIG  += sharedlib thread testlib
INCLUDEPATH += ../ecosystem

DESTDIR = $$(HOME)/lib

SOURCES += \
    gep_scope_main_window.cpp \
    gep_scope_tools.cpp \
    gep_scope_sequential_diagram.cpp \
    gep_scope_world_display.cpp \
    gep_scope_log_selection_display.cpp

HEADERS += \
    GEPScopeMainWindow.h \
    GEPScopeTools.h \
    GEPScopeSequentialDiagram.h \
    GEPScopeWorldDisplay.h \
    GEPScopeLogSelectionDisplay.h

FORMS += \
    gep_scope_main_window.ui \
    gep_scope_log_display_tree.ui











