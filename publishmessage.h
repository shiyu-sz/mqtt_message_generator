#ifndef PUBLISHMESSAGE_H
#define PUBLISHMESSAGE_H

#include <QtWidgets>
#include "controlmessage.h"

class PublishMessage : public ControlMessage
{
    Q_OBJECT

public:
    PublishMessage(QWidget *parent = 0);

    QList<quint8> generateMessage(void);
    void uiInit(QWidget *widget);
    void setDup(quint8 value);
    void setQos(quint8 value);
    void setRetain(quint8 value);
    void setTopicName(QString value);
    void setTopicName(QList<quint8> value);
    void setPackId(quint16 value);
    void setPayload(QString value);
    void setPayload(QList<quint8> value);


private slots:
    void slots_generate_button_clicked(void);
    void slots_generate_cpoy_button_clicked(void);

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

    const enum e_type type = PUBLISH;
    quint8 DUP;
    quint8 QoS;
    quint8 RETAIN;
    QList<quint8> topic_name;
    quint16 pack_id;
    QList<quint8> Payload;
};

#endif // PUBLISHMESSAGE_H
