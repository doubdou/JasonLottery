#-------------------------------------------------
#
# Project created by QtCreator 2016-01-13T22:27:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JasonLottery
TEMPLATE = app


SOURCES += main.cpp\
        lottery.cpp \
    helpdialog.cpp \
    stackedwidget.cpp

HEADERS  += lottery.h \
    helpdialog.h \
    stackedwidget.h

FORMS    += lottery.ui \
    helpdialog.ui \
    stackedwidget.ui

CONFIG += c++11

RESOURCES += \
    res.qrc

OTHER_FILES += \
    myapp.rc

RC_FILE = myapp.rc
