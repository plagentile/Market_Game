#include "chartbuilder.h"

ChartBuilder::ChartBuilder(QObject *parent)
    :QObject(parent)
{}

void ChartBuilder::on_requestLineChart(const QJsonObject* jResponsePointer){
    QChart * chart = new QChart();
    if(jResponsePointer && !jResponsePointer->empty())
    {
        const QString symbolName = jResponsePointer->value("symbol").toString();

        QLineSeries *closeSeries = new QLineSeries();
        closeSeries->setName(symbolName + " Close");
        closeSeries->setColor(QColor(Qt::blue));

        const QJsonArray &arr =  jResponsePointer->value("candles").toArray();
        for(const QJsonValue & v : arr){
            const double epochVal = v.toObject().value("datetime").toDouble();
            closeSeries->append(epochVal, v.toObject().value("close").toDouble());
        }

        chart->addSeries(closeSeries);

        QDateTimeAxis *axisX = new QDateTimeAxis;
        axisX->setTickCount(20);
        axisX->setFormat("dd-MMM");
        axisX->setTitleText("Date");
        chart->addAxis(axisX, Qt::AlignBottom);
        closeSeries->attachAxis(axisX);

        QValueAxis *axisY = new QValueAxis;
        axisY->setLabelFormat("%.2f");
        axisY->setTitleText("Price");
        chart->addAxis(axisY, Qt::AlignLeft);
        closeSeries->attachAxis(axisY);

        chart->setTitle(symbolName + " Price History");
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);
    }
    emit this->lineChartReady(chart);
}


