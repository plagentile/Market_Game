#include "networkhandler.h"

NetworkHandler::NetworkHandler(QObject *parent) : QObject(parent), status(Status::NotStarted)
{
    connect(&qNetworkAccessManager, &QNetworkAccessManager::authenticationRequired, this, &NetworkHandler::authenticationRequired);
    connect(&qNetworkAccessManager, &QNetworkAccessManager::encrypted, this, &NetworkHandler::encrypted);
    connect(&qNetworkAccessManager, &QNetworkAccessManager::sslErrors, this, &NetworkHandler::sslErrors);
    connect(&qNetworkAccessManager, &QNetworkAccessManager::finished, this, &NetworkHandler::finished);
}

void NetworkHandler::get(QString location){
    this->status =Status::Started;
    QNetworkReply * reply = qNetworkAccessManager.get(QNetworkRequest(QUrl(location)));
    connect(reply, &QNetworkReply::readyRead, this, &NetworkHandler::readyRead);
}

void NetworkHandler::readyRead(){
    if(this->status == Status::PassedEncypted){
        this->status = Status::PassedReadyRead;
        this->moveReplyToFile(qobject_cast<QNetworkReply*>(sender()));
    }else{
        this->status = Status::FailedReadyReadCheck;
    }
}

void NetworkHandler::authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator)
{
    Q_UNUSED(reply);
    Q_UNUSED(authenticator);
}

void NetworkHandler::encrypted(QNetworkReply *reply)
{
    if(status == Status::NotStarted)
    {
        status = Status::PassedEncypted;
    }
    else
    {
        status = Status::FailedEncryptCheck;
        reply->abort();
    }
}

void NetworkHandler::finished(QNetworkReply *reply)
{
    if(this->status == Status::PassedMoveReply)
    {
        this->status = Status::PassedFinshed;
    }
    else
    {
        this->status = Status::FailedFinishedCheck;
        reply->abort();
    }
}

void NetworkHandler::sslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
    reply->abort();
    Q_UNUSED(errors);
}



void NetworkHandler::moveReplyToFile(QNetworkReply* reply)
{
    if(this->status == Status::PassedEncypted)
    {
        if(reply)
        {
            qInfo() << reply->readAll() << "\n";
            this->status = Status::PassedMoveReply;
        }
        else
        {
            reply->abort();
            status = Status::BadReply;
        }
    }
    else
    {
        this->status = Status::FailedMoveReplyCheck;
    }
}

NetworkHandler::Status NetworkHandler::getStatus() const{
    return status;
}













