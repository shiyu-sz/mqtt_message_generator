#ifndef PUBLISHMESSAGE_H
#define PUBLISHMESSAGE_H

#include "controlmessage.h"

class PublishMessage : public ControlMessage
{
public:
    PublishMessage(QWidget *widget);

    enum e_type type = PUBLISH;
    quint8 DUP;
    quint8 QoS;
    quint8 RETAIN;

    quint16 topic_len;
    QList<quint8> topic_name;
    quint16 pack_id;

    void Generate_Message(void);

    void Ui_Init(QWidget *widget);

slots:
    void slots_generate_button_clicked(void);
};

#endif // PUBLISHMESSAGE_H
