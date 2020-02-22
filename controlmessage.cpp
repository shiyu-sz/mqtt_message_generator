
#include <QDebug>
#include "controlmessage.h"

ControlMessage::ControlMessage()
{
    RemainingLength.clear();
    All_Byte.clear();
}


void ControlMessage::Compute_Remaining_Length(quint32 num)
{
    quint32 x = num;
    quint8 encodedByte = 0;

    do
    {
        encodedByte = x % 128;
        x = x / 128;
        if( x > 0 )
            encodedByte |= 0x80;
        RemainingLength.append(encodedByte);
    }
    while( x > 0 );
}
