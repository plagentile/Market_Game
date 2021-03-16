#include "requestencapsulator.h"

RequestEncapsulator::RequestEncapsulator(QObject *parent)
    :QObject(parent), networkHandler(nullptr)
{
    connect(&networkHandler, &NetworkHandler::mySignal, this, &RequestEncapsulator::on_NetworkReplyReady);
}

void RequestEncapsulator::on_PriceHistoryChartRequested(const QString apiKey, const QString symbol, const QString priceHistoryPeriodType, const int32_t amountOfPeriods)
{
    QString requestURL("https://api.tdameritrade.com/v1/marketdata/" + symbol + "/pricehistory?apikey=" + apiKey);
    requestURL += this->getPeriodType(priceHistoryPeriodType, amountOfPeriods);

    this->networkHandler.get(requestURL);
}


void RequestEncapsulator::on_NetworkReplyReady(NetworkHandler::Status status){
    if(status == NetworkHandler::Status::PassedFinshed){
        printf("\nReply is good");
        //return this->chartBuilder.buildLineChart(this->networkHandler.getJSONReponse());
    }
}

const QString RequestEncapsulator::getPeriodType(const QString pType, const int32_t amountOfPeriods) const noexcept
{
    if(pType == "day"){
        //For daily periods, frequency is going to be in the span of 30minutes snapshots
        return  ("&periodType=day&period=" + QString::number(amountOfPeriods) + "&frequencyType=minute&frequency=30");
    }
    else if(pType == "month"){
        //Monthly requests have a daily frequency snapshot, with a frequncy of once per day
        return "&periodType=month";
    }
    else if(pType == "year"){

        return "&periodType=year";
    }
    else if(pType == "ytd"){
        return "&periodType=ytd";
    }

    return "";
}


/*void RequestEncapsulator::getPriceHistory(const QString apiKey, const QString symbol, const QString pType, int32_t pAmount, const QString fType, int32_t fAmount)
{

    priceHistoryRequest += getPeriodType(pType);
    priceHistoryRequest += "&" + QString::number(pAmount);
    priceHistoryRequest += getFrequencyType(fType);
    priceHistoryRequest += "&" + QString::number(fAmount);

    printf("\nRequest: %ls\n", qUtf16Printable(priceHistoryRequest));
}*/



/*QString RequestEncapsulator::getFrequencyType(const QString fType) noexcept
{
    if(fType == "minute") return "&frequencyType=minute";
    else if(fType == "daily") return "&frequencyType=daily";
    else if(fType == "weekly") return "&frequencyType=weekly";
    else if(fType == "monthly") return "&frequencyType=monthly";
    return "";
}*/





