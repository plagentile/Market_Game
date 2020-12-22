#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), pSDialog(new SignInDialog)
{
    ui->setupUi(this);
    this->initGetSignIn();
}

MainWindow::~MainWindow(){
    delete ui;
    if(this->pSDialog) delete pSDialog;
}


void MainWindow::initGetSignIn()
{
   if(this->pSDialog)
   {
       pSDialog->setModal(true);
       pSDialog->exec();
   }
}

