#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include <QRegExpValidator>
#include <QRegExp>
#include <QStandardItemModel>
#include "account.h"
#include "symbolternarysearchtree.h"
#include "requestencapsulator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, const SymbolTernarySearchTree *pTST = nullptr );
    MainWindow() = delete;
    MainWindow(const MainWindow & window) = delete;
    MainWindow & operator = (const MainWindow & window) = delete;
    ~MainWindow();

    enum class Status
    {
        Normal,
        NewSimulation,
        LoadSimulation,
        ExitNormal,
        ExitError
    };

    Status getStatus() const;

public: signals:
    void priceHistoryChartReqested(const QString apiKey, const QString symbol, const QString priceHistoryPeriodType, const int32_t amountOfPeriods);
    void searchSymbolPageRequested();

private slots:    
    void on_symbolSearchLineEdit_textChanged(const QString &arg1);
    void on_symbolListResults_clicked(const QModelIndex &index);

    void on_requestReady(RequestEncapsulator::Status status, QChart * chart);;
    void on_goToTradePageButton_clicked();

    void on_goToSymbolSearchPageRequested();
    void on_goToViewSymbolOverviewPage();

private:
    RequestEncapsulator requestEncapsulator;
    Account account;
    QStandardItemModel model;
    Ui::MainWindow *ui;
    const SymbolTernarySearchTree * pSymbolTST;
    QVector<const SymbolTernarySearchTree::Node *> vSearchResults;
    Status status;
};
#endif // MAINWINDOW_H
