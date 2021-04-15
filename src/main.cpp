#include <QApplication>
#include <QApplication>
#include <vector> 

#include "Game.h"
#include "QT/mainwindow.h"
#include "QT/mainwindow.h"

/**
 * Main window of the application.
 * @brief Source file for main
 * @file main.cpp
 * @author Samuel Slavka (xslavk02)
 */

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}


/*! \mainpage BlockEdior
 *
 * \section intro_sec Introduction
 *	 ICP project 2019
 * Navrhněte a implementujte aplikaci pro přehrávání šachových partií.
 * \section author_sec Authors 
 * Samuel Slavka (xslavk02)
 */