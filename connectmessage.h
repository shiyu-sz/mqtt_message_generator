#ifndef CONNECTMESSAGE_H
#define CONNECTMESSAGE_H

#include "controlmessage.h"
#include <QtWidgets>

class ConnectMessage : public ControlMessage
{
public:
    ConnectMessage(QWidget *parent);

    QList<quint8> generateMessage(void);
    void uiInit(QWidget *widget);

private slots:

private:
    QComboBox *level_combobox;

    const enum e_type type = CONNECT;
    QList<quint8> protocol_name;
    quint8 level;
    qint8 connect_flag;
    quint16 keep_alive;
    QList<quint8> client_id;
    QList<quint8> will_topic;
    QList<quint8> will_message;
    QList<quint8> user_name;
    QList<quint8> password;
};

#endif // CONNECTMESSAGE_H
