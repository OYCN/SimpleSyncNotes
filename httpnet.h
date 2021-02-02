#ifndef HTTPNET_H
#define HTTPNET_H

#include "inet.h"
#include "networkcenter.h"
#include <QtNetwork>
#include "configure.h"

class HTTPnet : public INet
{
public:
    HTTPnet(Configure *conf, QObject *parent = nullptr);
    bool Send(QString) override;
    bool Recv(QString &) override;

private:
    QNetworkAccessManager *manager;
    Configure *configure;
    QString buff;
    bool isRecv;

private slots:
    void replyFinished(QNetworkReply *);
};

#endif // HTTPNET_H
