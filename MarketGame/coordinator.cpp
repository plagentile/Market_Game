#include "Coordinator.h"

/*Enusre that the singleton pointer is null to begin with*/
Coordinator* Coordinator::pCInstance = 0;

Coordinator::Coordinator()
    :pMainWindow(new MainWindow()), pGetUserAPIKey(new GetUserAPIKey())
{
}

Coordinator::~Coordinator(){
    delete pMainWindow;
    delete pGetUserAPIKey;
}

void Coordinator::ShowMainWindow(){
    this->pMainWindow->show();

}

void Coordinator::ShowGetAPIKey(){
    int num = 0;
    this->pGetUserAPIKey->setModal(true);

    do{
        num = this->pGetUserAPIKey->exec();
    } while(num != 0 && (pGetUserAPIKey->keyOk()));

    printf("Key: %ls\n", qUtf16Printable(pGetUserAPIKey->getAPIKey()) );
}



void Coordinator::run()
{
    this->ShowGetAPIKey();
    this->ShowMainWindow();
}

Coordinator *Coordinator::getInstance(){
    if(!pCInstance){
        pCInstance = new Coordinator();
    }
    return pCInstance;
}
