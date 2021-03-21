#include "Coordinator.h"

Coordinator::Coordinator(QObject *parent)
    : QObject(parent), mainWindow(nullptr,&this->symbolTernarySearchTree),
      initialAccountSetup(nullptr), signInOptionsDialog(nullptr),
      termsOfService(nullptr),about(nullptr)
{

    QObject::connect(&signInOptionsDialog, &SignInOptionsDialog::showAboutPageRequested, this, &Coordinator::on_showAboutPageRequested);
    QObject::connect(&signInOptionsDialog, &SignInOptionsDialog::showTermsOfServicePageRequested, this, &Coordinator::on_showTermsOfServiceRequested);
    QObject::connect(&signInOptionsDialog, &SignInOptionsDialog::makeNewSimulationRequested, this, &Coordinator::on_makeNewSimulationRequested);
    QObject::connect(&signInOptionsDialog, &SignInOptionsDialog::loadNewSimulationRequested, this, &Coordinator::on_loadPreviousSimulationRequested);

    QObject::connect(&initialAccountSetup, &InitialAccountSetup::loginRequested, this, &Coordinator::on_loginRequested);

    QObject::connect(&mainWindow, &MainWindow::showAboutPageRequested, this, &Coordinator::on_showAboutPageRequested);
    QObject::connect(&mainWindow, &MainWindow::showTermsOfServicePageRequested, this, &Coordinator::on_showTermsOfServiceRequested);
    QObject::connect(&mainWindow, &MainWindow::exitProgram, this, &Coordinator::on_exitProgramRequested);
    QObject::connect(this, &Coordinator::loginAfterInitialAccount, &mainWindow, &MainWindow::on_setupInitialAccount);
}

void Coordinator::run(){

    /*Read the known symbols initially, in a seperate thread*/
    QFuture<void> fReadKnownSymbols = QtConcurrent::run(&this->symbolTernarySearchTree, &SymbolTernarySearchTree::setup);

    this->signInOptionsDialog.show();
}

void Coordinator::on_showAboutPageRequested(){
    this->about.show();
}

void Coordinator::on_showTermsOfServiceRequested(){
    this->termsOfService.show();
}

void Coordinator::on_makeNewSimulationRequested(){
    if(signInOptionsDialog.isActiveWindow()){
        this->signInOptionsDialog.close();
    }
    this->initialAccountSetup.show();
}

void Coordinator::on_loadPreviousSimulationRequested()
{
}

void Coordinator::on_loginRequested(const QString& key, const int32_t initBalance){
    if(initialAccountSetup.isActiveWindow()){
        this->initialAccountSetup.close();
    }
    emit this->loginAfterInitialAccount(key, initBalance);
    this->mainWindow.show();
}

void Coordinator::on_exitProgramRequested(){
   about.close();
   termsOfService.close();
   mainWindow.close();
}


