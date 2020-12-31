#ifndef COORDINATOR_H
#define COORDINATOR_H
#include "mainwindow.h"
#include "getuserapikey.h"
#include "signinoptionsdialog.h"
/*
    This class is responsible for controlling the flow of the program
    It launches the threads that will build the URL list from a raw txt file
    As well as ensuring that another thread successfully connects to the websites,
    and extracts the appropiate information.

    Singleton design
*/
class Coordinator{

public:
       static Coordinator * pCInstance; //The singleton instance
public:
       static Coordinator * getInstance();
       void run();

       Coordinator(const Coordinator & assignThis) =delete;
       Coordinator & operator =(const Coordinator &assignThis)=delete;
       ~Coordinator();
private:
    Coordinator();
    void ShowMainWindow();
    void ShowGetAPIKey();

private:
    MainWindow * pMainWindow;
    GetUserAPIKey * pGetUserAPIKey;
};
#endif // COORDINATOR_H
