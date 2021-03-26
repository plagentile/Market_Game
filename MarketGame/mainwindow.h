#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include <QRegExpValidator>
#include <QRegExp>
#include <QStandardItemModel>
#include <QCloseEvent>
#include <QDebug>
#include "account.h"
#include "symbolternarysearchtree.h"
#include "requestencapsulator.h"
#include "tradehandler.h"

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

public: signals:
    void priceHistoryLineChartReqested(const QString& apiKey, const QString& symbol, const QString& priceHistoryPeriodType, const int32_t amountOfPeriods);
    void priceHistoryCandlestickChartRequested(const QString& apiKey, const QString& symbol, const QString& priceHistoryPeriodType, const int32_t amountOfPeriods);
    void requestLiveQuote(const QString& apiKey, const QString& symbol);
    void showSearchSymbolPageRequested();
    void showAboutPageRequested();
    void showTermsOfServicePageRequested();
    void exitProgram();


public slots:
    void on_setupInitialAccount(const QString & key, const int32_t balance);
    void on_actionAbout_triggered();
    void on_actionTerms_Of_Service_triggered();
    void on_actionQuit_triggered();
    void on_liveQuoteRequestReady(QJsonObject jObject);

private slots:

    void timeout();
    void start();
    void stop();

    void on_actionCandlestick_triggered();
    void on_actionLinechart_triggered();
    void on_actionAccount_Overview_triggered();

    void on_symbolSearchLineEdit_textChanged(const QString &arg1);
    void on_symbolListResults_clicked(const QModelIndex &index);
    void on_requestReady(QChart * chart);;
    void on_goToSymbolSearchPageRequested();
    void on_goToViewSymbolOverviewPage();
    void on_buyButton_clicked();


protected:
    void closeEvent(QCloseEvent *event) override;


private:
    const RequestEncapsulator requestEncapsulator;
    Account account;
    TradeHandler tradeHandler;
    QTimer timer;
    QStandardItemModel model;
    Ui::MainWindow *ui;
    const SymbolTernarySearchTree * pSymbolTST;
    QVector<const SymbolTernarySearchTree::Node *> vSearchResults;

};
#endif // MAINWINDOW_H
