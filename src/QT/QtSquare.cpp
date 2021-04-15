#include "QtSquare.h"
#include <QGridLayout>

/**
 * Representation of Square in qt.
 * @brief Source file for QtSquare
 * @file QtSquare.cpp
 * @author Samuel Slavka (xslavk02)
 */

void QtSquare::SetLabel(int y, int x)
{
    QPixmap pix;
    int w= 90;
    int h= 90;

    if ( !parentptr->GetGame().IsUsed(x,y) ){
        pix.load(":/icons/EMPTY.png");
        label->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
        label->repaint();
        return;
    }

    char ptype = parentptr->GetGame().GetPieceType(x,y);
    char pcolor = parentptr->GetGame().GetPieceColor(x,y);

    QString path = ":/icons/";
    path += ptype;
    path += pcolor;
    path += ".png";

    pix.load(path);
    label->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    label->repaint();
};


QtSquare::QtSquare( MyTabPage *parent, QListWidget *lv, QStringList *strlist,  int x, int y) : QWidget(parent), str(strlist), list(lv)
{
    widget = new QWidget(this);
    widget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    widget->setFixedSize(100,100);

    label = new QLabel(widget);

    parentptr = parent;
    widget->heightForWidth(true);

    SetLabel(x,y);
}

void QtSquare::RefreshBoard( QGridLayout* grid )
{
    for (int x=0;x<8;x++){
        for (int y=0;y<8;y++){

            QLayoutItem* wg = grid->itemAt(x + y*8);
            if( (x+y)%2 ) wg->widget()->setStyleSheet(" background-color: rgb(204, 102, 0); ");
            else wg->widget()->setStyleSheet(" background-color: rgb(255, 204, 102); ");
            dynamic_cast<QtSquare*>(wg->widget())->SetLabel(y,x);
        }
    }
}

void QtSquare::mousePressEvent(QMouseEvent *event)
{
    event->accept();
    auto layout = dynamic_cast<QGridLayout*>(this->parentWidget()->layout());

    int index = layout->indexOf(this);
    Q_ASSERT(index >= 0);
    int rs,cs;
    bool undoflag = false;
    int x,y;
    layout->getItemPosition(index, &y, &x, &rs, &cs);

    if (!parentptr->GetGame().PossibleMoves.empty())
    {
        int len1 = parentptr->GetGame().MoveListLength();
        //undo redo
        if ((parentptr->GetCurrentMove())+1 == len1 ){
            parentptr->GetGame().MoveListPopback();
            // if black undo remove from list in view and clear notation
            if( parentptr->GetGame().GetTurn() == black ){
                parentptr->GetList().takeItem( parentptr->GetList().count()-1 );
                parentptr->GetGame().ClearOneMoveNotation();
                undoflag = true;
            }
            if( parentptr->GetCurrentMove() == 0 )
                parentptr->GetGame().ClearNotation();
        }
        //shift left right
        else if ( parentptr->GetCurrentMove() < len1 && parentptr->GetGame().MoveListLength() > 0)
        {
            while ( (parentptr->GetCurrentMove()) < parentptr->GetGame().MoveListLength() )
            {
                parentptr->GetGame().MoveListPopback();
                parentptr->GetGame().MoveListPopback();
                //changed
                if ( parentptr->GetGame().MoveListLength() % 2 != 0 && (parentptr->GetCurrentMove()+1) == parentptr->GetGame().MoveListLength()){
                    parentptr->GetGame().MoveListPopback();
                }
                parentptr->GetList().takeItem( parentptr->GetList().count()-1 );
            }
            parentptr->GetGame().ClearNotation();

        };
        //check if move was made
        len1 = parentptr->GetGame().MoveListLength();
        parentptr->GetGame().MakeMove(x,y);
        RefreshBoard( layout );

        if ( len1 < parentptr->GetGame().MoveListLength()){
            parentptr->IncCurrentMove();

            //every other turn notation is added to list
            if( (len1 < parentptr->GetGame().MoveListLength() && parentptr->GetGame().GetTurn() == white) || undoflag ) {
                QString notation = QString::fromStdString(parentptr->GetGame().GetNotationLine());
                list->addItem(notation);
                list->setCurrentRow( list->count() - 1 );
                parentptr->IncCurrentRow();
            }
        }
    }
    else
    {
        parentptr->GetGame().GetMoves(x, y);
        for ( auto it = parentptr->GetGame().PossibleMoves.begin(); it != parentptr->GetGame().PossibleMoves.end(); it++ )
        {
            auto grid =  dynamic_cast<QGridLayout*>(this->parentWidget()->layout());
            QLayoutItem* wg = grid->itemAt(it->ToX + it->ToY*8);

            wg->widget()->setStyleSheet("background-color:red;");
        }
    }
}
