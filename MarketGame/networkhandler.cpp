#include "networkhandler.h"

NetworkHandler::NetworkHandler(QObject *parent) : QObject(parent), handShakeOccurred(false)
{
    connect(&qNetworkAccessManager, &QNetworkAccessManager::authenticationRequired, this, &NetworkHandler::authenticationRequired);
    connect(&qNetworkAccessManager, &QNetworkAccessManager::encrypted, this, &NetworkHandler::encrypted);
    connect(&qNetworkAccessManager, &QNetworkAccessManager::sslErrors, this, &NetworkHandler::sslErrors);
}

void NetworkHandler::get(const QString& location){
    QNetworkReply * reply = qNetworkAccessManager.get(QNetworkRequest(QUrl(location)));
    if(reply){
        connect(reply, &QNetworkReply::readyRead, this, &NetworkHandler::readyRead);
    }
}

void NetworkHandler::readyRead(){
    if(this->handShakeOccurred){
        QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());
        if(reply) {
          emit response(QJsonDocument::fromJson(reply->readAll()).object());
        }
    }
    else{
        qobject_cast<QNetworkReply*>(sender())->abort();
    }
}

void NetworkHandler::authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator){
    if(reply){
        reply->abort();
    }
    Q_UNUSED(authenticator);
}

void NetworkHandler::encrypted(QNetworkReply *reply){
    this->handShakeOccurred =true;
    Q_UNUSED(reply);
}

void NetworkHandler::sslErrors(QNetworkReply *reply, const QList<QSslError> &errors){
    if(reply){
        reply->abort();
    }

    QFile file(QDir::currentPath() + "SSL_ERRORS.txt");
    if(!file.open(QIODevice::ReadWrite | QIODevice::Truncate| QIODevice::Text)){
        return; //no hope...
    }

    for(const QSslError &err : errors){
        file.write(err.errorString().toLocal8Bit());
    }
    file.close();
}

