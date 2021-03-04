#ifndef REQUESTENCAPSULATOR_H
#define REQUESTENCAPSULATOR_H

#include "networkhandler.h"
/*
 * The class is used for encapuslating user input into a usable string that
 * will be handed off to NetworkHandler to GET a symbol series from NetworkHandler
 */
class RequestEncapsulator
{
public:
    RequestEncapsulator() = default;
    RequestEncapsulator(const RequestEncapsulator & assign) =delete;
    RequestEncapsulator & operator =(const RequestEncapsulator & assign) = delete;
    ~RequestEncapsulator() = default;

    void getPriceHistory(const QString apiKey, const QString symbol, const QString pType, int32_t pAmount, const QString fType, int32_t fAmount);

private:
    QString getPeriodType(const QString pType) noexcept;
    QString getFrequencyType(const QString fType) noexcept;

private:
    const QString postSymbol = "/pricehistory?apikey=";
    const QString host = "https://api.tdameritrade.com/v1/marketdata/";

    NetworkHandler networkHandler;
};

#endif // REQUESTENCAPSULATOR_H
