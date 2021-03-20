#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent,  const SymbolTernarySearchTree *pTST)
    : QMainWindow(parent),
      requestEncapsulator(0),
      account(0, 0, ""),
      ui(new Ui::MainWindow),
      pSymbolTST(pTST),
      status(Status::Normal)
{
    this->ui->setupUi(this);
    this->ui->symbolSearchLineEdit->setValidator(new QRegExpValidator(QRegExp("[A-Z]{0,4}"), this));
    vSearchResults.reserve(this->pSymbolTST->getSYMBOL_SEARCH_VECTOR_RESERVE_SIZE());

    QObject::connect(this->ui->goToSymbolSearchPageButton, &QPushButton::clicked, this, &MainWindow::on_goToSymbolSearchPageRequested);
    QObject::connect(this->ui->symbolSearchLineEdit, &QLineEdit::returnPressed,this, &MainWindow::on_goToViewSymbolOverviewPage);
    QObject::connect(this->ui->searchSymbolButton, &QPushButton::clicked, this, &MainWindow::on_goToViewSymbolOverviewPage);

    QObject::connect(this,&MainWindow::searchSymbolPageRequested, this, &MainWindow::on_goToSymbolSearchPageRequested);
    QObject::connect(this, &MainWindow::priceHistoryChartReqested, &requestEncapsulator, &RequestEncapsulator::on_priceHistoryChartRequested);
    QObject::connect(&requestEncapsulator, &RequestEncapsulator::requestReady, this, &MainWindow::on_requestReady);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_goToViewSymbolOverviewPage(){
    //Check if the current text exists in this->vectSearchResults;
    const QString currTextEdit = this->ui->symbolSearchLineEdit->text();
    for(int32_t x = 0, length = this->vSearchResults.length(); x < length; ++x){
        if(this->ui->symbolSearchLineEdit->text() == vSearchResults[x]->symbol){
            //Valid symbol, set and show the next page, default view is one year of data with price points set at once per week
            emit this->priceHistoryChartReqested(this->account.getAPIKey(), currTextEdit, "day", 2);
            break;
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
        const QString res = item->data(0).toString();
        QString temp = "";
        for(int32_t x = 0, length = res.length(); x < length; ++x){ //find the symbol in the string
            if(res[x] == ',') break;
            temp += res[x];
        }
        this->ui->symbolSearchLineEdit->setText(temp);
        this->ui->symbolListResults->hide();
        this->ui->searchSymbolButton->show();
    }
}

void MainWindow::on_requestReady(RequestEncapsulator::Status status, QChart * chart){
    if(status == RequestEncapsulator::Status::ChartOkay && chart)
    {
        QChart * pTemp = this->ui->graphicsView->chart();
        chart->layout()->setContentsMargins(0, 0, 0, 0);
        this->ui->graphicsView->setChart(chart);
        this->ui->graphicsView->setRenderHint(QPainter::Antialiasing);
        pTemp->deleteLater();
    }
    this->ui->searchAndViewSymbolStackedWidget->setCurrentIndex(1);
}

MainWindow::Status MainWindow::getStatus() const{
    return status;
}


void MainWindow::on_goToTradePageButton_clicked(){

}

void MainWindow::on_goToSymbolSearchPageRequested(){
    this->ui->searchAndViewSymbolStackedWidget->setCurrentIndex(0);
    this->ui->searchSymbolButton->hide();
    this->ui->symbolListResults->hide();
    this->ui->searchSymbolButton->hide();
}
