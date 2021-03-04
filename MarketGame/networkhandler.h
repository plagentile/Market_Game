#ifndef NETWORKHANDLER_H
#define NETWORKHANDLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QAuthenticator>
class NetworkHandler : public QObject
{
    Q_OBJECT
public:
    explicit NetworkHandler(QObject *parent = nullptr);

public:
    enum class Status
    {
        NotStarted = 0,
        Started =1,
        InGet =2,
        InEncypted =3,
        InReadyRead = 4,
        Internal_Errors  =5,
        FailedEncrypt
    };



public slots:
    void get(QString location);

private slots:
    void readyRead();
    void authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator);
    void encrypted(QNetworkReply *reply);
    void finished(QNetworkReply *reply);
    void sslErrors(QNetworkReply *reply, const QList<QSslError> &errors);

private:
   QNetworkAccessManager qNetworkAccessManager;

};

#endif // NETWORKHANDLER_H
