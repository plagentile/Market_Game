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
    int num = 0;
    SignInOptionsDialog  signInOptionsDialog;
    TermsOfService termsOfService;
    About about;

    /*Run Get Sign In Options*/
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

     if(signInOption == SignInOptionsDialog::Options::NewSimulation){
        InitialAccountSetup  initialAccountSetup;
        if(initialAccountSetup.run() != ApplicationStatus::Status::ExitSuccessfully){
            return -1;                                                           //User Terminated the Progam
        }

        /*Run the Main Window*/
        MainWindow mainWindow(0, initialAccountSetup.getInitBalance(), initialAccountSetup.getAPIKey());
        mainWindow.show();
        num = coreApp.exec();
    }
    else{
        /*Load Previous Save*/
        printf("ToDo...\n");
    }
    return num;
}

