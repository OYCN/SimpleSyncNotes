#include "filetreewidget.h"

FileTreeWidget::FileTreeWidget(QWidget *parent): QTreeWidget(parent)
{
    this->header()->hide();
    this->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    this->header()->setStretchLastSection(false);

//    this->setAnimated(true); //展开折叠动画

    // 创建右击文件夹的菜单栏
    dirMenu = new QMenu();
    dirMenu->addAction("新建文件");
    dirMenu->addAction("重命名");
    dirMenu->addSeparator();
    dirMenu->addAction("新建文件夹");
    dirMenu->addAction("删除文件夹");
    dirMenu->addAction("在文件夹中查找");
    dirMenu->addAction("关闭项目");
    // 创建右击文件的菜单栏
    fileMenu = new QMenu();
    fileMenu->addAction("重命名");
    fileMenu->addAction("删除文件");
    connect(dirMenu,&QMenu::triggered,this,&FileTreeWidget::menuClickSolt);
    connect(fileMenu,&QMenu::triggered,this,&FileTreeWidget::menuClickSolt);
    connect(this,&FileTreeWidget::itemPressed,this,&FileTreeWidget::itemRightClickSolt);
    connect(this,&FileTreeWidget::itemDoubleClicked,this,&FileTreeWidget::itemDoubleClickSolt);

    // DEBUG
//    QTreeWidgetItem *root = CreateTopItem("根节点");
//    QTreeWidgetItem *dir1 = CreateDirItem("文件夹1", root);
//    QTreeWidgetItem *dir2 = CreateDirItem("文件夹2", root);
//    for(int i=0; i<10; i++)
//    {
//        dir2 = CreateDirItem("文件夹"+QString::number(i+3), dir2);
//    }
//    for(int i=0; i<50; i++)
//    {
//        CreateFileItem("文件"+QString::number(i), dir1);
//    }
}

bool FileTreeWidget::UpdateFromJsonStr(QString &str)
{
//    qDebug() << str;
    QJsonDocument json = QJsonDocument::fromJson(str.toUtf8());
//    qDebug() << json;
    if(json.isNull()) return false;
    if(json["type"]!="FileTree") return false;
    QJsonArray root = json["root"].toArray();
    QJsonObject nodes = json["nodes"].toObject();
    while(root.size()!=0)
    {
        QString t = root.first().toString();
        root.pop_front();
        QJsonObject j = nodes[t].toObject();
        if(j["type"].toString().compare("dir")==0) CreateTopItem(t);
    }
    qDebug() << root;
    qDebug() << nodes;
    return true;
}

// 创建文件树的根
QTreeWidgetItem *FileTreeWidget::CreateTopItem(QString name)
{
    QTreeWidgetItem *root = new QTreeWidgetItem();
    this->addTopLevelItem(root);
    root->setIcon(0,QIcon(":/FileTree/Res/Svg/wenjianjiadakai.svg"));
    root->setText(0, name);
    root->setExpanded(true);
    return root;
}

QTreeWidgetItem *FileTreeWidget::CreateFileItem(QString name, QTreeWidgetItem *parent)
{
    QTreeWidgetItem *child = new QTreeWidgetItem(parent);
    child->setIcon(0,QIcon(":/FileTree/Res/Svg/jilu.svg"));
    child->setText(0,name);
    child->setToolTip(0,"文件");
    return child;
}

QTreeWidgetItem *FileTreeWidget::CreateDirItem(QString name, QTreeWidgetItem *parent)
{
    QTreeWidgetItem *child = new QTreeWidgetItem(parent);
    child->setIcon(0,QIcon(":/FileTree/Res/Svg/wenjianjiadakai.svg"));
    child->setText(0,name);
    child->setToolTip(0,"文件夹");
    child->setExpanded(true);
    return child;
}

// 双击槽函数检测是文件还是目录
void FileTreeWidget::itemDoubleClickSolt(QTreeWidgetItem *item, int /*column*/)
{

    qDebug() << "双击Item";
}

// 鼠标右键单击文件或文件夹时所执行的操作
void FileTreeWidget::itemRightClickSolt(QTreeWidgetItem * item, int /*column*/)
{
//    this->resizeColumnToContents(0);
    if(qApp->mouseButtons() == Qt::RightButton)   //判断是否为右键
    {
        if(item->toolTip(0) == "文件"){
            fileMenu->exec(QCursor::pos()); //显示右键菜单栏
        }
        else{
            dirMenu->exec(QCursor::pos());  //显示右键菜单栏
        }
    }
}

void FileTreeWidget::menuClickSolt(QAction *act)
{
    qDebug() << "Item " <<act->text();
    if(act->text()=="关闭项目")
    {
        qDebug() << "in关闭项目";
    }
    if(act->text() == "删除文件")
    {
        qDebug() << "in删除文件";
    }
    if(act->text() == "删除文件夹")
    {
        qDebug() << "in删除文件夹";
    }
    if(act->text() == "重命名")
    {
        QString dlgTitle="重命名";
        QString txtLabel="请输入名字";
        QString defaultInput="";
        QLineEdit::EchoMode echoMode=QLineEdit::Normal;//正常文字输入
        bool ok=true;
        QString text = QInputDialog::getText(this, dlgTitle,txtLabel, echoMode,defaultInput, &ok);
        if (ok && !text.isEmpty())
            qDebug() << "重命名" << text;
    }
    if(act->text() == "新建文件")
    {
        QString dlgTitle="新建文件";
        QString txtLabel="请输入文件名";
        QString defaultInput="";
        QLineEdit::EchoMode echoMode=QLineEdit::Normal;//正常文字输入
        bool ok=true;
        QString text = QInputDialog::getText(this, dlgTitle,txtLabel, echoMode,defaultInput, &ok);
        if (ok && !text.isEmpty())
            qDebug() << "新建" << text;
    }
    if(act->text()=="新建文件夹")
    {
        QString dlgTitle="新建文件夹";
        QString txtLabel="请输入文件夹名";
        QString defaultInput="";
        QLineEdit::EchoMode echoMode=QLineEdit::Normal;//正常文字输入
        bool ok=true;
        QString text = QInputDialog::getText(this, dlgTitle,txtLabel, echoMode,defaultInput, &ok);
        if (ok && !text.isEmpty())
            qDebug() << "新建" << text;
    }
}

