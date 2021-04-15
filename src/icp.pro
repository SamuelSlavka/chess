#-------------------------------------------------
#
# Project created by QtCreator 2019-03-17T16:44:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = icp
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
    main.cpp \
    QT/mainwindow.cpp \
    Board.cpp \
    Game.cpp \
    Log.cpp \
    Piece.cpp \
    Square.cpp \
    Figures/Bishop.cpp \
    Figures/King.cpp \
    Figures/Knight.cpp \
    Figures/Pawn.cpp \
    Figures/Queen.cpp \
    Figures/Rook.cpp \
    QT/mytabpage.cpp \
    QT/QtSquare.cpp

HEADERS += \
    QT/mainwindow.h \
    Square.h \    
    Board.h \
    Game.h \
    Headers.h \
    Log.h \
    Piece.h \
    Figures/Bishop.h \
    Figures/King.h \
    Figures/Knight.h \    
    Figures/Pawn.h \    
    Figures/Queen.h \
    Figures/Rook.h \    
    QT/mytabpage.h \
    QT/QtSquare.h

FORMS += \
    QT/mainwindow.ui \
    QT/mytabpage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
