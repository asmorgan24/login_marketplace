#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#include "ui_loginwindow.h"

#include <QMainWindow>
#include "keyboard.h"
#include "inputcontroller.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);

    ~LoginWindow();

private:
    Ui::LoginWindow *ui;
    QLineEdit *username;
    QLineEdit *password;
    QPalette palBlue, palWhite;
    QCursor *cursor;

    Keyboard *keyb;
    InputController *ic;

    bool enterPressed = false;

public slots:
    void charPressed(const QString &text);
    void specialPressed(int key);


};

#endif // LOGINWINDOW_H
