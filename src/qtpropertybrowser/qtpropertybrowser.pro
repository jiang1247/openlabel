QT += widgets
CONFIG += c++17
TEMPLATE = lib
CONFIG += shared
TARGET = QtPropertyBrowser
DEFINES += QTPROPERTYBROWSER_LIBRARY
DESTDIR = $$PWD/../../bin/

RESOURCES += $$PWD/qtpropertybrowser.qrc

HEADERS += \
    qtbuttonpropertybrowser.h \
    qteditorfactory.h \
    qtgroupboxpropertybrowser.h \
    qtpropertybrowser.h \
    qtpropertybrowserutils_p.h \
    qtpropertymanager.h \
    qttreepropertybrowser.h \
    qtvariantproperty.h

SOURCES += \
    qtbuttonpropertybrowser.cpp \
    qteditorfactory.cpp \
    qtgroupboxpropertybrowser.cpp \
    qtpropertybrowser.cpp \
    qtpropertybrowserutils.cpp \
    qtpropertymanager.cpp \
    qttreepropertybrowser.cpp \
    qtvariantproperty.cpp


