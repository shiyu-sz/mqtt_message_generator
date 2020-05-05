
#include <QDebug>
#include <QHBoxLayout>
#include "mainwindow.h"
#include "controlmessage.h"
#include "publishmessage.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    //创建一个顶层的widget
    QWidget *widget = new QWidget();
    this->setCentralWidget(widget);

    //创建tabwidget
    QTabWidget * tabwidget = new QTabWidget();
    //选择路径的水平布局
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(tabwidget);
    widget->setLayout(hLayout);

    //初始化PUBLISH报文页面
    QWidget *publish_widget = new QWidget();
    PublishMessage * publish_obj = new PublishMessage(this);
    publish_obj->uiInit(publish_widget);
    tabwidget->addTab(publish_widget, "PUBLISH");

//    publish_obj->setDup(0);
//    publish_obj->setQos(0);
//    publish_obj->setRetain(1);
//    publish_obj->setTopicName("123");
//    publish_obj->setPackId(12);
//    publish_obj->setPayload("456");
//    qDebug() << "message" <<publish_obj->generateMessage();

}

MainWindow::~MainWindow()
{

}
