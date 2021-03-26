#include <QPixmap>
#include "mytabpage.h"
#include "ui_mytabpage.h"
#include "QtSquare.h"

/**
 * A single tab with single game.
 * @brief Source file for MyTabPage
 * @file mytabpage.cpp
 * @author Samuel Slavka (xslavk02)
 */

QGridLayout& MyTabPage::GetBoard(){
    return *(ui->BoardContainer);
}

Game& MyTabPage::GetGame(){
    return game;
}

MyTabPage::MyTabPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyTabPage)
{
    CurrentRow = -1;
    CurrentMove = 0;
    ui->setupUi(this);
    game.NewInit();
    QStringList *strlist = new QStringList();

    ui->BoardContainer->setSpacing(0);
    ui->BoardContainer->setMargin(0);

    for (int x=0;x<8;x++){
        for (int y=0;y<8;y++){
            QtSquare* m_myWidget = new QtSquare( this, ui->listWidget, strlist, x, y );

            if( (x+y)%2 ) m_myWidget->setStyleSheet(" background-color: rgb(204, 102, 0);");
            else m_myWidget->setStyleSheet(" background-color: rgb(255, 204, 102);");

            ui->BoardContainer->addWidget(m_myWidget,x,y);
        }
    }
}


MyTabPage::~MyTabPage()
{
    delete ui;
}

QListWidget& MyTabPage::GetList(){
    return *(ui->listWidget);
}

void MyTabPage::RefreshBoard()
{
    for (int x=0;x<8;x++){
        for (int y=0;y<8;y++){
            dynamic_cast<QtSquare*>(GetBoard().itemAt(x+y*8)->widget())->SetLabel(y,x);
        }
    }
}

void MyTabPage::LeftShift( bool multiple )
{
    int cr = ui->listWidget->currentRow();
    if ( multiple ) cr = CurrentRow;

    if( cr >= 0 )
    {
        if ( GetGame().MoveListLength()%2 != 0 && GetGame().MoveListLength() == CurrentMove ){
            GetGame().UnMakeMove( cr*2+2);
            CurrentMove--;
        }
        GetGame().UnMakeMove( cr*2+1);
        GetGame().UnMakeMove( cr*2);
        CurrentMove -= 2;

        ui->listWidget->setCurrentRow( cr-1 );
        CurrentRow = cr-1;
    }
    RefreshBoard();
}

void MyTabPage::RightShift( bool multiple )
{
    int cr = ui->listWidget->currentRow();
    if ( multiple ) cr = CurrentRow;

    if( cr+1 < (ui->listWidget->count()) )
    {
        if ( GetGame().MoveListLength()%2 != 0 && ui->listWidget->count() == (cr+2) ){
            GetGame().MakeMove( cr*2+4);
            CurrentMove++;
        }
        GetGame().MakeMove( cr*2+2);
        GetGame().MakeMove( cr*2+3);
        CurrentMove +=2 ;

        ui->listWidget->setCurrentRow( cr+1 );

        CurrentRow = cr+1;

        RefreshBoard();
    }
};


void MyTabPage::on_buttonLeft_clicked() {
    LeftShift( false );
}

void MyTabPage::on_buttonRight_clicked() {
    RightShift( false );
}


void MyTabPage::on_buttonBackward_clicked() {
    emit bkwd();
};
void MyTabPage::on_buttonForward_clicked() {
    emit fwrd();
};
void MyTabPage::on_buttonPause_clicked() {
    emit pause();
};

void MyTabPage::on_horizontalSlider_sliderMoved(int position){
   // std::cout << position << std::endl;
    emit speed(position);
}

void MyTabPage::on_buttonPlay_clicked()
{
    if ( !thread.isRunning() ) {
        if( !thread.isFinished() ) {
            connect(&thread, &PlayThread::shiftl, this, &MyTabPage::on_buttonLeft_clicked);
            connect(&thread, &PlayThread::shiftr, this, &MyTabPage::on_buttonRight_clicked);

        }

        connect(this, &MyTabPage::speed, &thread, &PlayThread::speedf);

        connect(this, &MyTabPage::bkwd, &thread, &PlayThread::bkwd);
        connect(this, &MyTabPage::fwrd, &thread, &PlayThread::fwrd);
        connect(this, &MyTabPage::pause, &thread, &PlayThread::pause);
        connect(this, &MyTabPage::play, &thread, &PlayThread::play);

        thread.start();
    }
    emit play();
}

void MyTabPage::on_buttonRestart_clicked()
{
    while ( 0 <= CurrentRow )
        LeftShift( false );
    if( GetGame().MoveListLength() != 1 )
        GetGame().SetWhiteTurn();
}

void MyTabPage::on_listWidget_doubleClicked(const QModelIndex &index)
{
    if ( index.row() > CurrentRow )
    {
        while ( index.row() > CurrentRow )
            RightShift( true );
    }
    else if ( index.row() < CurrentRow )
    {
        while ( index.row() < CurrentRow )
            LeftShift( true );
    }

    RefreshBoard();
}

void MyTabPage::IncCurrentRow() {
    CurrentRow++;
}
int MyTabPage::GetCurrentRow() {
    return CurrentRow;
}
int MyTabPage::GetCurrentMove() {
    return CurrentMove;
}

void MyTabPage::on_buttonUndo_clicked()
{
    if( CurrentMove > 0 && CurrentMove == GetGame().MoveListLength())
    {
        GetGame().UnMakeMove( CurrentMove-1 );
        CurrentMove--;
        if( GetGame().GetTurn() == black ) {
            ui->listWidget->setCurrentRow( CurrentRow-1 );
            CurrentRow--;
        }
        RefreshBoard();
    }
}

void MyTabPage::on_buttonRedo_clicked()
{
    if( CurrentMove+1 == GetGame().MoveListLength())
    {
        GetGame().MakeMove( CurrentMove );
        CurrentMove++;
        if( GetGame().GetTurn() == white ) {
            ui->listWidget->setCurrentRow( CurrentRow+1 );
            CurrentRow++;
        }
        RefreshBoard();
    }
}

void MyTabPage::IncCurrentMove()
{
    CurrentMove++;
}
