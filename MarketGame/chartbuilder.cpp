#include "chartbuilder.h"

ChartBuilder::ChartBuilder()
{

}

QChart* ChartBuilder::buildLineChart(const QJsonArray &arr){
    QChart * chart = new QChart();
    QLineSeries *series = new QLineSeries();

    //append series here....
    //QDateTime tpast = QDateTime::fromMSecsSinceEpoch(v.toObject().value("datetime").toDouble());
    //qDebug() << tpast;
    int y = 0;
    for(const QJsonValue & v : arr){
        series->append(v.toObject().value("close").toDouble(),y);
        y++;
    }
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Simple line chart example");

    return chart;
}
