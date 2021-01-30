TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        models/digger.cpp \
        models/edge.cpp \
        models/graph.cpp \
        models/node.cpp \
        modules/file.cpp \
        utility/mathematics.cpp

HEADERS += \
	base.h \
	models/digger.h \
	models/edge.h \
	models/graph.h \
	models/node.h \
	modules/file.h \
	utility/mathematics.h \
	utility/types.h

DISTFILES += \
	todolist.txt
