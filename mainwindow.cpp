
#include <QtWidgets>
#include "mainwindow.h"
#include "controlmessage.h"
#include "publishmessage.h"
#include "connectmessage.h"

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

    //初始化CONNECT报文页面
    ConnectMessage * connect_obj = new ConnectMessage(this);
    QWidget * connect_widget = connect_obj->uiInit();
    tabwidget->addTab(connect_widget, "CONNECT");

    //初始化PUBLISH报文页面
    PublishMessage * publish_obj = new PublishMessage(this);
    QWidget *publish_widget = publish_obj->uiInit();
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
