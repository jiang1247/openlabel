QT += core
CONFIG += c++17
TARGET = logger
TEMPLATE = lib
CONFIG += shared
DESTDIR = $$PWD/../../bin/

HEADERS += \
    consoleloghandler.h \
    log.h \
    logger.h \
    loghandler.h \
    logmanager.h

SOURCES += \
    consoleloghandler.cpp \
    logger.cpp \
    logmanager.cpp
