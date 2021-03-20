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


