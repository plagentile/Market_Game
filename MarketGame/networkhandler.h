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
        NotStarted,
        Started,
        PassedGet,
        PassedEncypted,
        PassedReadyRead,
        PassedMoveReply,
        PassedFinshed,
        FailedFinishedCheck,
        FailedEncryptCheck,
        FailedReadyReadCheck,
        FailedMoveReplyCheck,
        Internal_Errors,
        BadReply
    };

    Status getStatus() const;

public slots:
    void get(QString location);

private slots:
    void readyRead();
    void authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator);
    void encrypted(QNetworkReply *reply);
    void finished(QNetworkReply *reply);
    void sslErrors(QNetworkReply *reply, const QList<QSslError> &errors);

private:
    void moveReplyToFile(QNetworkReply* reply);

private:
   QNetworkAccessManager qNetworkAccessManager;
   Status status;
};

#endif // NETWORKHANDLER_H
