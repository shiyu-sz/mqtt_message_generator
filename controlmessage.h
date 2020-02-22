#ifndef CONTROLMESSAGE_H
#define CONTROLMESSAGE_H

#include <QWidget>
#include <QList>

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

    QList<quint8> RemainingLength;
    void Compute_Remaining_Length(quint32 num);

    QList<quint8> All_Byte;
};

#endif // CONTROLMESSAGE_H
