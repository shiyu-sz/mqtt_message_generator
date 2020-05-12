#ifndef CONTROLMESSAGE_H
#define CONTROLMESSAGE_H

#include <QtWidgets>

class ControlMessage : public QWidget
{
public:
    ControlMessage();

    enum e_type
    {
        CONNECT = 1,
        CONNACK,
        PUBLISH,
        PUBACK,
        PUBREC,
        PUBREL,
        PUBCOMP,
        SUBSCRIBE,
        SUBACK,
        UNSUBSCRIBE,
        UNSUBACK,
        PINGREQ,
        PINGRESP,
        DISCONNECT,
    };

    QList<quint8> ComputeRemainingLength(quint32 num);
};

#endif // CONTROLMESSAGE_H
