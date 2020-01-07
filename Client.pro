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
    askselect.cpp \
    dijkstrasalg.cpp \
    edge.cpp \
    gamelogic.cpp \
    graphwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    mainwindowchangingpresenter.cpp \
    mainwindowforcreatemultigame.cpp \
    mainwindowforenterexistinggame.cpp \
    mainwindowforsingleplay.cpp \
    node.cpp \
    singlgamepresenter.cpp \
    sockettest.cpp \
    statshandler.cpp \
    statslabel.cpp \
    strategy.cpp \
    structs.cpp \
    train.cpp

HEADERS += \
    Collections.h \
    askselect.h \
    dijkstrasalg.h \
    edge.h \
    gamelogic.h \
    graphwidget.h \
    mainwindow.h \
    mainwindowchangingpresenter.h \
    mainwindowforcreatemultigame.h \
    mainwindowforenterexistinggame.h \
    mainwindowforsingleplay.h \
    node.h \
    singlgamepresenter.h \
    sockettest.h \
    statshandler.h \
    statslabel.h \
    strategy.h \
    structs.h \
    train.h

FORMS += \
    askselect.ui \
    mainwindowforcreatemultigame.ui \
    mainwindowforenterexistinggame.ui \
    mainwindowforsingleplay.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
