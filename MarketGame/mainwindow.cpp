#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, const int32_t initBalance, const QString initAPIKey, const SymbolTernarySearchTree *pTST)
    : QMainWindow(parent),
      requestEncapsulator(0),
      account(0, initBalance, initAPIKey),
      ui(new Ui::MainWindow),
      pSymbolTST(pTST),
      status(Status::Normal)
{
    this->ui->setupUi(this);
    this->ui->symbolSearchLineEdit->setValidator(new QRegExpValidator(QRegExp("[A-Z]{0,4}"), 0));
    this->ui->symbolListResults->hide();                                                                              //Hide list of recommendations initially
    this->ui->searchSymbolButton->hide();
    vSearchResults.reserve(this->pSymbolTST->getSYMBOL_SEARCH_VECTOR_RESERVE_SIZE());
    connect(this, &MainWindow::priceHistoryChartReqested, &requestEncapsulator, &RequestEncapsulator::on_PriceHistoryChartRequested);
    connect(&requestEncapsulator, &RequestEncapsulator::requestReady, this, &MainWindow::on_requestReady);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::refreshSymbolInformation(){
    this->ui->dynamicAccountBalanceLabel->setText(QString::number(this->account.getAccountBalance(), 'f', 2));
    this->ui->dynamicAvailableFundsLabel->setText(QString::number(this->account.getAvailableFunds(), 'f', 2));
}

void MainWindow::showViewSymbolPage(){
    //Check if the current text exists in this->vectSearchResults;
    const QString currTextEdit = this->ui->symbolSearchLineEdit->text();
    for(int32_t x = 0, length = this->vSearchResults.length(); x < length; ++x){
        if(currTextEdit == vSearchResults[x]->symbol){
            //Valid symbol, set and show the next page, default view is one year of data with price points set at once per week
            emit this->priceHistoryChartReqested(this->account.getAPIKey(), currTextEdit, "day", 2);
        }
    }
}

void MainWindow::on_symbolSearchLineEdit_textChanged(const QString &arg1){
    if(arg1.length() <= 0) return;

    this->ui->searchSymbolButton->hide();
    this->ui->symbolListResults->show();

    this->vSearchResults = this->pSymbolTST->searchTST(arg1);                                                         //A move here would prevent RVO
    if(this->vSearchResults.length() == 0) return;                                                                    //Keep previous recommendations if going down a non existant symbol path

    QStandardItem *pRoot = model.invisibleRootItem();
    pRoot->removeRows(0, model.rowCount());

    for(int32_t r =0, length = this->vSearchResults.length(); r < length; ++r){
        pRoot->appendRow(new QStandardItem(vSearchResults[r]->symbol +", " +vSearchResults[r]->name + ", " +vSearchResults[r]->industry));
    }
    ui->symbolListResults->setModel(&model);
}

void MainWindow::on_symbolListResults_clicked(const QModelIndex &index){                                              //User clicked on a recommendation in the symbol list results fill the line edit, hide other recommendations
    QStandardItem * item = this->model.itemFromIndex(index);
    if(item){
        //find the symbol in the string
        QString res = item->data(0).toString();
        QString temp = "";
        for(int32_t x = 0, length = res.length(); x < length; ++x){
            if(res[x] == ',') break;
            temp += res[x];
        }
        this->ui->symbolSearchLineEdit->setText(temp);
        this->ui->symbolListResults->hide();
        this->ui->searchSymbolButton->show();
    }
}

void MainWindow::on_symbolSearchLineEdit_returnPressed(){
    this->showViewSymbolPage();
}

void MainWindow::on_searchSymbolButton_clicked(){
    this->showViewSymbolPage();
}

void MainWindow::on_requestReady(RequestEncapsulator::Status status, QChart * chart){
    if(status == RequestEncapsulator::Status::ChartOkay && chart){
        //set and show chart
        this->ui->graphicsView->setChart(chart);
        this->ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    }
    this->refreshSymbolInformation();
    this->ui->searchAndViewSymbolStackedWidget->setCurrentIndex(1);
}

MainWindow::Status MainWindow::getStatus() const{
    return status;
}
