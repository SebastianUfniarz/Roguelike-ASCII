TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        gracz.cpp \
        main.cpp \
        poziom.cpp \
        przeciwnik.cpp \
        systemgry.cpp

HEADERS += \
    gracz.h \
    poziom.h \
    przeciwnik.h \
    systemgry.h
