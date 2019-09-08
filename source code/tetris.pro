TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    tetris.cpp \
    gamewidgets/bricks/brick_orientation.cpp \
    gamewidgets/bricks/brick_base.cpp \
    gamewidgets/clock.cpp \
    systemwidgets/keyboard.cpp \
    systemwidgets/screen.cpp \
    gamewidgets/square.cpp \
    painter.cpp \
    gamewidgets/map.cpp \
    gamewidgets/tetrisinfo.cpp \
    gamewidgets/brick.cpp

HEADERS += \
    gamewidgets/bricks/brick_base.h \
    gamewidgets/bricks/brick_orientation.h \
    gamewidgets/clock.h \
    systemwidgets/keyboard.h \
    systemwidgets/screen.h \
    gamewidgets/square.h \
    painter.h \
    gamewidgets/map.h \
    gamewidgets/tetrisinfo.h \
    gamewidgets/brick.h \
    gamewidgets/all.h \
    systemwidgets/all.h \
    tetris.h
