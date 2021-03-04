#include "networkhandler.h"

NetworkHandler::NetworkHandler(QObject *parent) : QObject(parent)
{
    connect(&qNetworkAccessManager, &QNetworkAccessManager::authenticationRequired, this, &NetworkHandler::authenticationRequired);
    connect(&qNetworkAccessManager, &QNetworkAccessManager::encrypted, this, &NetworkHandler::encrypted);
    connect(&qNetworkAccessManager, &QNetworkAccessManager::sslErrors, this, &NetworkHandler::sslErrors);
    connect(&qNetworkAccessManager, &QNetworkAccessManager::finished, this, &NetworkHandler::finished);
}

void NetworkHandler::get(QString location){
    QNetworkReply * reply = qNetworkAccessManager.get(QNetworkRequest(QUrl(location)));
    connect(reply, &QNetworkReply::readyRead, this, &NetworkHandler::readyRead);
}

void NetworkHandler::readyRead(){
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if(reply) qInfo() << reply->readAll() << "\n";
}

void NetworkHandler::authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator)
{
    Q_UNUSED(reply);
    Q_UNUSED(authenticator);
}

void NetworkHandler::encrypted(QNetworkReply *reply)
{
    Q_UNUSED(reply);
}

void NetworkHandler::finished(QNetworkReply *reply)
{
    Q_UNUSED(reply);
}

void NetworkHandler::sslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
    Q_UNUSED(reply);
    Q_UNUSED(errors);
}
