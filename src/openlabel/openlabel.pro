include(../shared.pri)

TARGET = openlabel
TEMPLATE = lib
CONFIG += shared
DESTDIR = $$BINDIR

include(datasource.pri)
include(graphics.pri)
include(shader.pri)
include(operation.pri)
include(event.pri)

HEADERS += \
    baseobject.h \
    document.h \
    factory.h \
    global.h \
    property.h \
    propertyiddispatcher.h \
    scene.h

SOURCES += \
    baseobject.cpp \
    document.cpp \
    factory.cpp \
    propertyiddispatcher.cpp \
    scene.cpp
