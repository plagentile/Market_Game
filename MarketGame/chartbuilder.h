#ifndef CHARTBUILDER_H
#define CHARTBUILDER_H
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QtCharts>

class ChartBuilder : public QObject
{
     Q_OBJECT
public:
    explicit ChartBuilder(QObject *parent = nullptr);
    ChartBuilder() = delete;
    ChartBuilder(const ChartBuilder & assign) =delete;
    ChartBuilder & operator = (const ChartBuilder & assign) =delete;
    ~ChartBuilder() = default;

public slots:
    void on_requestLineChart(const QJsonObject jReponseObject) const ;
    void on_requestCandlestickChart(const QJsonObject jReponseObject) const ;

public: signals:
    void chartReady(QChart * chart) const;

private:
    QFont font;
};

#endif // CHARTBUILDER_H
