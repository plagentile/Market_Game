#ifndef REQUESTENCAPSULATOR_H
#define REQUESTENCAPSULATOR_H

#include "chartbuilder.h"
#include "networkhandler.h"
/*
 * The class is used for encapuslating user input into a usable string that
 * will be handed off to NetworkHandler to GET a symbol series from NetworkHandler
 */
class RequestEncapsulator
{
public:
    RequestEncapsulator();
    RequestEncapsulator(const RequestEncapsulator & assign) =delete;
    RequestEncapsulator & operator =(const RequestEncapsulator & assign) = delete;
    ~RequestEncapsulator() = default;

    QChart* getPriceHistoryChart(const QString apiKey, const QString symbol, const QString priceHistoryPeriodType, const int32_t amountOfPeriods);

private:
    const QString getPeriodType(const QString pType, const int32_t amountOfPeriods) const noexcept;

private:
    NetworkHandler networkHandler;
    ChartBuilder chartBuilder;
};

#endif // REQUESTENCAPSULATOR_H
