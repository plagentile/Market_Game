#ifndef COORDINATOR_H
#define COORDINATOR_H

#include "mainwindow.h"
#include "initialaccountsetup.h"
#include "signinoptionsdialog.h"
#include "termsofservice.h"
#include "about.h"
#include "symbolternarysearchtree.h"
#include <QApplication>
#include <QtConcurrent/QtConcurrentRun>

/*This class is responsible for controlling the (initial) flow of the program*/

class Coordinator: public QObject
{
public:
    Coordinator(QObject *parent = nullptr);
    Coordinator() = delete;
    Coordinator(const Coordinator & assignThis) =delete;
    Coordinator & operator =(const Coordinator &assignThis)=delete;
    ~Coordinator() =default;
    int32_t run(QApplication *coreApp);

private slots:
    void on_showAboutPageRequested();
    void on_showTermsOfServiceRequested();
    void on_makeNewSimulationRequested();
    void on_loadPreviousSimulationRequested();

private:
    MainWindow mainWindow;
    InitialAccountSetup initialAccountSetup;
    SignInOptionsDialog signInOptionsDialog;
    TermsOfService termsOfService;
    About about;
    SymbolTernarySearchTree symbolTernarySearchTree;
};
#endif // COORDINATOR_H
