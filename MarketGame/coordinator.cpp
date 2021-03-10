#include "Coordinator.h"

/*Enusre that the singleton pointer is null to begin with*/
Coordinator* Coordinator::pCInstance = 0;

Coordinator *Coordinator::getInstance(){
    if(!pCInstance){
        pCInstance = new Coordinator();
    }
    return pCInstance;
}

int32_t Coordinator::run(const QApplication &coreApp){

    /*Read the known symbols initially, in a seperate thread*/
    QFuture<void> fReadKnownSymbols = QtConcurrent::run(&readKnownSymbols, &ReadKnownSymbols::run);

    /*Get the sign-in option from the user*/
    SignInOptionsDialog::Options selectedOption = this->runSignInOptions();

    /*If the symbols are not done yet, something went terribly wrong (takes 50-60ms at most)*/
    if(this->readKnownSymbols.getStatus() != ReadKnownSymbols::Status::Done){
        if(!fReadKnownSymbols.isFinished())fReadKnownSymbols.cancel();
        return -1;
    }

    /*Check if the user elected to either make a new sim, or load a previous save*/
    if(selectedOption == SignInOptionsDialog::Options::NewSimulation)
    {
       if(this->initialAccountSetup.run() != InitialAccountSetup::Status::ExitSuccessfully){
           return 0; //User Terminated the Progam
       }
       this->runMainWindow(coreApp);
    }
    else if(selectedOption == SignInOptionsDialog::Options::LoadPreviousSave)
    {
        printf("ToDo...\n");
    }
    return 0;
}

SignInOptionsDialog::Options Coordinator::runSignInOptions()
{
    /*Run Sign In Options*/
    SignInOptionsDialog::Options signInOption;
    do{
         signInOption = signInOptionsDialog.run();
         if(signInOption == SignInOptionsDialog::Options::TermsOfService){
             termsOfService.exec();                                              //Show Terms of Service
         }
         else if(signInOption==SignInOptionsDialog::Options::About){
             about.exec();                                                       //Show About
         }
   } while((signInOption == SignInOptionsDialog::Options::TermsOfService) || (signInOption == SignInOptionsDialog::Options::About));

    return signInOption;
}

InitialAccountSetup::Status Coordinator::runInitialAccountSetup(){
    return initialAccountSetup.run();
}

MainWindow::Status Coordinator::runMainWindow(const QApplication &coreApp){
    MainWindow mainWindow(0,&this->initialAccountSetup, readKnownSymbols.getSymbolTernarySearchTree());
    mainWindow.show();
    coreApp.exec();

    return mainWindow.getStatus();
}

