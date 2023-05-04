QT += core
CONFIG += c++17
TARGET = permission
TEMPLATE = lib
CONFIG += shared
DESTDIR = $$PWD/../../bin/

HEADERS += \
    permission.h \
    permissionmanager.h \
    role.h \
    user.h \
    usermanager.h

SOURCES += \
    permission.cpp \
    permissionmanager.cpp \
    role.cpp \
    user.cpp \
    usermanager.cpp
