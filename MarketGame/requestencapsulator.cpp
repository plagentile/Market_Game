#include "requestencapsulator.h"

RequestEncapsulator::RequestEncapsulator(QObject *parent)
    :QObject(parent), requestType(RequestType::Unknown),networkHandler(nullptr), chartBuilder(nullptr)
{
    connect(this, &RequestEncapsulator::sendNetworkRequest, &networkHandler, &NetworkHandler::get);
    connect(&networkHandler, &NetworkHandler::done, this, &RequestEncapsulator::on_networkReplyFinished);
    connect(this, &RequestEncapsulator::requestLineChart, &chartBuilder, &ChartBuilder::on_requestLineChart);
    connect(&chartBuilder, &ChartBuilder::lineChartReady, this, &RequestEncapsulator::on_lineChartReady);
}

void RequestEncapsulator::on_priceHistoryChartRequested(const QString& apiKey, const QString& symbol, const QString& priceHistoryPeriodType, const int32_t amountOfPeriods){
    this->requestType = RequestType::PriceHistoryLine;
    QString requestURL("https://api.tdameritrade.com/v1/marketdata/" + symbol + "/pricehistory?apikey=" + apiKey);
    requestURL += this->getPeriodType(priceHistoryPeriodType, amountOfPeriods);
    emit this->sendNetworkRequest(requestURL);
}

void RequestEncapsulator::on_networkReplyFinished(NetworkHandler::Status status, const QJsonObject * jResponsePointer){
    if(status == NetworkHandler::Status::PassedFinshed)
    {
        switch(requestType)
        {
            case(RequestType::PriceHistoryLine):
            {
                emit this->requestLineChart(jResponsePointer);
                break;
            }
            case(RequestType::PriceHistoryCandleStick):
            {
                break;
            }
            default:
                break;
        }
    }
}

void RequestEncapsulator::on_lineChartReady(QChart *chart){
    if(chart){
        emit this->requestReady(Status::ChartOkay, chart);
    }
    else{
        emit this->requestReady(Status::Error, nullptr);
    }
}

const QString RequestEncapsulator::getPeriodType(const QString pType, const int32_t amountOfPeriods) const noexcept{
    if(pType == "day"){
        return  ("&periodType=day&period=" + QString::number(amountOfPeriods) + "&frequencyType=minute&frequency=30");
    }
    else if(pType == "month"){
        return "&periodType=month&period=" + QString::number(amountOfPeriods) + "&frequencyType=daily&frequency=1";
    }
    else if(pType == "year"){
       return "&periodType=year&period="+ QString::number(amountOfPeriods) + "&frequencyType=weekly&frequency=1";
    }
    else if(pType == "ytd"){
        return "&periodType=ytd&period=1&frequencyType=daily&frequency=1";
    }
    return "";
}


