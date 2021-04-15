#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "mytabpage.h"
#include <QObject>

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

namespace Ui
{
    class MainWindow;
}

///@brief  Main widnow of application.
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /// @brief Returns pointer to current tab
    MyTabPage *GetCurrentTab();
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /// @brief  New Game.
    void on_actionNew_triggered();
    /// @brief Opens saved game.
    void on_actionOpen_triggered();
    /// @brief  Saves current game.
    void on_actionSave_triggered();
    /// @brief Shows about.
    void on_actionAbout_triggered();
    /**
    * @brief Closes tab at index.
    * @param index Index of tab to close.
    */
    void on_tabWidget_tabCloseRequested(int index);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
