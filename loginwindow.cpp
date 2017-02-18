#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "keyboard.h"


LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    Keyboard *keyb = new Keyboard();
    connect(keyb, &Keyboard::keyClicked,this, &LoginWindow::charPressed);
    connect(keyb, &Keyboard::specialKeyClicked,this, &LoginWindow::specialPressed);



    ui->keyboard = keyb;
    ui->keyboard->show();
    ui->mainLayout->addWidget(keyb,0,Qt::AlignCenter);


    QLineEdit *username = ui->lineEdit;
    QLineEdit *password = ui->lineEdit_2;





    QMainWindow::showFullScreen();
}

LoginWindow::~LoginWindow()
{
    delete ui;
}


void LoginWindow::charPressed(const QString &text) {

}


void LoginWindow::specialPressed(int key) {

}
