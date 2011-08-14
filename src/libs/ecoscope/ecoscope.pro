#
# ecoscope.pro - qmake file for the scope library
#
# Frank Cieslok, Aug. 2011
#

TARGET   = ecoscope
TEMPLATE = lib
CONFIG  += staticlib thread testlib
INCLUDEPATH += ../ecosystem

DESTDIR = $$(HOME)/lib

SOURCES += \
    gep_scope_main_window.cpp \
    gep_scope_tools.cpp

HEADERS += \
    GEPScopeMainWindow.h \
    GEPScopeTools.h

FORMS += \
    gep_scope_main_window.ui
