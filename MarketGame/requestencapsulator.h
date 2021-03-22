#ifndef REQUESTENCAPSULATOR_H
#define REQUESTENCAPSULATOR_H

#include "chartbuilder.h"
#include "networkhandler.h"
/*
 * The class is used for encapuslating user input into a usable string that
 * will be handed off to NetworkHandler to GET a symbol series from NetworkHandler
 */
class RequestEncapsulator: public QObject
{
    Q_OBJECT
public:

    explicit RequestEncapsulator(QObject *parent = nullptr);
    RequestEncapsulator() =delete;
    RequestEncapsulator(const RequestEncapsulator & assign) =delete;
    RequestEncapsulator & operator =(const RequestEncapsulator & assign) = delete;
    ~RequestEncapsulator() = default;

public slots:
    void on_priceHistoryLineChartRequested(const QString& apiKey, const QString& symbol, const QString& priceHistoryPeriodType, const int32_t amountOfPeriods);
    void on_priceHistoryCandlestickChartRequested(const QString& apiKey, const QString& symbol, const QString& priceHistoryPeriodType, const int32_t amountOfPeriods);

    void on_networkReplyFinished(const QJsonObject * jResponsePointer);
    void on_chartReady(QChart * chart);

public: signals:
    void requestCandlestickChart(const QJsonObject* jResponsePointer);
    void requestLineChart(const QJsonObject* jResponsePointer);
    void requestReady(QChart * chart);
    void sendNetworkRequest(QString url);

private:
    const QString getPeriodType(const QString& pType, const int32_t amountOfPeriods) const noexcept;

private:

    enum class RequestType{
        Unknown,
        PriceHistoryLine,
        PriceHistoryCandleStick
    };
    NetworkHandler networkHandler;
    const ChartBuilder chartBuilder;
    RequestType requestType;

};

#endif // REQUESTENCAPSULATOR_H
