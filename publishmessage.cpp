
#include <QDebug>
#include <QComboBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QButtonGroup>
#include <QRadioButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include "publishmessage.h"

PublishMessage::PublishMessage(QWidget *widget)
{
    Ui_Init(widget);
}

void PublishMessage::Generate_Message(void)
{
    //第一个字节
    quint8 head = 0;
    head = (type&0x0f)<<4 | (DUP&0x01)<<3 | (QoS&0x03)<<1 | (RETAIN&0x01);
    All_Byte.append(head);

    //剩余长度
    quint32 overlength = 0;
    overlength = sizeof(topic_len) + topic_name.length() + sizeof(pack_id);
    Compute_Remaining_Length(overlength);
    All_Byte.append(RemainingLength);

    //主题长度
    All_Byte.append(topic_len/256);
    All_Byte.append(topic_len%256);

    //主题名
    All_Byte.append(topic_name);

    //标识符
    All_Byte.append(pack_id/256);
    All_Byte.append(pack_id%256);

    qDebug() << "All_Byte = " << All_Byte;
}

void PublishMessage::Ui_Init(QWidget *widget)
{
    //创建dup
    QLabel * dup_label = new QLabel("DUP:");
    QComboBox * dup_combobox = new QComboBox();
    dup_combobox->addItem("0", 0);
    dup_combobox->addItem("1", 1);

    //dup的水平布局
    QHBoxLayout *hLayout_1 = new QHBoxLayout();
    hLayout_1->addWidget(dup_label);
    hLayout_1->addWidget(dup_combobox);
    hLayout_1->setSpacing(10);
    hLayout_1->setContentsMargins(0,0,10,10);

    //创建QoS
    QLabel * qos_label = new QLabel("QoS:");
    QComboBox * qos_combobox = new QComboBox();
    qos_combobox->addItem("0", 0);
    qos_combobox->addItem("1", 1);
    qos_combobox->addItem("2", 2);

    //Qos的水平布局
    QHBoxLayout *hLayout_2 = new QHBoxLayout();
    hLayout_2->addWidget(qos_label);
    hLayout_2->addWidget(qos_combobox);
    hLayout_2->setSpacing(10);
    hLayout_2->setContentsMargins(0,0,10,10);

    //创建RETAIN
    QLabel * retain_label = new QLabel("RETAIN:");
    QComboBox * retain_combobox = new QComboBox();
    retain_combobox->addItem("0", 0);
    retain_combobox->addItem("1", 1);

    //RETAIN的水平布局
    QHBoxLayout *hLayout_3 = new QHBoxLayout();
    hLayout_3->addWidget(retain_label);
    hLayout_3->addWidget(retain_combobox);
    hLayout_3->setSpacing(10);
    hLayout_3->setContentsMargins(0,0,10,10);

    //创建选择格式单选框
    QLabel * format_label = new QLabel("Topic Name Format:");
    QButtonGroup *RadioGroup = new QButtonGroup();
    QRadioButton *ascii_radio = new QRadioButton("ASCII");
    QRadioButton *hex_radio = new QRadioButton("HEX");
    RadioGroup->addButton(ascii_radio, 0);
    RadioGroup->addButton(hex_radio, 1);
    ascii_radio->setChecked(true);

    //单选框的水平布局
    QHBoxLayout *hLayout_4 = new QHBoxLayout();
    hLayout_4->addWidget(format_label);
    hLayout_4->addWidget(ascii_radio);
    hLayout_4->addWidget(hex_radio);
    hLayout_4->setSpacing(10);
    hLayout_4->setContentsMargins(0,0,10,10);

    //创建主题名输入框
    QTextEdit * topic_textedit = new QTextEdit();

    //创建报文标识符输入框
    QLabel * pack_id_label = new QLabel("Packet Identifier:");
    QLineEdit * pack_id_lineedit = new QLineEdit();

    //报文标识符的水平布局
    QHBoxLayout *hLayout_5 = new QHBoxLayout();
    hLayout_5->addWidget(pack_id_label);
    hLayout_5->addWidget(pack_id_lineedit);
    hLayout_5->setSpacing(10);
    hLayout_5->setContentsMargins(0,0,10,10);

    //生成按钮
    QPushButton * generate_button = new QPushButton("生成");
    connect(generate_button, SIGNAL(clicked()), this, SLOT(slots_generate_button_clicked()));

    //指令输出框
    QTextEdit * cmd_textedit = new QTextEdit();

    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->addLayout(hLayout_1);
    vLayout->addLayout(hLayout_2);
    vLayout->addLayout(hLayout_3);
    vLayout->addLayout(hLayout_4);
    vLayout->addWidget(topic_textedit);
    vLayout->addLayout(hLayout_5);
    vLayout->addWidget(generate_button);
    vLayout->addWidget(cmd_textedit);

    widget->setLayout(vLayout);
}

//成生按钮的槽
void PublishMessage::slots_generate_button_clicked(void)
{

}
