#-------------------------------------------------
#
# Project created by QtCreator 2014-08-28T11:19:31
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qsetup
TEMPLATE = app

DEPENDPATH += .

SOURCES += main.cpp\
    setupwizard.cpp

HEADERS  += \
    setupwizard.h

contains(QT_MAJOR_VERSION, 5){
    RC_ICONS = "icon/setup_green.ico"
}

RESOURCES +=QFramer0.qrc QFramer1.qrc QFramer2.qrc 7-Zip.qrc