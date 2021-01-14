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
    MainWindow  pMainWindow;
    GetUserAPIKey  pGetUserAPIKey;
    SignInOptionsDialog  pSignInOptionsDialog;

    /*Run Get Sign In Options*/
    pSignInOptionsDialog.setModal(true);
    pSignInOptionsDialog.exec();

    /*Run Get API Key*/
    int num = 0;
    pGetUserAPIKey.setModal(true);

    do{
        num = pGetUserAPIKey.exec();
    } while(num != 0 && (pGetUserAPIKey.keyOk()));

    printf("Key: %ls\n", qUtf16Printable(pGetUserAPIKey.getAPIKey()) );


    /*Run the Main Window*/
    pMainWindow.show();
    num = coreApp.exec();

    return num;
}

