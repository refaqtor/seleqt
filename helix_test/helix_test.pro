#-------------------------------------------------
#
# Project created by QtCreator 2014-11-09T02:29:47
#
#-------------------------------------------------

QT       += testlib sql

QT       -= gui

TARGET = tst_helix_test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_helix_test.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

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

RESOURCES += \
    data.qrc

OTHER_FILES += \
    resources/idd8-2-0.json
