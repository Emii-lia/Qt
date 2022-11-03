#-------------------------------------------------
#
# Project created by QtCreator 2022-10-12T15:03:10
#
#-------------------------------------------------

QT       += core gui sql
QT       += core gui charts
QT += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myProject
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        adduser.cpp \
        ch_pass.cpp \
        dialog.cpp \
        finance.cpp \
        historic.cpp \
        inscription.cpp \
        liste_generale.cpp \
        main.cpp \
        mainwindow.cpp \
        menu.cpp \
        modifuser.cpp \
        profil.cpp \
        reinscription.cpp \
        rmuser.cpp

HEADERS += \
        adduser.h \
        ch_pass.h \
        dialog.h \
        finance.h \
        historic.h \
        inscription.h \
        liste_generale.h \
        mainwindow.h \
        menu.h \
        modifuser.h \
        profil.h \
        reinscription.h \
        rmuser.h

FORMS += \
        adduser.ui \
        ch_pass.ui \
        dialog.ui \
        finance.ui \
        historic.ui \
        inscription.ui \
        liste_generale.ui \
        mainwindow.ui \
        menu.ui \
        modifuser.ui \
        profil.ui \
        reinscription.ui \
        rmuser.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets.qrc

DISTFILES +=
