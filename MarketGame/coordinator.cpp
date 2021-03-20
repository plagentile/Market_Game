#include "Coordinator.h"

Coordinator::Coordinator(QObject *parent)
    : QObject(parent), mainWindow(0,&this->symbolTernarySearchTree),
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
}

int32_t Coordinator::run(QApplication *coreApp){

    if(coreApp)
    {
       /*Read the known symbols initially, in a seperate thread*/
       QFuture<void> fReadKnownSymbols = QtConcurrent::run(&this->symbolTernarySearchTree, &SymbolTernarySearchTree::setup);

       /*Get the sign-in option from the user*/
       this->signInOptionsDialog.show();
       coreApp->exec();
       return 0;
    }
    return -1;
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
    this->mainWindow.on_setupInitialAccount(key, initBalance);
    this->mainWindow.show();
}

void Coordinator::on_exitProgramRequested(){
   about.close();
   termsOfService.close();
   mainWindow.close();
}


