#-------------------------------------------------
#
# Project created by QtCreator 2014-11-09T02:23:21
#
#-------------------------------------------------

QT       += sql

QT       -= gui

TARGET = helix
TEMPLATE = lib
CONFIG += staticlib

SOURCES += helix.cpp \
    cJSON.c

HEADERS += helix.h \
    cJSON.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
