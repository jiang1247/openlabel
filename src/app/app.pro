include(../shared.pri)

TARGET = openlabel
TEMPLATE = app
DESTDIR = $$BINDIR

LIBS += -lopenlabel -lgui

SOURCES += \
    main.cpp

HEADERS +=

