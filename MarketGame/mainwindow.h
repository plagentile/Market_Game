#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include <QRegExpValidator>
#include <QRegExp>
#include "account.h"
#include "initialaccountsetup.h"
#include "searchsymbol.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, const InitialAccountSetup* initAccountSetup =nullptr, const SymbolTernarySearchTree *pSymbolTST = nullptr );
    MainWindow() = delete;
    MainWindow(const MainWindow & window) = delete;
    MainWindow & operator = (const MainWindow & window) = delete;
    ~MainWindow();
private:
    void refresh(void);

private slots:
    void on_exitButton_clicked();
    void on_searchButton_clicked();
    void on_accountButton_clicked();

private:
    Ui::MainWindow *ui;
    Account * pAccount;
    SearchSymbol * pSearchSymbol;
};
#endif // MAINWINDOW_H
