
SOURCES += \
    $$PWD/pn532.c \
    $$PWD/pn532_rpi.c \
    $$PWD/qpn532.cpp

HEADERS += \
    $$PWD/pn532.h \
    $$PWD/pn532_rpi.h \
    $$PWD/qpn532.h

INCLUDEPATH += $$PWD

LIBS += -lwiringPi
