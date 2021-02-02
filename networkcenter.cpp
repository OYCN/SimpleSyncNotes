#include "networkcenter.h"

NetWorkCenter::NetWorkCenter(Protocol ptcl, Configure *conf, QObject *parent) :
    QObject(parent),
    configure(conf)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=](){isTimeout = true;});
    if(ptcl == Protocol::HTTP)
    {
        net = new HTTPnet(configure, this);
    }
    else if(ptcl == Protocol::TCP)
    {

    }
    else if(ptcl == Protocol::UDP)
    {

    }
    else
    {

    }
}

bool NetWorkCenter::catVersion(QString &str)
{
    if(!net->Send("version?"))
    {
        qDebug() << "版本查询时信息发送失败";
    }
    else
    {
        if(waitRecv(str, 1000))
        {
            return true;
        }
        qDebug() << "版本查询接收超时";
    }
    return false;
}

bool NetWorkCenter::waitRecv(QString &str, int time)
{
    timer->setInterval(time);
    isTimeout = false;
    timer->start();
    while(!isTimeout)
    {
        if(net->Recv(str))
        {
            timer->stop();
            return true;
        }
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    return false;
}

bool NetWorkCenter::TestConnect()
{
    QString tmp;
    if(catVersion(tmp))
    {
        qDebug() << tmp;
        return true;
    }
    else
    {
        return false;
    }
}

bool NetWorkCenter::getFileTree(QString &str)
{
    if(!net->Send("FileTree?"))
    {
        qDebug() << "文件树查询时信息发送失败";
    }
    else
    {
        if(waitRecv(str, 1000))
        {
            return true;
        }
        qDebug() << "文件树查询接收超时";
    }
    return false;
}
