# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------
QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += ./QConfig.h \
    ./QInIConfig.h \
    ./QJsonConfig.h \
    ./WindowsTop.h
SOURCES += ./WindowsTop.cpp \
    ./QConfig.cpp \
    ./QInIConfig.cpp \
    ./QJsonConfig.cpp \
    ./main.cpp
FORMS += ./WindowsTop.ui
RESOURCES += WindowsTop.qrc
unix:!macx {
    LIBS += -lX11
}
# win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/QHotKey/QHotKey/release/ -lQHotkey1
# else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/QHotKey/QHotKey/debug/ -lQHotkey1
# else:unix: LIBS += -L$$OUT_PWD/QHotKey/QHotKey/ -lQHotkey1

# INCLUDEPATH += $$PWD/../QHotKey/QHotKey
# DEPENDPATH += $$PWD/../QHotKey/QHotKey

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/QHotkey/QHotkey/release/ -lQHotkey
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/QHotkey/QHotkey/debug/ -lQHotkey
else:unix: LIBS += -L$$OUT_PWD/QHotkey/QHotkey/ -lQHotkey

INCLUDEPATH += $$PWD/QHotkey/QHotkey
DEPENDPATH += $$PWD/QHotkey/QHotkey
