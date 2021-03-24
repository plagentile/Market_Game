#include "chartbuilder.h"

ChartBuilder::ChartBuilder(QObject *parent)
    :QObject(parent)
{
    this->font.setPointSize(12);
    this->font.setFamily("Georgia");
}

void ChartBuilder::on_requestLineChart(const QJsonObject* jResponsePointer){
    QChart * chart = new QChart();

    if(jResponsePointer && !jResponsePointer->empty())
    {
        QLineSeries *closeSeries = new QLineSeries();
        closeSeries->setColor(QColor(Qt::blue));
        closeSeries->setName(jResponsePointer->value("symbol").toString() + " Close");
        chart->setTitle(jResponsePointer->value("symbol").toString() + " Price History (Delayed)");
        chart->setTitleFont(this->font);

        const QJsonArray &arr =  jResponsePointer->value("candles").toArray();
        for(const QJsonValue & v : arr){
            closeSeries->append(v.toObject().value("datetime").toDouble(), v.toObject().value("close").toDouble());
        }

        chart->addSeries(closeSeries);

        QDateTimeAxis *axisX = new QDateTimeAxis;
        axisX->setTickCount(20);
        axisX->setFormat("dd MMM");
        axisX->setTitleText("Date");
        axisX->setTitleFont(this->font);
        chart->addAxis(axisX, Qt::AlignBottom);
        closeSeries->attachAxis(axisX);

        QValueAxis *axisY = new QValueAxis;
        axisY->setLabelFormat("%.2f");
        axisY->setTitleText("Price");
        axisY->setTitleFont(this->font);
        chart->addAxis(axisY, Qt::AlignLeft);
        closeSeries->attachAxis(axisY);

        chart->legend()->setFont(this->font);
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);
    }
    emit this->chartReady(chart);
}

void ChartBuilder::on_requestCandlestickChart(const QJsonObject *jResponsePointer)
{
    QChart * chart = new QChart();
    if(jResponsePointer && !jResponsePointer->empty())
    {
        QCandlestickSeries *series = new QCandlestickSeries();
        series->setIncreasingColor(QColor(Qt::green));
        series->setDecreasingColor(QColor(Qt::red));
        series->setName(jResponsePointer->value("symbol").toString() + " Close");
        chart->setTitle(jResponsePointer->value("symbol").toString() + " Price History");


        const QJsonArray &arr =  jResponsePointer->value("candles").toArray();
        for(const QJsonValue & v : arr)
        {
            QCandlestickSet *candlestickSet = new QCandlestickSet(v.toObject().value("datetime").toDouble());
            candlestickSet->setOpen(v.toObject().value("open").toDouble());
            candlestickSet->setHigh(v.toObject().value("high").toDouble());
            candlestickSet->setLow(v.toObject().value("low").toDouble());
            candlestickSet->setClose(v.toObject().value("close").toDouble());
            series->append(candlestickSet);
        }

        chart->addSeries(series);

        QDateTimeAxis *axisX = new QDateTimeAxis;
        axisX->setTickCount(20);
        axisX->setFormat("dd MMM");
        axisX->setTitleText("Date");
        axisX->setTitleFont(this->font);
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        QValueAxis *axisY = new QValueAxis;
        axisY->setLabelFormat("%.2f");
        axisY->setTitleText("Price");
        axisY->setTitleFont(this->font);
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);

        chart->legend()->setFont(this->font);
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);
    }
    emit this->chartReady(chart);
}


