#include "mainwindow.h"

/**
 * Main window.
 * @brief Source file for MainWindow
 * @file mainwindow.cpp
 * @author Samuel Slavka (xslavk02)
 */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->tabWidget);
}



MainWindow::~MainWindow()
{
    delete ui;
}

MyTabPage* MainWindow::GetCurrentTab()
{
    return qobject_cast<MyTabPage *>(ui->tabWidget->currentWidget());
}

void MainWindow::on_actionNew_triggered()
{
    int order = ui->tabWidget->count();
    MyTabPage* tab =new MyTabPage;
    ui->tabWidget->addTab(static_cast<QWidget*>(tab) ,  QString("game ")+QString::number(order));
};

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open file");
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this,"Warning","Could not open file: "+ file.errorString());
        return;
    }

    //create mew board
    on_actionNew_triggered();
    ui->tabWidget->setCurrentIndex( ui->tabWidget->count()-1 );

    QTextStream in(&file);



    std::vector<Move> moves;
    int index =  ui->tabWidget->count()-1;
    while (!in.atEnd())
    {
        QString line = in.readLine();
        if ( !GetCurrentTab()->GetGame().ParseNotation( moves, line.toUtf8().constData() )) {
            ui->tabWidget->removeTab( index );
            QMessageBox::warning(this,"Warning","Could not parse: "+ file.errorString());
            return;
        }


        GetCurrentTab()->IncCurrentMove();  //todo krajsie
        GetCurrentTab()->IncCurrentMove();
        GetCurrentTab()->IncCurrentRow();

        GetCurrentTab()->GetList().addItem(line);
        GetCurrentTab()->GetList().setCurrentRow( GetCurrentTab()->GetList().count() - 1 );

        GetCurrentTab()->GetGame().MakeMovesOpen( moves );
        moves.clear();
    }

    GetCurrentTab()->RefreshBoard();

}

void MainWindow::on_actionSave_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save file");
    QFile file(filename);
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this,"Warning","Could not save file: "+ file.errorString());
        return;
    }
    setWindowTitle(filename);
    QTextStream out(&file);
    for(int i = 0; i < GetCurrentTab()->GetList().count(); ++i) {
        out << GetCurrentTab()->GetList().item(i)->text();
        out << "\n";
    }
    file.close();
}

void MainWindow::on_actionAbout_triggered()
{
 QMessageBox::warning(this,"About","Project made by Samuel Slavka, xslavk02");
//         warning(this,"Warning","Could not open file: "+ file.errorString());
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->removeTab(index);
}
