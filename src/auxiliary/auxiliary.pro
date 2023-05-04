QT += core
CONFIG += c++17
TARGET = auxiliary
TEMPLATE = lib
CONFIG += shared
DESTDIR = $$PWD/../../bin/

HEADERS += \
    floatcompare.h \
    listcompare.h \
    recttransform.h \
    utils.h

SOURCES += \
    recttransform.cpp
