#include "configure.h"

Configure::Configure(QObject *parent) : QObject(parent)
{
    settings = new QSettings(QSettings::NativeFormat,
                         QSettings::UserScope,
                         QCoreApplication::organizationName(),
                         QCoreApplication::applicationName());
    Reload();
}

void Configure::Reload()
{
    serverIP = settings->value("serverIP", "127.0.0.1").toString();
    serverPort = settings->value("serverPort", 8888).toInt();
}

void Configure::Submit()
{
    settings->setValue("serverIP", serverIP);
    settings->setValue("serverPort", serverPort);
}
