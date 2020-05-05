
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

PublishMessage::PublishMessage(QWidget *parent)
{

}

/**
 * @brief PublishMessage::setDup
 * @param value
 */
void PublishMessage::setDup(quint8 value)
{
    DUP = value;
}

/**
 * @brief PublishMessage::setQos
 * @param value
 */
void PublishMessage::setQos(quint8 value)
{
    QoS = value;
}

/**
 * @brief PublishMessage::setRetain
 * @param value
 */
void PublishMessage::setRetain(quint8 value)
{
    RETAIN = value;
}

/**
 * @brief PublishMessage::setTopicName
 * @param value
 */
void PublishMessage::setTopicName(QString value)
{
    topic_name.clear();

    char*  ch;
    QByteArray ba = value.toLatin1(); // must
    ch=ba.data();

    for(int i=0; i<ba.length(); i++)
        topic_name.append((quint8)ch[i]);
}

/**
 * @brief PublishMessage::setTopicName
 * @param value
 */
void PublishMessage::setTopicName(QList<quint8> value)
{
    topic_name.clear();
    topic_name = value;
}

/**
 * @brief PublishMessage::setPackId
 * @param value
 */
void PublishMessage::setPackId(quint16 value)
{
    pack_id = value;
}

/**
 * @brief PublishMessage::setPayload
 * @param value
 */
void PublishMessage::setPayload(QString value)
{
    Payload.clear();

    char*  ch;
    QByteArray ba = value.toLatin1(); // must
    ch=ba.data();

    for(int i=0; i<ba.length(); i++)
        Payload.append((quint8)ch[i]);
}

/**
 * @brief PublishMessage::setPayload
 * @param value
 */
void PublishMessage::setPayload(QList<quint8> value)
{
    Payload.clear();
    Payload = value;
}

/**
 * @brief PublishMessage::generateMessage 生成报文
 * @return
 */
QList<quint8> PublishMessage::generateMessage(void)
{
    QList<quint8> all_byte;

    //第一个字节
    quint8 head = 0;
    head = (type&0x0f)<<4 | (DUP&0x01)<<3 | (QoS&0x03)<<1 | (RETAIN&0x01);
    all_byte.append(head);

    //剩余长度
    quint32 overlength = 0;
    QList<quint8> len;
    overlength = 2 + topic_name.length() + 2 + Payload.length();
    len = ComputeRemainingLength(overlength);
    all_byte.append(len);

    //主题长度
    all_byte.append(topic_name.length()/256);
    all_byte.append(topic_name.length()%256);

    //主题名
    all_byte.append(topic_name);

    //标识符
    all_byte.append(pack_id/256);
    all_byte.append(pack_id%256);

    //有效载荷
    all_byte.append(Payload);

    return all_byte;
}

/**
 * @brief PublishMessage::uiInit 初始化ui
 * @param widget
 */
void PublishMessage::uiInit(QWidget *widget)
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
    pack_id_lineedit->setText("0");

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

/**
 * @brief PublishMessage::slots_generate_button_clicked ui中的按钮槽
 */
void PublishMessage::slots_generate_button_clicked(void)
{
    setDup(dup_combobox->currentData().toInt());
    setQos(qos_combobox->currentData().toInt());
    setRetain(retain_combobox->currentData().toInt());

    //如果topic是ascii
    QString topic = topic_textedit->toPlainText();
    if( topic_RadioGroup->checkedId() == 0 )
    {
        setTopicName(topic);
    }
    //否则是hex
    else
    {
        QList<quint8> data;
        topic = topic.trimmed();
        QStringList str_list = topic.split(" ");
        foreach (QString s, str_list)
        {
            if(s.isEmpty() == false)
                data.append((quint8)s.toInt(0, 16));
        }
        setTopicName(data);
    }

    //报文标识符
    setPackId(pack_id_lineedit->text().toInt());

    //如果Payload是ascii
    QString payload = payload_textedit->toPlainText();
    if( payload_RadioGroup->checkedId() == 0 )
    {
        setPayload(payload);
    }
    //否则是hex
    else
    {
        QList<quint8> data;
        payload = payload.trimmed();
        QStringList str_list = payload.split(" ");
        foreach (QString s, str_list)
        {
            if(s.isEmpty() == false)
                data.append((quint8)s.toInt(0, 16));
        }
        setPayload(data);
    }

    QList<quint8> message = generateMessage();

    QString str;
    for(int i=0; i<message.length(); i++ )
    {
        str += QString("%1").arg(message.at(i), 2, 16, QLatin1Char('0')).toUpper();
        str += " ";
    }

    cmd_textedit->clear();
    cmd_textedit->setText(str);
}
