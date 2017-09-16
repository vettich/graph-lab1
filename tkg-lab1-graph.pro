TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

#CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    graph.cpp \
    dsu.cpp \
    graphs/graphadjlist.cpp \
    graphs/graphadjmatrix.cpp \
    graphs/graphbase.cpp \
    graphs/graphlistofedges.cpp

HEADERS += \
    graph.h \
    dsu.h \
    graphs/graphadjlist.h \
    graphs/graphadjmatrix.h \
    graphs/graphbase.h \
    graphs/graphlistofedges.h

