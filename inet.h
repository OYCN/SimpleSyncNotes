#ifndef INET_H
#define INET_H

#include <QObject>

class INet : public QObject
{
    Q_OBJECT
public:
    explicit INet(QObject *parent = nullptr);
    virtual bool Send(QString) = 0;
    virtual bool Recv(QString &) = 0;

signals:

};

#endif // INET_H
