#ifndef NETWORKCENTER_H
#define NETWORKCENTER_H

#include <QObject>
#include <QCoreApplication>
#include "inet.h"
#include "configure.h"
#include "httpnet.h"

enum Protocol
{
    HTTP,
    TCP,
    UDP
};

class NetWorkCenter : public QObject
{
    Q_OBJECT
public:
    explicit NetWorkCenter(Protocol ptcl, Configure *conf, QObject *parent = nullptr);
    bool TestConnect();
    bool catVersion(QString &);
    bool getFileTree(QString &);

private:
    bool waitRecv(QString &, int);
private:
    INet *net;
    Configure *configure;
    QTimer *timer;
    bool isTimeout;
signals:

private slots:
};

#endif // NETWORKCENTER_H
