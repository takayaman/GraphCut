TARGET = GraphCut

INCLUDEPATH += /usr/include

LIBS += -L/usr/lib/x86_64-linux-gnu \
  -lglog

QMAKE_CXXFLAGS += -std=c++11

HEADERS += \
    vertex.h \
    graph.h \
    edge.h

SOURCES += \
    vertex.cpp \
    main.cpp \
    graph.cpp \
    edge.cpp
