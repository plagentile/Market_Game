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
    MainWindow  pMainWindow;
    SignInOptionsDialog  pSignInOptionsDialog;


    //ApplicationErrors::APP_ERRORS coreStatus = ApplicationErrors::APP_ERRORS::ExitSuccessfully;

    /*Run Get Sign In Options*/
    SignInOptionsDialog::Options signInOption = pSignInOptionsDialog.run();
    if(signInOption == SignInOptionsDialog::Options::NoOptionSelected){
        return -1;                                                          //User Terminated the Progam
    }
    else if(signInOption == SignInOptionsDialog::Options::NewSimulation){
        /*Run Get API Key*/
        GetUserAPIKey  getUserAPIKey;
        getUserAPIKey.run();
    }
    else
    {
        /*Load Previous Save*/
        printf("\nTodo...");
    }

    /*Run the Main Window*/
    pMainWindow.show();
    num = coreApp.exec();

    return num;
}

