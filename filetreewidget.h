#ifndef FILETREEWIDGET_H
#define FILETREEWIDGET_H

#include <QTreeWidget>
#include <QMenu>
#include <QDebug>
#include <QApplication>
#include <QHeaderView>
#include <QScrollBar>
#include <QInputDialog>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

class FileTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    FileTreeWidget(QWidget *parent = 0);
    bool UpdateFromJsonStr(QString &);
    QTreeWidgetItem *CreateTopItem(QString);
    QTreeWidgetItem *CreateFileItem(QString, QTreeWidgetItem *);
    QTreeWidgetItem *CreateDirItem(QString, QTreeWidgetItem *);
private:
    QMenu *dirMenu;  //文件夹菜单栏
    QMenu *fileMenu;  //文件菜单栏
signals:
private slots:
    void itemDoubleClickSolt(QTreeWidgetItem *, int);
    void itemRightClickSolt(QTreeWidgetItem *, int);
    void menuClickSolt(QAction *);
};

#endif // FILETREEWIDGET_H
