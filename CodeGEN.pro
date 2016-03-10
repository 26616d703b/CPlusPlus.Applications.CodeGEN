QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ClassGEN
TEMPLATE = app


SOURCES += \
    cpphighlighter.cpp \
    generatedcodewindow.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS  += \
    cpphighlighter.h \
    generatedcodewindow.h \
    mainwindow.h

RC_ICONS = Resources/Icons/app.ico
