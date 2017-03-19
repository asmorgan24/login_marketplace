#include "keyboardInputController.h"
#include "loginwindow.h"
#include "iostream"


InputController::InputController(Keyboard *k) : keyboard(k)
{

}

void InputController::keyPressEvent( QKeyEvent* event ) {
  switch ( event->key() ) {
    case Qt::Key_W:
        keyboard->up();
        std::cout << "hit up" <<std::endl;
        break;
    case Qt::Key_X:
        keyboard->down();
        break;
    case Qt::Key_A:
        keyboard->left();
        break;
    case Qt::Key_D:
        keyboard->right();
        break;
    case Qt::Key_S:
        keyboard->select();
        break;
    default:
        event->ignore();
        break;
    }
}

void InputController::anything() {
    keyboard->down();
    keyboard->right();
    keyboard->select();
    keyboard->down();
    keyboard->select();
    keyboard->up();
    keyboard->select();
    keyboard->left();
    keyboard->left();
    keyboard->select();
}


