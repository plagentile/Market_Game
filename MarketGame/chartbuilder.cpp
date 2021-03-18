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

        const QJsonArray arr =  jResponsePointer->value("candles").toArray();
        for(const QJsonValue & v : arr){
            const double epochVal = v.toObject().value("datetime").toDouble();
            closeSeries->append(epochVal, v.toObject().value("close").toDouble());
            highSeries->append(epochVal, v.toObject().value("high").toDouble());
            lowSeries->append(epochVal,v.toObject().value("low").toDouble());
        }


        chart->addSeries(closeSeries);
        chart->addSeries(highSeries);
        chart->addSeries(lowSeries);

        QDateTimeAxis *axisX = new QDateTimeAxis;
        axisX->setTickCount(10);
        axisX->setFormat("MMM yyyy");
        axisX->setTitleText("Date");
        chart->addAxis(axisX, Qt::AlignBottom);


        QValueAxis *axisY = new QValueAxis;
        axisY->setLabelFormat("%d");
        axisY->setTitleText("Price");
        chart->addAxis(axisY, Qt::AlignLeft);

        closeSeries->attachAxis(axisX);
        highSeries->attachAxis(axisX);
        lowSeries->attachAxis(axisX);


        closeSeries->attachAxis(axisY);
        highSeries->attachAxis(axisY);
        lowSeries->attachAxis(axisY);

        chart->setTitle(symbolName + " Price History");
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);
    }
    emit this->lineChartReady(chart);
}


