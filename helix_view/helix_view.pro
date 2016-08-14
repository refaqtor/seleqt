#-------------------------------------------------
#
# Project created by QtCreator 2014-11-17T22:44:45
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = helix_view
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../helix/release/ -lhelix
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../helix/debug/ -lhelix
else:unix: LIBS += -L$$OUT_PWD/../helix/ -lhelix

INCLUDEPATH += $$PWD/../helix
DEPENDPATH += $$PWD/../helix

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../helix/release/libhelix.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../helix/debug/libhelix.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../helix/release/helix.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../helix/debug/helix.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../helix/libhelix.a

OTHER_FILES += \
    resources/idd8-2-0.json

RESOURCES += \
    resources.qrc
