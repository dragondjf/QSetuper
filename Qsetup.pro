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

# build dir
BuildDir =build_$$QT_VERSION

CONFIG(debug, debug|release) {
    DESTDIR = $$PWD/$$BuildDir/debug
    OBJECTS_DIR = $$PWD/$$BuildDir/debug/.obj
    MOC_DIR = $$PWD/$$BuildDir/debug/.moc
    RCC_DIR = $$PWD/$$BuildDir/debug/.rcc
    UI_DIR = $$PWD/$$BuildDir/debug/.ui
} else {
    DESTDIR = $$PWD/$$BuildDir/release
    OBJECTS_DIR = $$PWD/$$BuildDir/release/.obj
    MOC_DIR = $$PWD/$$BuildDir/release/.moc
    RCC_DIR = $$PWD/$$BuildDir/release/.rcc
    UI_DIR = $$PWD/$$BuildDir/release/.ui
}


SOURCES += main.cpp\
    QSetup/customsetuppage.cpp \
    QSetup/defaultsetuppage.cpp \
    QSetup/fbasedialog.cpp \
    QSetup/finishpage.cpp \
    QSetup/ftitlebar.cpp \
    QSetup/futil.cpp \
    QSetup/installbarpage.cpp \
    QSetup/pictureview.cpp \
    QSetup/setupwizard.cpp


HEADERS  += \
    QSetup/customsetuppage.h \
    QSetup/defaultsetuppage.h \
    QSetup/fbasedialog.h \
    QSetup/finishpage.h \
    QSetup/ftitlebar.h \
    QSetup/futil.h \
    QSetup/installbarpage.h \
    QSetup/pictureview.h \
    QSetup/setupwizard.h


contains(QT_MAJOR_VERSION, 5){
    RC_ICONS = "skin/setup_green.ico"
}

RESOURCES +=QFramer0.qrc QFramer1.qrc QFramer2.qrc 7-Zip.qrc skin.qrc