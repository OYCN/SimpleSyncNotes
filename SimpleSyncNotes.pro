QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    configure.cpp \
    filetreewidget.cpp \
    httpnet.cpp \
    inet.cpp \
    main.cpp \
    mainwindow.cpp \
    networkcenter.cpp \
    serverconfigdialog.cpp

HEADERS += \
    configure.h \
    filetreewidget.h \
    httpnet.h \
    inet.h \
    mainwindow.h \
    networkcenter.h \
    serverconfigdialog.h

FORMS += \
    mainwindow.ui \
    serverconfigdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Res.qrc
