#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), pSDialog(new SignInDialog)
{
    ui->setupUi(this);
    this->GetSignIn();
}

MainWindow::~MainWindow(){
    delete ui;
    if(this->pSDialog) delete pSDialog;
}


void MainWindow::GetSignIn()
{
   do
    {
        if(this->pSDialog)
        {

            pSDialog->setModal(true);
            pSDialog->exec();
            this->key = pSDialog->getAPIKey();
            printf("Key: %ls\n", qUtf16Printable(key) );
        }
    } while(pSDialog && !(this->keyOk()));
}

/**
 * @brief MainWindow::keyOk
 * @return
 * Can add basic key checks here
 */
bool MainWindow::keyOk()
{
    if(this->key.size() > 5)return true;
    return false;
}

