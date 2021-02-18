#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, const InitialAccountSetup* initAccountSetup, const SymbolTernarySearchTree *pSymbolTST)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      pAccount(new Account(0, initAccountSetup->getInitBalance(), initAccountSetup->getAPIKey())),
      pSymbolTST(pSymbolTST)
{

    ui->setupUi(this);
    ui->symbolSearchLineEdit->setValidator(new QRegExpValidator(QRegExp("[A-Z]{0,4}"), 0));
    this->refresh();
}

MainWindow::~MainWindow(){
    delete ui;
    delete pAccount;
}


void MainWindow::refresh()
{
    this->ui->dynamicAccountBalanceLabel->setText(QString::number(this->pAccount->getAccountBalance(), 'f', 2));
    this->ui->dynamicAvailableFundsLabel->setText(QString::number(this->pAccount->getAvailableFunds(), 'f', 2));
}

void MainWindow::on_exitButton_clicked(){
    this->close();
}

void MainWindow::on_searchButton_clicked(){

}

void MainWindow::on_accountButton_clicked()
{
    this->pAccount->run();
}

void MainWindow::on_symbolSearchLineEdit_textChanged(const QString &arg1)
{
    if(arg1.length() < 0) return;

    QVector<const SymbolTernarySearchTree::Node *> vectRes = this->pSymbolTST->searchTST(arg1);
    const int32_t length = vectRes.length();
    QStandardItem *pRoot = model.invisibleRootItem();
    pRoot->removeRows(0, model.rowCount());

    for(int32_t r =0 ; r < length; ++r){
        pRoot->appendRow(new QStandardItem(vectRes[r]->symbol +"\t" +vectRes[r]->name + "\t" +vectRes[r]->industry));
    }
    ui->symbolListResults->setModel(&model);
}
