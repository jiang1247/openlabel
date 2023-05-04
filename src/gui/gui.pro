include(../shared.pri)

TARGET = gui
TEMPLATE = lib
CONFIG += shared
DESTDIR = $$BINDIR

LIBS += -lopenlabel

include(action.pri)
include(mouseproxy.pri)
include(property.pri)

HEADERS += \
    bindingdatasourcedialog.h \
    datalistdockwidget.h \
    documentchangedevent.h \
    editarea.h \
    graphicsitem.h \
    graphicslistdockwidget.h \
    graphicspropertybrowser.h \
    graphicsscene.h \
    graphicsview.h \
    mainwindow.h \
    operationsdockwidget.h

SOURCES += \
    bindingdatasourcedialog.cpp \
    datalistdockwidget.cpp \
    documentchangedevent.cpp \
    editarea.cpp \
    graphicsitem.cpp \
    graphicslistdockwidget.cpp \
    graphicspropertybrowser.cpp \
    graphicsscene.cpp \
    graphicsview.cpp \
    mainwindow.cpp \
    operationsdockwidget.cpp

RESOURCES += \
    gui.qrc
