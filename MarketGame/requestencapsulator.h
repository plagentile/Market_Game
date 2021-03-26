#ifndef REQUESTENCAPSULATOR_H
#define REQUESTENCAPSULATOR_H

#include "chartbuilder.h"
#include "networkhandler.h"
#include <QChart>
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
    void on_liveQuoteRequested(const QString& apiKey, const QString& symbol);
    void on_networkReplyFinished(QJsonObject jReponseObject);
    void on_chartReady(QtCharts::QChart *chart);

public: signals:
    void requestForChartReady(QtCharts::QChart *chart);
    void liveQuoteReady(QJsonObject jReponseObject);

private: signals:
    void requestCandlestickChart(QJsonObject jReponseObject);
    void requestLineChart(QJsonObject jReponseObject);
    void sendNetworkRequest(QString url);

private:
    const QString getPeriodType(const QString& pType, const int32_t amountOfPeriods) const noexcept;

private:
    enum class RequestType{
        Unknown,
        PriceHistoryLine,
        PriceHistoryCandleStick,
        LiveQuote
    };

    NetworkHandler networkHandler;
    const ChartBuilder chartBuilder;
    QQueue<RequestType> ticketQueue;
};

#endif // REQUESTENCAPSULATOR_H
