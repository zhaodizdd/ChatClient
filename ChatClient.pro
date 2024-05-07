QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/interface/chat/groupchat.cpp \
    src/interface/chat/onechat.cpp \
    src/interface/main/item.cpp \
    src/interface/main/chatitem.cpp \
    src/interface/main/firenditem.cpp \
    src/interface/main/groupitem.cpp \
    src/interface/main/mainwindow.cpp \
    src/interface/momon/alert.cpp \
    src/interface/momon/inputpopup.cpp \
    src/models/basemodel.cpp \
    src/net/clientnet.cpp \
    src/interface/login/login.cpp \
    src/main.cpp \
    src/models/usermodel.cpp \
    src/route/route.cpp \

HEADERS += \
    src/interface/chat/groupchat.h \
    src/interface/chat/onechat.h \
    src/interface/main/item.h \
    src/interface/main/chatitem.h \
    src/interface/main/firenditem.h \
    src/interface/main/groupitem.h \
    src/interface/main/mainwindow.h \
    src/interface/momon/alert.h \
    src/interface/momon/inputpopup.h \
    src/models/basemodel.h \
    src/net/clientnet.h \
    src/interface/login/login.h \
    src/models/usermodel.h \
    src/route/msg.h \
    src/route/responsestruct.h \
    src/route/route.h \

FORMS += \
    src/interface/chat/groupchat.ui \
    src/interface/chat/onechat.ui \
    src/interface/main/chatitem.ui \
    src/interface/main/item.ui \
    ui/alert.ui \
    ui/inputpopup.ui \
    ui/login.ui \
    ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES += \
    source/login/Icon-Arrow-down.png \
    source/login/Icon-Arrow-normal.png \
    source/login/close.png \
    source/login/code_hover.png \
    source/login/code_normal.png \
    source/login/icon-bigarrow-down.png \
    source/login/icon-bigarrow-hover.png \
    source/login/icon-bigarrow-normal.png \
    source/login/icon-close-down.png \
    source/login/icon-close-normal.png \
    source/login/icon-enter-down.png \
    source/login/icon-enter-hover.png \
    source/login/icon-enter-normal.png \
    source/login/icon-enter-undo.png \
    source/login/min.png \
    source/login/point-invisible-down.png \
    source/login/point-online-down.png \
    source/login/屏幕截图 2024-03-11 221111.png
