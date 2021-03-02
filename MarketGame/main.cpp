#include "Coordinator.h"
#include "symbolternarysearchtree.h"
#include "networkhandler.h"

int32_t main(int argc, char *argv[]){

    QApplication a(argc, argv);
    Coordinator * pCoordinator = Coordinator::getInstance();

    //int32_t num = pCoordinator->run(a);
    NetworkHandler networkHandler;
    QByteArray data;
    data.append("param1=hello");
    data.append("&");
    data.append("param2=world");
    networkHandler.post("https://www.postman-echo.com/post",data);

    //qDebug() << QSslSocket::supportsSsl() << QSslSocket::sslLibraryBuildVersionString() << QSslSocket::sslLibraryVersionString();
    delete pCoordinator;                                        //Ensure that leaks are plugged
    return a.exec();
}
