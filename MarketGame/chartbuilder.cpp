#include "chartbuilder.h"

ChartBuilder::ChartBuilder(QObject *parent)
    :QObject(parent)
{
}

void ChartBuilder::on_requestLineChart(const QJsonObject* jResponsePointer){
    QChart * chart = new QChart();
    if(jResponsePointer && !jResponsePointer->empty())
    {
        QLineSeries *series = new QLineSeries();
        double x = 0.0;
        const QJsonArray arr =  jResponsePointer->value("candles").toArray();
        for(const QJsonValue & v : arr){
            //QDateTime tpast = QDateTime::fromMSecsSinceEpoch(v.toObject().value("datetime").toDouble());
            series->append(x, v.toObject().value("close").toDouble());
            x++;
        }
        chart->legend()->hide();
        chart->addSeries(series);
        chart->createDefaultAxes();
        chart->setTitle(jResponsePointer->value("symbol").toString());
    }
    emit this->lineChartReady(chart);
}


