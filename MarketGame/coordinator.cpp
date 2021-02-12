#include "Coordinator.h"

/*Enusre that the singleton pointer is null to begin with*/
Coordinator* Coordinator::pCInstance = 0;

Coordinator *Coordinator::getInstance(){
    if(!pCInstance){
        pCInstance = new Coordinator();
    }
    return pCInstance;
}

int32_t Coordinator::run(const QApplication &coreApp)
{
    //SearchSymbol searchSymbol;

    //searchSymbol.show();
    //searchSymbol.exec();

    /*Read the known symbols initially*/
    if(readKnownSymbols.run() != ReadKnownSymbols::Status::Normal){
        return -1;
    }

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
        if(initialAccountSetup.run() != ApplicationStatus::Status::ExitSuccessfully){
            return -1;                                                           //User Terminated the Progam
        }

        /*Run the Main Window*/
        MainWindow mainWindow(0,&initialAccountSetup, readKnownSymbols.getBST());
        mainWindow.show();
        return coreApp.exec();
    }
    else{
        /*Load Previous Save*/
        printf("ToDo...\n");
    }
    return 0;
}

