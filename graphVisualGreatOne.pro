QT += widgets

HEADERS += \
        edge.h \
        mainwindow.h \
        node.h \
        graphwidget.h

SOURCES += \
        edge.cpp \
        main.cpp \
        mainwindow.cpp \
        node.cpp \
        graphwidget.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/graphicsview/elasticnodes
INSTALLS += target

FORMS += \
    mainwindow.ui
