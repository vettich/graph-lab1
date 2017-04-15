TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

#CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    graph.cpp \
    graphadjlist.cpp \
    graphadjmatrix.cpp \
    graphlistofedges.cpp \
    graphbase.cpp

HEADERS += \
    graph.h \
    graphadjlist.h \
    graphadjmatrix.h \
    graphlistofedges.h \
    graphbase.h

