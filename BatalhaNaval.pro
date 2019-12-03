TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        batalhanaval.cpp \
        main.cpp \
        mysocket.cpp \
        navio.cpp \
        pos.cpp \
        tabuleiro.cpp

HEADERS += \
    batalhanaval.h \
    mysocket.h \
    navio.h \
    pos.h \
    tabuleiro.h
