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
    MainWindow  mainWindow;
    SignInOptionsDialog  signInOptionsDialog;
    TermsOfService termsOfService;


    //ApplicationErrors::App_Status coreStatus = ApplicationErrors::APP_ERRORS::ExitSuccessfully;

    /*Run Get Sign In Options*/
    SignInOptionsDialog::Options signInOption;
    do
    {
         signInOption = signInOptionsDialog.run();
         if(signInOption == SignInOptionsDialog::Options::TermsOfService){
             /*Show Terms of Service*/
             termsOfService.exec();
         }
    } while((signInOption == SignInOptionsDialog::Options::TermsOfService) || (signInOption == SignInOptionsDialog::Options::About));


    if(signInOption == SignInOptionsDialog::Options::NoOptionSelected){
        return -1;                                                          //User Terminated the Progam
    }
    else if(signInOption == SignInOptionsDialog::Options::NewSimulation){
        /*Run Get API Key*/
        GetUserAPIKey  getUserAPIKey;
        if(getUserAPIKey.run() != ApplicationStatus::Status::ExitSuccessfully){
            return -1;
        }
    }
    else
    {
        /*Load Previous Save*/
        printf("ToDo...\n");
    }



    /*Run the Main Window*/
    mainWindow.show();
    num = coreApp.exec();

    return num;
}

