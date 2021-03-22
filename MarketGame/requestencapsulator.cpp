#include "requestencapsulator.h"

RequestEncapsulator::RequestEncapsulator(QObject *parent)
    :QObject(parent),networkHandler(nullptr), chartBuilder(nullptr), requestType(RequestType::Unknown)
{
    QObject::connect(this, &RequestEncapsulator::sendNetworkRequest, &networkHandler, &NetworkHandler::get);
    QObject::connect(&networkHandler, &NetworkHandler::done, this, &RequestEncapsulator::on_networkReplyFinished);

    QObject::connect(this, &RequestEncapsulator::requestLineChart, &chartBuilder, &ChartBuilder::on_requestLineChart);
    QObject::connect(this,&RequestEncapsulator::requestCandlestickChart,&chartBuilder,&ChartBuilder::on_requestCandlestickChart);
    QObject::connect(&chartBuilder, &ChartBuilder::chartReady, this, &RequestEncapsulator::on_chartReady);
}

void RequestEncapsulator::on_priceHistoryLineChartRequested(const QString& apiKey, const QString& symbol, const QString& priceHistoryPeriodType, const int32_t amountOfPeriods){
    this->requestType = RequestType::PriceHistoryLine;
    QString requestURL("https://api.tdameritrade.com/v1/marketdata/" + symbol + "/pricehistory?apikey=" + apiKey);
    requestURL += this->getPeriodType(priceHistoryPeriodType, amountOfPeriods);
    emit this->sendNetworkRequest(requestURL);
}

void RequestEncapsulator::on_priceHistoryCandlestickChartRequested(const QString &apiKey, const QString &symbol, const QString &priceHistoryPeriodType, const int32_t amountOfPeriods){
    this->requestType = RequestType::PriceHistoryCandleStick;
    QString requestURL("https://api.tdameritrade.com/v1/marketdata/" + symbol + "/pricehistory?apikey=" + apiKey);
    requestURL += this->getPeriodType(priceHistoryPeriodType, amountOfPeriods);
    emit this->sendNetworkRequest(requestURL);
}

void RequestEncapsulator::on_networkReplyFinished(const QJsonObject * jResponsePointer){
    //A nullptr will be picked in chart builder
    switch(requestType)
    {
         case(RequestType::PriceHistoryLine):
         {
             emit this->requestLineChart(jResponsePointer);
             break;
         }
         case(RequestType::PriceHistoryCandleStick):
         {
             emit this->requestCandlestickChart(jResponsePointer);
             break;
         }
         default:
             break;
    }
}

void RequestEncapsulator::on_chartReady(QChart *chart){
       emit this->requestReady(chart);
}

const QString RequestEncapsulator::getPeriodType(const QString& pType, const int32_t amountOfPeriods) const noexcept{
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
