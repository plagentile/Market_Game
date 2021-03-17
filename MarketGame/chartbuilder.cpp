#include "chartbuilder.h"

ChartBuilder::ChartBuilder(QObject *parent)
    :QObject(parent)
{
}

void ChartBuilder::on_requestLineChart(const QJsonArray &arr)
{
    QChart * chart = new QChart();
    QLineSeries *series = new QLineSeries();

    //append series here....
    //QDateTime tpast = QDateTime::fromMSecsSinceEpoch(v.toObject().value("datetime").toDouble());
    //qDebug() << tpast;
    double x = 0.0;
    for(const QJsonValue & v : arr){
        series->append(x, v.toObject().value("close").toDouble());
        x++;
    }
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Simple line chart example");

    emit this->lineChartReady(chart);
}
