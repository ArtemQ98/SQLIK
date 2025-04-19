#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    a.setWindowIcon(QIcon(":/res/img/ico.png"));
    w.showMaximized();
    w.show();
    return a.exec();
}
