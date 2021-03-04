#include "networkhandler.h"

NetworkHandler::NetworkHandler(QObject *parent) : QObject(parent), status(Status::NotStarted)
{
    connect(&qNetworkAccessManager, &QNetworkAccessManager::authenticationRequired, this, &NetworkHandler::authenticationRequired);
    connect(&qNetworkAccessManager, &QNetworkAccessManager::encrypted, this, &NetworkHandler::encrypted);
    connect(&qNetworkAccessManager, &QNetworkAccessManager::sslErrors, this, &NetworkHandler::sslErrors);
    connect(&qNetworkAccessManager, &QNetworkAccessManager::finished, this, &NetworkHandler::finished);
}

void NetworkHandler::get(const QString location, const QString currSymbol){
    this->status =Status::Started;
    this->currentSymbol = currSymbol;
    QNetworkReply * reply = qNetworkAccessManager.get(QNetworkRequest(QUrl(location)));
    connect(reply, &QNetworkReply::readyRead, this, &NetworkHandler::readyRead);
}

void NetworkHandler::readyRead(){
    if(this->status == Status::PassedEncypted)
    {
        this->status = Status::PassedReadyRead;
        this->moveReplyToFile(qobject_cast<QNetworkReply*>(sender()));
    }
    else
    {
        qobject_cast<QNetworkReply*>(sender())->abort();
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
    if(status == Status::Started)
    {
        status = Status::PassedEncypted;
    }
    else
    {
        status = Status::FailedEncryptCheck;
        reply->abort();
    }
}

void NetworkHandler::finished(QNetworkReply *reply){
    if(this->status != Status::PassedMoveReply){
        reply->abort();
        return;
    }

    this->status = Status::PassedFinshed;
}

void NetworkHandler::sslErrors(QNetworkReply *reply, const QList<QSslError> &errors){
    reply->abort();
    Q_UNUSED(errors);
}

void NetworkHandler::moveReplyToFile(QNetworkReply* reply)
{
    if(!reply) {this->status = Status::BadReply; return;}
    if(this->status != Status::PassedReadyRead){ reply->abort(); this->status = Status::FailedMoveReplyCheck;  return;}

    QFile file(QDir::currentPath() + currentSymbol+".txt");
    if(!file.open(QIODevice::ReadWrite | QIODevice::Truncate| QIODevice::Text)) {
        this->status = Status::Internal_Errors;
        reply->abort();
        return;
    }

    file.write(reply->readAll());
    file.close();

    this->status = Status::PassedMoveReply;
}

NetworkHandler::Status NetworkHandler::getStatus() const{
    return status;
}













