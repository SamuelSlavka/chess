#ifndef QTSQUARE_H
#define QTSQUARE_H

#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include "mytabpage.h"
#include "../Piece.h"

///@brief  Square in gui.
class QtSquare : public QWidget
{
    Q_OBJECT
public:
    /**
    * @brief Constructor sets initial values.
    */
    explicit QtSquare(MyTabPage *parent = nullptr, QListWidget *lv = nullptr, QStringList *strlist = nullptr, int x = -1, int y = -1);

    QLabel *label;

    /**
    * @brief Sets piece picture.
    * @param x X cordinate for updating.
    * @param y Y cordinate for updating.
    */
    void RefreshBoard(QGridLayout *grid);

    /**
    * @brief Sets piece picture.
    * @param x X cordinate for updating.
    * @param y Y cordinate for updating.
    */
    void SetLabel(int x, int y);
public slots:

    /**
    * @brief Proceses click on square.
    * @param event Press event.
    */
    void mousePressEvent(QMouseEvent *event);

private:
    QStringList *str;
    /// @brief pointer to Mytabpage parent.
    MyTabPage *parentptr;
    /// @brief  pointer to list in parent.
    QListWidget *list;

    QWidget *widget;
};

#endif // QTSQUARE_H
