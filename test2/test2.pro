QT     += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG += c++11

LIBS +=-lGLEW -lglfw -lglut -lGLEW -lGLU -lGL -lX11 -lXxf86vm -lrt -lm -pthread -lXrandr -lXinerama


TARGET = test2
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    test2_oglwidget.cpp

HEADERS += test2_oglwidget.h
