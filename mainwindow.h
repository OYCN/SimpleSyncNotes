#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QShortcut>
#include <QTextCursor>
#include <QLabel>
#include <QTextEdit>
#include <QAction>
#include <QSettings>
#include "configure.h"
#include "networkcenter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString textType;
    QString nowText;
//    QTextCursor nowCursor;
    int64_t position;
    QLabel *displayColRow;

public:
    Configure *configure;
    NetWorkCenter *network;

private slots:
    void toPureTextSlot();
    void toMarkdownTextSlot();
    void cursorPositionChangedSlot();
    void textChangedSlot();
    void servConfigSlot();
};
#endif // MAINWINDOW_H
