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

public slots:
    void on_requestLineChart(const QJsonObject* jReponsePointer);

public: signals:
    void lineChartReady(QChart * chart);

};

#endif // CHARTBUILDER_H
