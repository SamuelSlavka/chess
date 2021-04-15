#ifndef MYTABPAGE_H
#define MYTABPAGE_H

#include <QWidget>
#include <QGridLayout>
#include <QStringList>
#include <QtCore>
#include <QtGui>
#include <QDialog>
#include <QListWidget>
#include <QThread>

#include <iostream>
#include "../Game.h"
#include <thread>
#include <chrono>
#include <mutex>

void print();

namespace Ui
{
    class MyTabPage;
}
/// @brief Thread handling playback.
class PlayThread : public QThread
{
    Q_OBJECT

    int direction = 1;
    int speed = 1;

    void run() override
    {
        while (direction != 0)
        {
            QThread::currentThread()->sleep(speed);
            if (direction > 0)
                emit shiftr();
            else if (direction < 0)
                emit shiftl();
        };
    }

public:
    /// @brief Stops playback.
    void pause()
    {
        direction = 0;
    }
    /// @brief Changes direction of playback.
    void fwrd()
    {
        direction = 1;
    }
    /// @brief Changes direction of playback.
    void bkwd()
    {
        direction = -1;
    }
    /// @brief Starts playback.
    void play()
    {
        if (!direction)
            direction = 1;
    }
    /// @brief Changes speed of playback.
    void speedf(int slider)
    {
        speed = (100 - slider) / 20 + 1;
    }

signals:
    /// @brief Signal to unmake move.
    void shiftl();
    /// @brief Signal to make move.
    void shiftr();
};

///@brief  Tab with single instance of Game.
class MyTabPage : public QWidget
{
    Q_OBJECT

public:
    QStringListModel *model;
    /// @brief return pointer to Game.
    Game &GetGame();
    explicit MyTabPage(QWidget *parent = nullptr);
    /// @brief returns pointer to board.
    QGridLayout &GetBoard();
    /// @brief Repaints elements on board.
    void RefreshBoard();
    ~MyTabPage();
    /// @brief Returns reference.
    /// @ return Reference to UI list.
    QListWidget &GetList();
    /// @brief increases index of current row.
    void IncCurrentRow();
    /// @brief  Returns index of current row.
    /// @ return int index
    int GetCurrentRow();
    /// @brief Unmakes move from move vector.
    /// @param multiple true if multiple shifts in row
    void LeftShift(bool multiple);
    /// @brief  Makes move from move vector.
    /// @param multiple true if multiple shifts in row
    void RightShift(bool multiple);
    /// @brief increase index of current move.
    void IncCurrentMove();
    /// @brief  Returns index of current move.
    /// @ return int index
    int GetCurrentMove();

signals:
    /// @brief Pauses playback of moves.
    void pause();
    /// @brief Starts playback of moves.
    void play();
    /// @brief  Sets playback to forward.
    void fwrd();
    /// @brief  Sets playback to backward.
    void bkwd();
    ///  @brief Sets speed of playback.
    /// @param position values 0-100.
    void speed(int sp);

private slots:
    /// @brief Unmakes one move.
    void on_buttonLeft_clicked();
    /// @brief Makes one move.
    void on_buttonRight_clicked();
    /// @brief Pauses playback of moves.
    void on_buttonPause_clicked();
    /// @brief Starts playback of moves.
    void on_buttonPlay_clicked();
    /// @brief Sets first move as current.
    void on_buttonRestart_clicked();
    /// @brief Sets move which is clicked as current.
    /// @param index Index of move.
    void on_listWidget_doubleClicked(const QModelIndex &index);
    // @brief Reverses last half move.
    void on_buttonUndo_clicked();
    /// @brief  Reverses undo.
    void on_buttonRedo_clicked();
    /// @brief  Sets playback to forward.
    void on_buttonForward_clicked();
    /// @brief  Sets playback to backward.
    void on_buttonBackward_clicked();
    /// @brief Sets speed of playback.
    /// @param position values 0-100.
    void on_horizontalSlider_sliderMoved(int position);

private:
    PlayThread thread;

    int CurrentRow;
    int CurrentMove;
    Ui::MyTabPage *ui;
    Game game;
};

#endif // MYTABPAGE_H
