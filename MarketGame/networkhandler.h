#ifndef NETWORKHANDLER_H
#define NETWORKHANDLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QAuthenticator>
#include <QFile>
#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>
class NetworkHandler : public QObject
{
    Q_OBJECT
public:
    explicit NetworkHandler(QObject *parent = nullptr);
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
        PassedReadyRead,
        PassedFinshed,
        NeedAuthentication,
        SSLError,
        FailedEncryptCheck,
        FailedReadyReadCheck,
        Internal_Errors,
        BadReply
    };

    Status getStatus() const;

public:
   QJsonArray getJSONReponse();

public: signals:
    void done(Status status, const QJsonObject*jReponseObject );

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
   QJsonObject jResponseObject;
   Status status;
   bool handShakeOccurred;
};

#endif // NETWORKHANDLER_H
