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

    //keep alive
    QLabel *keep_label = new QLabel("Keep Alive(uint s):");
    QLineEdit *keep_lineedit = new QLineEdit();
    keep_lineedit->setText("1000");

    //keep alive水平布局
    QHBoxLayout *hLayout_3 = new QHBoxLayout();
    hLayout_3->addWidget(keep_label);
    hLayout_3->addWidget(keep_lineedit);
    hLayout_3->setSpacing(10);
    hLayout_3->setContentsMargins(0,0,10,10);

    //ClientId格式单选框
    QLabel * ClientId_format_label = new QLabel("ClientId Format:");
    QButtonGroup *ClientId_RadioGroup = new QButtonGroup();
    QRadioButton *ClientId_ascii_radio = new QRadioButton("ASCII");
    QRadioButton *ClientId_hex_radio = new QRadioButton("HEX");
    ClientId_RadioGroup->addButton(ClientId_ascii_radio, 0);
    ClientId_RadioGroup->addButton(ClientId_hex_radio, 1);
    ClientId_ascii_radio->setChecked(true);

    //单选框的水平布局
    QHBoxLayout *hLayout_4 = new QHBoxLayout();
    hLayout_4->addWidget(ClientId_format_label);
    hLayout_4->addWidget(ClientId_ascii_radio);
    hLayout_4->addWidget(ClientId_hex_radio);
    hLayout_4->setSpacing(10);
    hLayout_4->setContentsMargins(0,0,10,10);

    //ClientId输入框
    QTextEdit *ClientId_textedit = new QTextEdit();

    //ClientId垂直布局
    QVBoxLayout *vLayout_2 = new QVBoxLayout();
    vLayout_2->addLayout(hLayout_4);
    vLayout_2->addWidget(ClientId_textedit);

    //ClientId盒子
    QGroupBox *ClientId_groupbox = new QGroupBox("ClientId", this);
    ClientId_groupbox->setLayout(vLayout_2);

    //Will Topic格式单选框
    QLabel * WillTopic_format_label = new QLabel("Will Topic Format:");
    QButtonGroup *WillTopic_RadioGroup = new QButtonGroup();
    QRadioButton *WillTopic_ascii_radio = new QRadioButton("ASCII");
    QRadioButton *WillTopic_hex_radio = new QRadioButton("HEX");
    WillTopic_RadioGroup->addButton(WillTopic_ascii_radio, 0);
    WillTopic_RadioGroup->addButton(WillTopic_hex_radio, 1);
    WillTopic_ascii_radio->setChecked(true);

    //单选框的水平布局
    QHBoxLayout *hLayout_5 = new QHBoxLayout();
    hLayout_5->addWidget(WillTopic_format_label);
    hLayout_5->addWidget(WillTopic_ascii_radio);
    hLayout_5->addWidget(WillTopic_hex_radio);
    hLayout_5->setSpacing(10);
    hLayout_5->setContentsMargins(0,0,10,10);

    //WillTopic输入框
    QTextEdit *WillTopic_textedit = new QTextEdit();

    //WillTopic垂直布局
    QVBoxLayout *vLayout_3 = new QVBoxLayout();
    vLayout_3->addLayout(hLayout_5);
    vLayout_3->addWidget(WillTopic_textedit);

    //WillTopic盒子
    QGroupBox *WillTopic_groupbox = new QGroupBox("Will Topic", this);
    WillTopic_groupbox->setLayout(vLayout_3);

    //Will Message格式单选框
    QLabel * WillMessage_format_label = new QLabel("Will Message Format:");
    QButtonGroup *WillMessage_RadioGroup = new QButtonGroup();
    QRadioButton *WillMessage_ascii_radio = new QRadioButton("ASCII");
    QRadioButton *WillMessage_hex_radio = new QRadioButton("HEX");
    WillMessage_RadioGroup->addButton(WillMessage_ascii_radio, 0);
    WillMessage_RadioGroup->addButton(WillMessage_hex_radio, 1);
    WillMessage_ascii_radio->setChecked(true);

    //单选框的水平布局
    QHBoxLayout *hLayout_6 = new QHBoxLayout();
    hLayout_6->addWidget(WillMessage_format_label);
    hLayout_6->addWidget(WillMessage_ascii_radio);
    hLayout_6->addWidget(WillMessage_hex_radio);
    hLayout_6->setSpacing(10);
    hLayout_6->setContentsMargins(0,0,10,10);

    //WillTopic输入框
    QTextEdit *WillMessage_textedit = new QTextEdit();

    //WillTopic垂直布局
    QVBoxLayout *vLayout_4 = new QVBoxLayout();
    vLayout_4->addLayout(hLayout_6);
    vLayout_4->addWidget(WillMessage_textedit);

    //WillTopic盒子
    QGroupBox *WillMessage_groupbox = new QGroupBox("Will Message", this);
    WillMessage_groupbox->setLayout(vLayout_4);

    //User Name格式单选框
    QLabel * UserName_format_label = new QLabel("User Name Format:");
    QButtonGroup *UserName_RadioGroup = new QButtonGroup();
    QRadioButton *UserName_ascii_radio = new QRadioButton("ASCII");
    QRadioButton *UserName_hex_radio = new QRadioButton("HEX");
    UserName_RadioGroup->addButton(UserName_ascii_radio, 0);
    UserName_RadioGroup->addButton(UserName_hex_radio, 1);
    UserName_ascii_radio->setChecked(true);

    //单选框的水平布局
    QHBoxLayout *hLayout_7 = new QHBoxLayout();
    hLayout_7->addWidget(UserName_format_label);
    hLayout_7->addWidget(UserName_ascii_radio);
    hLayout_7->addWidget(UserName_hex_radio);
    hLayout_7->setSpacing(10);
    hLayout_7->setContentsMargins(0,0,10,10);

    //User Name输入框
    QTextEdit *UserName_textedit = new QTextEdit();

    //User Name垂直布局
    QVBoxLayout *vLayout_5 = new QVBoxLayout();
    vLayout_5->addLayout(hLayout_7);
    vLayout_5->addWidget(UserName_textedit);

    //User Name盒子
    QGroupBox *UserName_groupbox = new QGroupBox("User Name", this);
    UserName_groupbox->setLayout(vLayout_5);

    //Password格式单选框
    QLabel * Password_format_label = new QLabel("Password Format:");
    QButtonGroup *Password_RadioGroup = new QButtonGroup();
    QRadioButton *Password_ascii_radio = new QRadioButton("ASCII");
    QRadioButton *Password_hex_radio = new QRadioButton("HEX");
    Password_RadioGroup->addButton(Password_ascii_radio, 0);
    Password_RadioGroup->addButton(Password_hex_radio, 1);
    Password_ascii_radio->setChecked(true);

    //单选框的水平布局
    QHBoxLayout *hLayout_8 = new QHBoxLayout();
    hLayout_8->addWidget(Password_format_label);
    hLayout_8->addWidget(Password_ascii_radio);
    hLayout_8->addWidget(Password_hex_radio);
    hLayout_8->setSpacing(10);
    hLayout_8->setContentsMargins(0,0,10,10);

    //Password输入框
    QTextEdit *Password_textedit = new QTextEdit();

    //Password垂直布局
    QVBoxLayout *vLayout_6 = new QVBoxLayout();
    vLayout_6->addLayout(hLayout_8);
    vLayout_6->addWidget(Password_textedit);

    //Password盒子
    QGroupBox *Password_groupbox = new QGroupBox("Password", this);
    Password_groupbox->setLayout(vLayout_6);

    //生成按钮
    QPushButton * generate_button = new QPushButton("生成");
    connect(generate_button, SIGNAL(clicked()), this, SLOT(slots_generate_button_clicked()));
    //生成并复制按钮
    QPushButton * generate_cpoy_button = new QPushButton("生成并复制");
    connect(generate_cpoy_button, SIGNAL(clicked()), this, SLOT(slots_generate_cpoy_button_clicked()));
    //单选框的水平布局
    QHBoxLayout *hLayout_9 = new QHBoxLayout();
    hLayout_9->addWidget(generate_button);
    hLayout_9->addWidget(generate_cpoy_button);

    //指令输出框
    QTextEdit *cmd_textedit = new QTextEdit();

    //左侧控件垂直布局
    QVBoxLayout *vLayout_l = new QVBoxLayout();
    vLayout_l->addLayout(hLayout_1);
    vLayout_l->addWidget(connect_flag_groupbox);
    vLayout_l->addLayout(hLayout_3);
    vLayout_l->addLayout(hLayout_9);
    vLayout_l->addWidget(cmd_textedit);

    //右侧控件垂直布局
    QVBoxLayout *vLayout_h = new QVBoxLayout();
    vLayout_h->addWidget(ClientId_groupbox);
    vLayout_h->addWidget(WillTopic_groupbox);
    vLayout_h->addWidget(WillMessage_groupbox);
    vLayout_h->addWidget(UserName_groupbox);
    vLayout_h->addWidget(Password_groupbox);

    //总的水平布局
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addLayout(vLayout_l);
    hLayout->addLayout(vLayout_h);
    hLayout->setSpacing(10);
    hLayout->setContentsMargins(10,10,10,10);

    widget->setLayout(hLayout);
}
