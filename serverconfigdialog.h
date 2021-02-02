#ifndef SERVERCONFIGDIALOG_H
#define SERVERCONFIGDIALOG_H

#include <QDialog>
#include <QTextCursor>
#include "mainwindow.h"

#define HTML_ERROR(x) "<font color=\"red\">" x "</font>"
#define HTML_WARRING(x) "<font color=\"brown\">" x "</font>"
#define HTML_SUCCESS(x) "<font color=\"green\">" x "</font>"
#define HTML_INFO(x) "<font color=\"black\">" x "</font>"
#define HTML_DEBUG(x) "<font color=\"blue\">" x "</font>"

namespace Ui {
class ServerConfigDialog;
}

class ServerConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ServerConfigDialog(MainWindow *parent = nullptr);
    ~ServerConfigDialog();

private:
    void LogPrint(QString, int limitlen=0);

private:
    Ui::ServerConfigDialog *ui;
    QStringList log;
    Configure *configure;
    NetWorkCenter *network;

private slots:
    void testConnectSlot();
    void testFunctionSlot();
};

#endif // SERVERCONFIGDIALOG_H
