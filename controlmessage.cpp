
#include <QDebug>
#include "controlmessage.h"

ControlMessage::ControlMessage()
{
}


QList<quint8> ControlMessage::ComputeRemainingLength(quint32 num)
{
    quint32 x = num;
    quint8 encodedByte = 0;
    QList<quint8> length;

    do
    {
        encodedByte = x % 128;
        x = x / 128;
        if( x > 0 )
            encodedByte |= 0x80;
        length.append(encodedByte);
    }
    while( x > 0 );

    return length;
}
