#include "Coordinator.h"

Coordinator::Coordinator(QObject *parent)
    : QObject(parent), initialAccountSetup(nullptr), signInOptionsDialog(nullptr),termsOfService(nullptr),about(nullptr)
{
}

int32_t Coordinator::run(const QApplication &coreApp){

    /*Read the known symbols initially, in a seperate thread*/
    QFuture<void> fReadKnownSymbols = QtConcurrent::run(&this->symbolTernarySearchTree, &SymbolTernarySearchTree::setup);

    /*Get the sign-in option from the user*/
    SignInOptionsDialog::Options selectedOption = this->runSignInOptions();

    /*If the symbols are not done yet, something went terribly wrong (takes 50-60ms at most)*/
    if(this->symbolTernarySearchTree.getStatus() != SymbolTernarySearchTree::Status::Ready){
        if(!fReadKnownSymbols.isFinished())fReadKnownSymbols.cancel();
        return -1;
    }

    /*Check if the user elected to either make a new sim, or load a previous save*/
    if(selectedOption == SignInOptionsDialog::Options::NewSimulation){
        return this->runMainWindow(coreApp, MainWindow::Status::NewSimulation);
    }
    else if(selectedOption == SignInOptionsDialog::Options::LoadPreviousSave){
        return this->runMainWindow(coreApp, MainWindow::Status::LoadSimulation);
    }

    return 0;   //User Quit Before selecting to either load or make a new simulation.
}

SignInOptionsDialog::Options Coordinator::runSignInOptions(){
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

int32_t Coordinator::runMainWindow(const QApplication &coreApp, MainWindow::Status status){

    while(status ==MainWindow::Status::NewSimulation || status == MainWindow::Status::LoadSimulation )
    {
        if(this->initialAccountSetup.run() != InitialAccountSetup::Status::ExitSuccessfully){
            return 0; //User Terminated the Progam
        }

        if(status == MainWindow::Status::NewSimulation){
            MainWindow mainWindow(0,this->initialAccountSetup.getInitBalance(),this->initialAccountSetup.getAPIKey(), &this->symbolTernarySearchTree);
            mainWindow.show();
            coreApp.exec();
            status = mainWindow.getStatus();
        }
        else if(status == MainWindow::Status::LoadSimulation){
            printf("\nTodo...");
            break;
        }
    }
    if(status == MainWindow::Status::ExitError) return -1;
    return 0;
}


