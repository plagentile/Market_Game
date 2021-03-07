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
    if(!reply){
        this->status = Status::BadReply;
        return;
    }
    connect(reply, &QNetworkReply::readyRead, this, &NetworkHandler::readyRead);
}

void NetworkHandler::readyRead(){
    if(this->status == Status::PassedEncypted){
        this->status = Status::PassedReadyRead;
        QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());
        QJsonObject jObject = QJsonDocument::fromJson(reply->readAll()).object();

        QJsonValue value = jObject.value("candles");
        QJsonArray  arr = value.toArray();

        //print out all of the lows....
        for(const QJsonValue & v : arr){
            QDateTime tpast = QDateTime::fromMSecsSinceEpoch(v.toObject().value("datetime").toDouble());
            //QDateTime time = QDateTime::fromTime_t()
            qDebug() << tpast;
            //qDebug() << v.toObject().value("datetime").toDouble() << "\n";
        }
        //Now have an array of 52 arrays.....

    }
    else{
        qobject_cast<QNetworkReply*>(sender())->abort();
        this->status = Status::FailedReadyReadCheck;
    }
}

void NetworkHandler::authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator){
    this->status = Status::NeedAuthentication;
    if(reply) reply->abort();
    Q_UNUSED(authenticator);
}

void NetworkHandler::encrypted(QNetworkReply *reply){
    if(status != Status::Started){
        status = Status::FailedEncryptCheck;
        if(reply)reply->abort();
        return;
    }
    status = Status::PassedEncypted;
}

void NetworkHandler::finished(QNetworkReply *reply){
    if(this->status != Status::PassedMoveReply){
        if(reply) reply->abort();
        return;
    }
    this->status = Status::PassedFinshed;
}

void NetworkHandler::sslErrors(QNetworkReply *reply, const QList<QSslError> &errors){
    if(reply) reply->abort();
    this->status = Status::SSLError;
    QFile file(QDir::currentPath() + "SSL_ERRORS.txt");

    if(!file.open(QIODevice::ReadWrite | QIODevice::Truncate| QIODevice::Text)) return; //no hope...

    for(QSslError err : errors){
        file.write(err.errorString().toLocal8Bit());
    }

    file.close();
}


NetworkHandler::Status NetworkHandler::getStatus() const{
    return status;
}













