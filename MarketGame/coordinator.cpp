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

    /*Read the known symbols initially*/
    QFuture<void> fReadKnownSymbols = QtConcurrent::run(&readKnownSymbols, &ReadKnownSymbols::run);

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
         else if(signInOption == SignInOptionsDialog::Options::NoOptionSelected){
             return -1;                                                          //User Terminated the Progam
         }
    } while((signInOption == SignInOptionsDialog::Options::TermsOfService) || (signInOption == SignInOptionsDialog::Options::About));

     /*Check if the user elected to either make a new sim, or load a previous save*/
     if(signInOption == SignInOptionsDialog::Options::NewSimulation){
        InitialAccountSetup  initialAccountSetup;
        if(initialAccountSetup.run() != InitialAccountSetup::Status::ExitSuccessfully){
            return -1;                                                           //User Terminated the Progam
        }

        /*Run the Main Window, if the symbols are not done yet, something went terribly wrong*/
        if(this->readKnownSymbols.getStatus() != ReadKnownSymbols::Status::Done){
            if(!fReadKnownSymbols.isFinished())fReadKnownSymbols.cancel();
            return -1;
        }

        MainWindow mainWindow(0,&initialAccountSetup, readKnownSymbols.getSymbolTernarySearchTree());
        mainWindow.show();
        return coreApp.exec();
    }
    else{
        /*Load Previous Save*/
        printf("ToDo...\n");
    }
    return 0;
}

