#ifndef CHARTBUILDER_H
#define CHARTBUILDER_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
class ChartBuilder
{
public:
    ChartBuilder();


public:
    void buildBoxWhiskersChart(const QJsonArray & arr);
};

#endif // CHARTBUILDER_H
