#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("mqtt报文生成工具(designed by shiyu)");
    w.show();

    return a.exec();
}
