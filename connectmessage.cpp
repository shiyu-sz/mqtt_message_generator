#include "connectmessage.h"
#include <QtWidgets>

ConnectMessage::ConnectMessage(QWidget *parent)
{

}


/**
 * @brief PublishMessage::uiInit 初始化ui
 * @param widget
 */
void ConnectMessage::uiInit(QWidget *widget)
{
    //协仪版本
    QLabel * level_label = new QLabel("Protocol Level:");
    level_combobox = new QComboBox();
    level_combobox->addItem("3.1.1" , 4);
    level_combobox->addItem("3.1"   , 3);

    //协仪版本的水平布局
    QHBoxLayout *hLayout_1 = new QHBoxLayout();
    hLayout_1->addWidget(level_label);
    hLayout_1->addWidget(level_combobox);
    hLayout_1->setSpacing(10);
    hLayout_1->setContentsMargins(0,0,10,10);

    //Connect Flags bit
    QCheckBox *CheckBox_bit7 = new QCheckBox("User Name Flag", this);
    QCheckBox *CheckBox_bit6 = new QCheckBox("Password Flag", this);
    QCheckBox *CheckBox_bit5 = new QCheckBox("Will Retain", this);

    //Will的QoS
    QLabel * qos_label = new QLabel("Will QoS:");
    QComboBox *qos_combobox = new QComboBox();
    qos_combobox->addItem("0", 0);
    qos_combobox->addItem("1", 1);
    qos_combobox->addItem("2", 2);

    //Qos的水平布局
    QHBoxLayout *hLayout_2 = new QHBoxLayout();
    hLayout_2->addWidget(qos_label);
    hLayout_2->addWidget(qos_combobox);
    hLayout_2->setSpacing(10);
    hLayout_2->setContentsMargins(0,0,10,10);

    QCheckBox *CheckBox_bit2 = new QCheckBox("Will Flag", this);
    QCheckBox *CheckBox_bit1 = new QCheckBox("Clean Session", this);

    connect(CheckBox_bit7, SIGNAL(stateChanged(int)), this, SLOT(slots_CheckBox_bit7_stateChanged()));
    connect(CheckBox_bit6, SIGNAL(stateChanged(int)), this, SLOT(slots_CheckBox_bit6_stateChanged()));
    connect(CheckBox_bit5, SIGNAL(stateChanged(int)), this, SLOT(slots_CheckBox_bit5_stateChanged()));
    connect(CheckBox_bit2, SIGNAL(stateChanged(int)), this, SLOT(slots_CheckBox_bit2_stateChanged()));
    connect(CheckBox_bit1, SIGNAL(stateChanged(int)), this, SLOT(slots_CheckBox_bit1_stateChanged()));

    //Connect Flags垂直布局
    QVBoxLayout *vLayout_1 = new QVBoxLayout();
    vLayout_1->addWidget(CheckBox_bit7);
    vLayout_1->addWidget(CheckBox_bit6);
    vLayout_1->addWidget(CheckBox_bit5);
    vLayout_1->addLayout(hLayout_2);
    vLayout_1->addWidget(CheckBox_bit2);
    vLayout_1->addWidget(CheckBox_bit1);

    //Connect Flags盒子
    QGroupBox *connect_flag_groupbox = new QGroupBox("Connect Flags", this);
    connect_flag_groupbox->setLayout(vLayout_1);

    //所有控件垂直布局
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->addLayout(hLayout_1);
    vLayout->addWidget(connect_flag_groupbox);

    widget->setLayout(vLayout);
}
