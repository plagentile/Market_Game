#ifndef COORDINATOR_H
#define COORDINATOR_H

#include "mainwindow.h"
#include "initialaccountsetup.h"
#include "signinoptionsdialog.h"
#include "termsofservice.h"
#include "about.h"
#include "symbolternarysearchtree.h"

/*This class is responsible for controlling the (initial) flow of the program*/

class Coordinator: public QObject
{
    Q_OBJECT
public:
    explicit Coordinator(QObject *parent = nullptr);
    Coordinator() = delete;
    Coordinator(const Coordinator & assignThis) =delete;
    Coordinator & operator =(const Coordinator &assignThis)=delete;
    ~Coordinator() =default;

    void run();

public: signals:
    void loginAfterInitialAccount(const QString &key, const int32_t initBalance);

private slots:
    void on_showAboutPageRequested();
    void on_showTermsOfServiceRequested();
    void on_makeNewSimulationRequested();
    void on_loadPreviousSimulationRequested();
    void on_loginRequested(const QString& key, const int32_t initBalance);
    void on_exitProgramRequested();

private:
    MainWindow mainWindow;
    InitialAccountSetup initialAccountSetup;
    SignInOptionsDialog signInOptionsDialog;
    TermsOfService termsOfService;
    About about;
    SymbolTernarySearchTree symbolTernarySearchTree;
};
#endif // COORDINATOR_H
