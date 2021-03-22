#include "networkhandler.h"

NetworkHandler::NetworkHandler(QObject *parent) : QObject(parent), status(Status::NotStarted), handShakeOccurred(false)
{
    connect(&qNetworkAccessManager, &QNetworkAccessManager::authenticationRequired, this, &NetworkHandler::authenticationRequired);
    connect(&qNetworkAccessManager, &QNetworkAccessManager::encrypted, this, &NetworkHandler::encrypted);
    connect(&qNetworkAccessManager, &QNetworkAccessManager::sslErrors, this, &NetworkHandler::sslErrors);
    connect(&qNetworkAccessManager, &QNetworkAccessManager::finished, this, &NetworkHandler::finished);
}

void NetworkHandler::get(const QString location){
    this->status =Status::Started;
    QNetworkReply * reply = qNetworkAccessManager.get(QNetworkRequest(QUrl(location)));
    if(!reply){
        this->status = Status::BadReply;
        return;
    }
    connect(reply, &QNetworkReply::readyRead, this, &NetworkHandler::readyRead);
}

void NetworkHandler::readyRead(){
    if(this->handShakeOccurred){
        QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());
        if(reply) this->jResponseObject = QJsonDocument::fromJson(reply->readAll()).object();
        this->status = Status::PassedReadyRead;
    }
    else{
        qobject_cast<QNetworkReply*>(sender())->abort();
        this->status = Status::FailedReadyReadCheck;
    }
}

void NetworkHandler::authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator){
    this->status = Status::NeedAuthentication;
    if(reply){reply->abort();}
    Q_UNUSED(authenticator);
}

void NetworkHandler::encrypted(QNetworkReply *reply){
    this->handShakeOccurred =true;
    Q_UNUSED(reply);
}

void NetworkHandler::finished(QNetworkReply *reply){
    if(this->status != Status::PassedReadyRead){
        if(reply) {reply->abort();}
        emit done(nullptr);
    }
    else
    {
        this->status = Status::PassedFinshed;
        emit done(&this->jResponseObject);
    }
}

void NetworkHandler::sslErrors(QNetworkReply *reply, const QList<QSslError> &errors){
    if(reply){reply->abort();}

    this->status = Status::SSLError;
    QFile file(QDir::currentPath() + "SSL_ERRORS.txt");

    if(!file.open(QIODevice::ReadWrite | QIODevice::Truncate| QIODevice::Text)) return; //no hope...

    for(QSslError err : errors){
        file.write(err.errorString().toLocal8Bit());
    }
    file.close();
}

