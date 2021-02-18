#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include <QRegExpValidator>
#include <QRegExp>
#include <QStandardItemModel>
#include "account.h"
#include "initialaccountsetup.h"
#include "symbolternarysearchtree.h"
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
    void on_symbolSearchLineEdit_textChanged(const QString &arg1);

private:
    QStandardItemModel model;
    Ui::MainWindow *ui;
    Account * pAccount;
    const SymbolTernarySearchTree * pSymbolTST;
};
#endif // MAINWINDOW_H
