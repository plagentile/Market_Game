#include "updatehandler.h"

UpdateHandler::UpdateHandler(QObject *parent): QObject(parent)
{
    QObject::connect(&this->timer, &QTimer::timeout, this, &UpdateHandler::timeout);
    timer.setInterval(2000);
}

void UpdateHandler::start()
{
    this->timer.start();
    this->loop.exec();

    delete this; //This same instance will never be again after exiting exec();
}

void UpdateHandler::stop()
{
    this->timer.stop();
    this->loop.quit();
}

void UpdateHandler::timeout()
{
    qInfo() << "Timed out...";
}
