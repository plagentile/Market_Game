#include "chartbuilder.h"

ChartBuilder::ChartBuilder(QObject *parent)
    :QObject(parent)
{
}

void ChartBuilder::on_requestLineChart(const QJsonObject* jReponsePointer){
    QChart * chart = new QChart();
    if(jReponsePointer)
    {
        QLineSeries *series = new QLineSeries();
        //append series here....

        //qDebug() << tpast;
        double x = 0.0;
        QJsonArray arr =  jReponsePointer->value("candles").toArray();
        for(const QJsonValue & v : arr){
            QDateTime tpast = QDateTime::fromMSecsSinceEpoch(v.toObject().value("datetime").toDouble());
            series->append(tpast, v.toObject().value("close").toDouble());
            x++;
        }
        chart->legend()->hide();
        chart->addSeries(series);
        chart->createDefaultAxes();
        chart->setTitle("Simple line chart example");
    }
    emit this->lineChartReady(chart);
}
