#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

#include "QKeyEvent"

#include "keyboard.h"


class InputController
{

public:
    explicit InputController(Keyboard *k);
    void anything();

private:
    Keyboard *keyboard;

    void keyPressEvent( QKeyEvent* event );
};

#endif // INPUTCONTROLLER_H
