#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName(QString("oPluss"));
    QCoreApplication::setApplicationName(QString("SimpleSyncNotes"));
    MainWindow w;
    w.show();
    return a.exec();
}
