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


    enum class Status{
        ChartOkay,
        Error
    };

public slots:
    void on_priceHistoryChartRequested(const QString apiKey, const QString symbol, const QString priceHistoryPeriodType, const int32_t amountOfPeriods);
    void on_networkReplyFinished(NetworkHandler::Status status, const QJsonObject * jResponsePointer);
    void on_lineChartReady(QChart * chart);

public: signals:
    void requestLineChart(const QJsonObject* jResponsePointer);
    void requestReady(Status status, QChart * chart);
    void sendNetworkRequest(QString url);

private:
    const QString getPeriodType(const QString pType, const int32_t amountOfPeriods) const noexcept;

private:

    enum class RequestType{
        Unknown,
        PriceHistoryLine,
        PriceHistoryCandleStick
    };
    RequestType requestType;

    NetworkHandler networkHandler;
    ChartBuilder chartBuilder;
};

#endif // REQUESTENCAPSULATOR_H
