#ifndef NETWORKHANDLER_H
#define NETWORKHANDLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QAuthenticator>
#include <QFile>
#include <QDir>
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
        NeedAuthentication,
        SSLError,
        FailedEncryptCheck,
        FailedReadyReadCheck,
        FailedMoveReplyCheck,
        Internal_Errors,
        BadReply
    };

    Status getStatus() const;

public slots:
    void get(const QString location, const QString currSymbol);

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
   QString currentSymbol;
   Status status;
};

#endif // NETWORKHANDLER_H
