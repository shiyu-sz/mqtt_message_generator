#ifndef SUBSCRIBE_H
#define SUBSCRIBE_H

#include "controlmessage.h"

class Subscribe : public ControlMessage
{
    Q_OBJECT

public:
    Subscribe(QWidget *parent = 0);
};

#endif // SUBSCRIBE_H
