#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix(":/files/img/chartLogo.png");
    ui->leftImageLabel->setPixmap(pix.scaled(ui->leftImageLabel->width(), ui->leftImageLabel->height(), Qt::KeepAspectRatioByExpanding));
}

MainWindow::~MainWindow(){
    delete ui;
}


