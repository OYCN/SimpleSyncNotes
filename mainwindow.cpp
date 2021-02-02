#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serverconfigdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->splitter->setStretchFactor(0, 2);
    ui->splitter->setStretchFactor(1, 8);
//    ui->textEdit->setHtml("<font color='red' size='6'><red>Hello PyQt5!\n单击按钮。</font>");
//    ui->textEdit->setMarkdown("# asdf");
    textType = "pure";
    QFont font = QFont("宋体",20,2);
    ui->textEdit->setFont(font);
    configure = new Configure(this);
    network = new NetWorkCenter(Protocol::HTTP, configure, this);

    QShortcut *toPureTextSignal = new QShortcut(this);
    toPureTextSignal->setKey(tr("ctrl+e"));
    toPureTextSignal->setAutoRepeat(false);
    connect(toPureTextSignal, &QShortcut::activated, this, &MainWindow::toPureTextSlot);

    QShortcut *toMarkdownTextSignal = new QShortcut(this);
    toMarkdownTextSignal->setKey(tr("ctrl+r"));
    toMarkdownTextSignal->setAutoRepeat(false);
    connect(toMarkdownTextSignal, &QShortcut::activated, this, &MainWindow::toMarkdownTextSlot);

    displayColRow = new QLabel(this);
    ui->statusbar->addPermanentWidget(displayColRow);
    connect(ui->textEdit, &QTextEdit::cursorPositionChanged, this, &MainWindow::cursorPositionChangedSlot);
    connect(ui->textEdit, &QTextEdit::textChanged, this, &MainWindow::textChangedSlot);
    connect(ui->actiontestServer, &QAction::triggered, this, &MainWindow::servConfigSlot);

    QString tmp;
    if(!(network->getFileTree(tmp) && ui->treeWidget->UpdateFromJsonStr(tmp)))
        qDebug() << "文件树未更新";

    emit ui->textEdit->textChanged();
    emit ui->textEdit->cursorPositionChanged();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::toPureTextSlot()
{
    if(textType.compare("markdown")==0)
    {
        ui->textEdit->setPlainText(nowText);
        ui->textEdit->setReadOnly(false);
//        qDebug() << "before set" << nowCursor.position();
//        ui->textEdit->setTextCursor(nowCursor);
        QTextCursor tmpCursor = ui->textEdit->textCursor();
        tmpCursor.setPosition(position);
        ui->textEdit->setTextCursor(tmpCursor);
//        qDebug() << "after set" << ui->textEdit->textCursor().position();
        textType = "pure";
        emit ui->textEdit->cursorPositionChanged();
    }
}

void MainWindow::toMarkdownTextSlot()
{
    if(textType.compare("pure")==0)
    {
        textType = "markdown";
        ui->textEdit->setMarkdown(nowText);
        ui->textEdit->setReadOnly(true);
        QString str = QString("行: -- | 列: -- | 字数: --/%1")
                .arg(ui->textEdit->toPlainText().remove('\r').remove('\n').length(), 0, 10, QLatin1Char('0'));
        displayColRow->setText(str);
    }
}

void MainWindow::cursorPositionChangedSlot()
{
    if(textType.compare("pure")==0)
    {
        QString str;
        QTextCursor nowCursor = ui->textEdit->textCursor();
        str = QString("行: %1 | 列: %2 | 字数: %3/%4")
                .arg(nowCursor.blockNumber(), 0, 10, QLatin1Char('0'))
                .arg(nowCursor.positionInBlock(), 0, 10, QLatin1Char('0'))
                .arg(nowCursor.position(), 0, 10, QLatin1Char('0'))
                .arg(nowText.length(), 0, 10, QLatin1Char('0'));
        displayColRow->setText(str);
        position = nowCursor.position();
//        qDebug() << "restor cursor" << nowCursor.position();
    }
}

void MainWindow::textChangedSlot()
{
    if(textType.compare("pure")==0)
    {
        nowText = ui->textEdit->toPlainText();
    }
}

void MainWindow::servConfigSlot()
{
//    qDebug() << "will start server configure";
    ServerConfigDialog scd(this);
    if(scd.exec()==ServerConfigDialog::Accepted)
    {
        qDebug() << "配置完成";
        configure->Submit();
    }
    else
    {
        qDebug() << "配置取消";
        configure->Reload();
    }
}
