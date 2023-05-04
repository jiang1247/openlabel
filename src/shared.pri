QT += core gui widgets
CONFIG += c++17
DEFINES += QT_DEPRECATED_WARNINGS

BINDIR = $$PWD/../bin/

LIBS += -L$$BINDIR \
    -llogger \
    -lauxiliary \
    -lpermission \
    -lqtpropertybrowser

INCLUDEPATH += $$PWD/ $$PWD/qtpropertybrowser/
