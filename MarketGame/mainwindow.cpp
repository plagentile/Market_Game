#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), pGetUserAPIKey(new GetUserAPIKey)
{
    ui->setupUi(this);
    this->GetSignIn();
}

MainWindow::~MainWindow(){
    delete ui;
    if(this->pGetUserAPIKey) delete pGetUserAPIKey;
}


void MainWindow::GetSignIn()
{
   do
    {
        if(this->pGetUserAPIKey)
        {

            pGetUserAPIKey->setModal(true);
            pGetUserAPIKey->exec();
            this->key = pGetUserAPIKey->getAPIKey();
            printf("Key: %ls\n", qUtf16Printable(key) );
        }
    } while(pGetUserAPIKey && !(this->keyOk()));
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

