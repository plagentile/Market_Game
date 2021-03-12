#ifndef NETWORKHANDLER_H
#define NETWORKHANDLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QAuthenticator>
#include <QFile>
#include <QDir>
#include "chartbuilder.h"
class NetworkHandler : public QObject
{
    Q_OBJECT
public:
    NetworkHandler(QObject *parent = nullptr);
    NetworkHandler() =delete;
    NetworkHandler(const NetworkHandler & assign) = delete;
    NetworkHandler & operator =(const NetworkHandler & assign) =delete;
    ~NetworkHandler() = default;
public:
    enum class Status
    {
        NotStarted,
        Started,
        PassedGet,
        PassedEncypted,
        PassedReadyRead,
        PassedMoveReply,
        PassedFinshed,
        NeedAuthentication,
        SSLError,
        FailedEncryptCheck,
        FailedReadyReadCheck,
        FailedMoveReplyCheck,
        Internal_Errors,
        BadReply
    };

    Status getStatus() const;

public:
   QJsonArray getJSONReponse();

public slots:
    void get(const QString location);

private slots:
    void readyRead();
    void authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator);
    void encrypted(QNetworkReply *reply);
    void finished(QNetworkReply *reply);
    void sslErrors(QNetworkReply *reply, const QList<QSslError> &errors);

private:
   QNetworkAccessManager qNetworkAccessManager;
   QJsonObject jReposneObject;
   Status status;
};

#endif // NETWORKHANDLER_H
