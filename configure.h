#ifndef CONFIGURE_H
#define CONFIGURE_H

#include <QObject>
#include <QSettings>
#include <QApplication>

class Configure : public QObject
{
    Q_OBJECT
public:
    explicit Configure(QObject *parent = nullptr);
    void Reload();
    void Submit();

private:
    QSettings *settings;

public:
    QString serverIP;
//    QString serverHost;
    int serverPort;



signals:

};

#endif // CONFIGURE_H
