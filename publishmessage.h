#ifndef PUBLISHMESSAGE_H
#define PUBLISHMESSAGE_H

#include <QComboBox>
#include <QButtonGroup>
#include <QTextEdit>
#include "controlmessage.h"

class PublishMessage : public ControlMessage
{
    Q_OBJECT

public:
    PublishMessage(QWidget *widget);

    enum e_type type = PUBLISH;
    quint8 DUP;
    quint8 QoS;
    quint8 RETAIN;

    quint16 topic_len;
    QList<quint8> topic_name;
    quint16 pack_id;
    QList<quint8> Payload;

    void Generate_Message(void);

    void Ui_Init(QWidget *widget);

private slots:
    void slots_generate_button_clicked(void);

private:
    QComboBox * dup_combobox;
    QComboBox * qos_combobox;
    QComboBox * retain_combobox;
    QButtonGroup * topic_RadioGroup;
    QButtonGroup * payload_RadioGroup;
    QTextEdit * topic_textedit;
    QLineEdit * pack_id_lineedit;
    QTextEdit * payload_textedit;
    QTextEdit * cmd_textedit;
};

#endif // PUBLISHMESSAGE_H
