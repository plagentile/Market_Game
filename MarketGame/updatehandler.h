#ifndef UPDATEHANDLER_H
#define UPDATEHANDLER_H
#include <QTimer>
#include <QEventLoop>
#include <QDebug>
class UpdateHandler : public QObject
{
    Q_OBJECT
public:
    explicit UpdateHandler(QObject * parent = nullptr);
    UpdateHandler() =delete;
    UpdateHandler(const UpdateHandler & assign) =delete;
    UpdateHandler & operator = (const UpdateHandler& assign) =delete;
    ~UpdateHandler() = default;

public slots:
    void start();
    void stop();
    void timeout();

private:
    QTimer timer;
    QEventLoop loop;
};

#endif // UPDATEHANDLER_H
