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

class Coordinator
{
public:
    explicit Coordinator(QObject *parent = nullptr);
    Coordinator() = delete;
    Coordinator(const Coordinator & assignThis) =delete;
    Coordinator & operator =(const Coordinator &assignThis)=delete;
    ~Coordinator() =default;
    int32_t run(const QApplication &coreApp);
private:
    SignInOptionsDialog::Options runSignInOptions();
    int32_t runMainWindow(const QApplication &coreApp, MainWindow::Status);

private:
    InitialAccountSetup initialAccountSetup;
    SignInOptionsDialog signInOptionsDialog;
    TermsOfService termsOfService;
    About about;
    SymbolTernarySearchTree symbolTernarySearchTree;
};
#endif // COORDINATOR_H
