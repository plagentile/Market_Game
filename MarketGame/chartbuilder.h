#ifndef CHARTBUILDER_H
#define CHARTBUILDER_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QtCharts>
class ChartBuilder
{
public:
    ChartBuilder();


public:
    void buildBoxWhiskersChart(const QJsonArray & arr);

    QChart* buildLineChart(const QJsonArray & arr);
};

#endif // CHARTBUILDER_H
