#include "httpnet.h"

HTTPnet::HTTPnet(Configure *conf, QObject *parent):
    INet(parent),
    configure(conf)
{
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &HTTPnet::replyFinished);
}

bool HTTPnet::Send(QString data)
{
    if(isRecv == true)
    {
        isRecv = false;
//        manager->post(QNetworkRequest(QUrl(
//                                         "http://" +
//                                         configure->serverIP +
//                                         ":" +
//                                         QString(configure->serverPort) +
//                                         "api")),
//                      data.toUtf8());
        manager->post(QNetworkRequest(QUrl("http://api.opluss.top/api.php")), data.toUtf8());
//        manager->get(QNetworkRequest(QUrl("http://api.opluss.top")));
        return true;
    }
    else
    {
        return false;
    }
}

bool HTTPnet::Recv(QString &data)
{
    if(isRecv == true)
    {
        data = buff;
    }
    return isRecv;
}

void HTTPnet::replyFinished(QNetworkReply *reply)
{
    QTextCodec *codec = QTextCodec::codecForName("utf8");
    buff = codec->toUnicode(reply->readAll());
    reply->deleteLater();
    isRecv = true;
}
