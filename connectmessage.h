#ifndef CONNECTMESSAGE_H
#define CONNECTMESSAGE_H

#include "controlmessage.h"

class ConnectMessage : public ControlMessage
{
public:
    ConnectMessage();

    quint8 type;

};

#endif // CONNECTMESSAGE_H
