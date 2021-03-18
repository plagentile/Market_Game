#include "chartbuilder.h"

ChartBuilder::ChartBuilder(QObject *parent)
    :QObject(parent)
{
}

void ChartBuilder::on_requestLineChart(const QJsonObject* jResponsePointer){
    QChart * chart = new QChart();
    if(jResponsePointer && !jResponsePointer->empty())
    {
        const QString symbolName = jResponsePointer->value("symbol").toString();

        QLineSeries *closeSeries = new QLineSeries();
        closeSeries->setName(symbolName + " Close");
        closeSeries->setColor(QColor(Qt::blue));

        QLineSeries *highSeries = new QLineSeries();
        highSeries->setName(symbolName + " High");
        highSeries->setColor(QColor(Qt::green));

        QLineSeries *lowSeries = new QLineSeries();
        lowSeries->setName(symbolName + " Low");
        lowSeries->setColor(QColor(Qt::red));

        double x = 0.0;
        const QJsonArray arr =  jResponsePointer->value("candles").toArray();
        for(const QJsonValue & v : arr){
            //QDateTime tpast = QDateTime::fromMSecsSinceEpoch(v.toObject().value("datetime").toDouble());
            closeSeries->append(x, v.toObject().value("close").toDouble());
            highSeries->append(x, v.toObject().value("high").toDouble());
            lowSeries->append(x,v.toObject().value("low").toDouble());
            x++;
        }
        chart->addSeries(closeSeries);
        chart->addSeries(highSeries);
        chart->addSeries(lowSeries);

        chart->createDefaultAxes();
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);
        chart->setTitle(jResponsePointer->value("symbol").toString());
    }
    emit this->lineChartReady(chart);
}


