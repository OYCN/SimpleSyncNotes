#include "serverconfigdialog.h"
#include "ui_serverconfigdialog.h"

ServerConfigDialog::ServerConfigDialog(MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::ServerConfigDialog)
{
    configure = parent->configure;
    network = parent->network;
    ui->setupUi(this);

    ui->ip->setText(configure->serverIP);
    ui->port->setValue(configure->serverPort);

    connect(ui->ip, &QLineEdit::textChanged , this, [=](){
        configure->serverIP = ui->ip->text();
    });

    connect(ui->port, &QSpinBox::textChanged , this, [=](){
        configure->serverPort = ui->port->text().toInt();
    });

    connect(ui->connect, &QPushButton::clicked, this, &ServerConfigDialog::testConnectSlot);
    connect(ui->test, &QPushButton::clicked, this, &ServerConfigDialog::testFunctionSlot);
}

ServerConfigDialog::~ServerConfigDialog()
{
    delete ui;
}

void ServerConfigDialog::LogPrint(QString str, int limitlen)
{
//    static int row = 1;
//    str = QString("[%1] %2").arg(row++).arg(str);
//    log.append(str);
//    if(limitlen!=0 && log.length()>limitlen) log.removeFirst();
    ui->outlog->append(str);
    ui->outlog->setHtml(log.join("<br>"));
    ui->outlog->moveCursor(QTextCursor::End);
}

void ServerConfigDialog::testConnectSlot()
{
    QString ip = ui->ip->text();
    int port = ui->port->value();

    LogPrint(QString("将对%1:%2进行连接测试").arg(ip).arg(port));
    if(!network->TestConnect()) LogPrint(HTML_ERROR("连接错误，详情请见日志"));
    else LogPrint(HTML_SUCCESS("连接正常"));
}

void ServerConfigDialog::testFunctionSlot()
{
    QString ip = ui->ip->text();
    int port = ui->port->value();

    LogPrint(QString("将对%1:%2进行功能测试").arg(ip).arg(port));
    LogPrint("1)连接测试");
    if(!network->TestConnect()) LogPrint(HTML_ERROR("连接错误，详情请见日志"));
    else LogPrint(HTML_SUCCESS("连接正常"));
}

