#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, const InitialAccountSetup* initAccountSetup)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->account = new Account(0, initAccountSetup->getInitBalance(), initAccountSetup->getAPIKey());
    this->refresh();
}

MainWindow::~MainWindow(){
    delete ui;
    delete account;
}

void MainWindow::refresh()
{
    this->ui->dynamicAccountBalanceLabel->setText(QString::number(this->account->getAccountBalance(), 'f', 2));
    this->ui->dynamicAvailableFundsLabel->setText(QString::number(this->account->getAvailableFunds(), 'f', 2));
}

void MainWindow::on_exitButton_clicked(){
    this->close();
}

void MainWindow::on_searchButton_clicked()
{
    printf("TODO....");
}

void MainWindow::on_accountButton_clicked()
{
    this->account->run();
}
