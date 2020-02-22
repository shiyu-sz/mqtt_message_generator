
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
    overlength = sizeof(topic_len) + topic_name.length() + sizeof(pack_id) + Payload.length();
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

    //有效载荷
    All_Byte.append(Payload);

    qDebug() << "All_Byte = " << All_Byte;
}

void PublishMessage::Ui_Init(QWidget *widget)
{
    //创建dup
    QLabel * dup_label = new QLabel("DUP:");
    dup_combobox = new QComboBox();
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
    qos_combobox = new QComboBox();
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
    retain_combobox = new QComboBox();
    retain_combobox->addItem("0", 0);
    retain_combobox->addItem("1", 1);

    //RETAIN的水平布局
    QHBoxLayout *hLayout_3 = new QHBoxLayout();
    hLayout_3->addWidget(retain_label);
    hLayout_3->addWidget(retain_combobox);
    hLayout_3->setSpacing(10);
    hLayout_3->setContentsMargins(0,0,10,10);

    //创建topic格式单选框
    QLabel * topic_format_label = new QLabel("Topic Name Format:");
    topic_RadioGroup = new QButtonGroup();
    QRadioButton *topic_ascii_radio = new QRadioButton("ASCII");
    QRadioButton *topic_hex_radio = new QRadioButton("HEX");
    topic_RadioGroup->addButton(topic_ascii_radio, 0);
    topic_RadioGroup->addButton(topic_hex_radio, 1);
    topic_ascii_radio->setChecked(true);

    //单选框的水平布局
    QHBoxLayout *hLayout_4 = new QHBoxLayout();
    hLayout_4->addWidget(topic_format_label);
    hLayout_4->addWidget(topic_ascii_radio);
    hLayout_4->addWidget(topic_hex_radio);
    hLayout_4->setSpacing(10);
    hLayout_4->setContentsMargins(0,0,10,10);

    //创建topic输入框
    topic_textedit = new QTextEdit();

    //创建报文标识符输入框
    QLabel * pack_id_label = new QLabel("Packet Identifier:");
    pack_id_lineedit = new QLineEdit();

    //报文标识符的水平布局
    QHBoxLayout *hLayout_5 = new QHBoxLayout();
    hLayout_5->addWidget(pack_id_label);
    hLayout_5->addWidget(pack_id_lineedit);
    hLayout_5->setSpacing(10);
    hLayout_5->setContentsMargins(0,0,10,10);

    //创建Payload格式单选框
    QLabel * payload_format_label = new QLabel("Payload Format:");
    payload_RadioGroup = new QButtonGroup();
    QRadioButton *payload_ascii_radio = new QRadioButton("ASCII");
    QRadioButton *payload_hex_radio = new QRadioButton("HEX");
    payload_RadioGroup->addButton(payload_ascii_radio, 0);
    payload_RadioGroup->addButton(payload_hex_radio, 1);
    payload_ascii_radio->setChecked(true);

    //单选框的水平布局
    QHBoxLayout *hLayout_6 = new QHBoxLayout();
    hLayout_6->addWidget(payload_format_label);
    hLayout_6->addWidget(payload_ascii_radio);
    hLayout_6->addWidget(payload_hex_radio);
    hLayout_6->setSpacing(10);
    hLayout_6->setContentsMargins(0,0,10,10);

    //创建Payload输入框
    payload_textedit = new QTextEdit();

    //生成按钮
    QPushButton * generate_button = new QPushButton("生成");
    connect(generate_button, SIGNAL(clicked()), this, SLOT(slots_generate_button_clicked()));

    //指令输出框
    cmd_textedit = new QTextEdit();

    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->addLayout(hLayout_1);
    vLayout->addLayout(hLayout_2);
    vLayout->addLayout(hLayout_3);
    vLayout->addLayout(hLayout_4);
    vLayout->addWidget(topic_textedit);
    vLayout->addLayout(hLayout_5);
    vLayout->addLayout(hLayout_6);
    vLayout->addWidget(payload_textedit);
    vLayout->addWidget(generate_button);
    vLayout->addWidget(cmd_textedit);

    widget->setLayout(vLayout);
}

//成生按钮的槽
void PublishMessage::slots_generate_button_clicked(void)
{
    //先将成员变量初始化

    DUP = dup_combobox->currentData().toInt();
    QoS = qos_combobox->currentData().toInt();
    RETAIN = retain_combobox->currentData().toInt();

    //如果topic是ascii
    if( topic_RadioGroup->checkedId() == 0 )
    {
        QString topic = topic_textedit->toPlainText();
        topic_len = topic.length();

        char*  ch;
        QByteArray ba = topic.toLatin1(); // must
        ch=ba.data();

        for(int i=0; i<ba.length(); i++)
            topic_name.append((quint8)ch[i]);
    }
    //否则是hex
    else
    {

    }

    //报文标识符
    pack_id = pack_id_lineedit->text().toInt();

    //如果Payload是ascii
    if( payload_RadioGroup->checkedId() == 0 )
    {
        QString payload = payload_textedit->toPlainText();

        char*  ch;
        QByteArray ba = payload.toLatin1(); // must
        ch=ba.data();

        for(int i=0; i<ba.length(); i++)
            Payload.append((quint8)ch[i]);
    }
    //否则是hex
    else
    {

    }

    Generate_Message();

    QString str;
    for(int i=0; i<All_Byte.length(); i++ )
    {
        str += QString::number(All_Byte.at(i), 16);
        str += " ";
    }

    cmd_textedit->setText(str);
}
