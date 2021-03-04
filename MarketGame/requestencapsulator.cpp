#include "requestencapsulator.h"


void RequestEncapsulator::getPriceHistory(const QString apiKey, const QString symbol, const QString pType, int32_t pAmount, const QString fType, int32_t fAmount)
{
    QString priceHistoryRequest = this->host;
    priceHistoryRequest += symbol;
    priceHistoryRequest += postSymbol;
    priceHistoryRequest += apiKey;
    priceHistoryRequest += getPeriodType(pType);
    priceHistoryRequest += "&" + QString::number(pAmount);
    priceHistoryRequest += getFrequencyType(fType);
    priceHistoryRequest += "&" + QString::number(fAmount);

    printf("\nRequest: %ls\n", qUtf16Printable(priceHistoryRequest));
    this->networkHandler.get(priceHistoryRequest);
}

QString RequestEncapsulator::getPeriodType(const QString pType) noexcept{

    if(pType == "daily") return "&periodType=day";
    else if(pType == "month") return "&periodType=month";
    else if(pType == "year") return "&periodType=year";
    else if(pType == "ytd") return "&periodType=ytd";
    return "";
}

QString RequestEncapsulator::getFrequencyType(const QString fType) noexcept
{
    if(fType == "minute") return "&frequencyType=minute";
    else if(fType == "daily") return "&frequencyType=daily";
    else if(fType == "weekly") return "&frequencyType=weekly";
    else if(fType == "monthly") return "&frequencyType=monthly";
    return "";
}





