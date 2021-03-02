#include "networkhandler.h"

NetworkHandler::NetworkHandler(QObject *parent) : QObject(parent)
{
    connect(&qNetworkAccessManager, &QNetworkAccessManager::authenticationRequired, this, &NetworkHandler::authenticationRequired);
    connect(&qNetworkAccessManager, &QNetworkAccessManager::encrypted, this, &NetworkHandler::encrypted);
    connect(&qNetworkAccessManager, &QNetworkAccessManager::preSharedKeyAuthenticationRequired, this, &NetworkHandler::preSharedKeyAuthenticationRequired);
    connect(&qNetworkAccessManager, &QNetworkAccessManager::proxyAuthenticationRequired, this, &NetworkHandler::proxyAuthenticationRequired);
    connect(&qNetworkAccessManager, &QNetworkAccessManager::sslErrors, this, &NetworkHandler::sslErrors);

}

void NetworkHandler::get(QString location)
{
    qInfo() << "In get...\n";
    QNetworkReply * reply = qNetworkAccessManager.get(QNetworkRequest(QUrl(location)));
    connect(reply, &QNetworkReply::readyRead, this, &NetworkHandler::readyRead);
}

void NetworkHandler::post(QString location, QByteArray data)
{
    qInfo() << "In post...\n";
    QNetworkRequest request = QNetworkRequest(QUrl(location));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "plain/text");

    QNetworkReply *reply = qNetworkAccessManager.post(request, data);
    connect(reply, &QNetworkReply::readyRead, this, &NetworkHandler::readyRead);
}

void NetworkHandler::readyRead()
{
    qInfo() << "In readyRead...\n";
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    if(reply) qInfo() << reply->readAll() << "\n";
}

void NetworkHandler::authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator)
{
    qInfo() << "authenticationRequired...\n";
    Q_UNUSED(reply);
    Q_UNUSED(authenticator);
}

void NetworkHandler::encrypted(QNetworkReply *reply)
{
    qInfo() << "encrypted...\n";
    Q_UNUSED(reply);
}

void NetworkHandler::finished(QNetworkReply *reply)
{
     qInfo() << "finished...\n";
    Q_UNUSED(reply);
}

void NetworkHandler::preSharedKeyAuthenticationRequired(QNetworkReply *reply, QSslPreSharedKeyAuthenticator *authenticator)
{
     qInfo() << "preSharedKeyAuthenticationRequired...\n";
    Q_UNUSED(reply);
    Q_UNUSED(authenticator);
}

void NetworkHandler::proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator)
{
    qInfo() << "proxyAuthenticationRequired...\n";
    Q_UNUSED(proxy);
    Q_UNUSED(authenticator);
}

void NetworkHandler::sslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
     qInfo() << "sslErrors...\n";
    Q_UNUSED(reply);
    Q_UNUSED(errors);
}
