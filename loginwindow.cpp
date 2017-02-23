#include <QtGamepad/QtGamepad>

#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "keyboard.h"

#include <iostream>
using namespace std;



LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    keyb = new Keyboard();

    connect(keyb, &Keyboard::keyClicked,this, &LoginWindow::charPressed);
    connect(keyb, &Keyboard::specialKeyClicked,this, &LoginWindow::specialPressed);

    im->getInstance();
    im->init();



    ui->keyboard = keyb;
    ui->keyboard->show();
    ui->mainLayout->addWidget(keyb,0,Qt::AlignCenter);

    username = ui->lineEdit_2;
    password = ui->lineEdit;
    cursor = new QCursor();


    palBlue= palette();
    palWhite = palette();
    palBlue.setColor(QPalette::Background, Qt::blue);
    palWhite.setColor(QPalette::Background, Qt::white);
    username->setPalette(palBlue);


    QMainWindow::showFullScreen();


    //im->init();
    //ic->anything();
}

LoginWindow::~LoginWindow()
{
    delete ui;
}


void LoginWindow::charPressed(const QString &text) {
    if(!enterPressed) {
        username->setText(username->text()+text);
    }
    else if (enterPressed) {
        password->setText(password->text()+text);
    }
}


void LoginWindow::specialPressed (int key) {

    if (key == Qt::Key_Enter && !enterPressed){
        enterPressed = true;
        username->setDisabled(true);
        username->setPalette(palWhite);
        password->setPalette(palBlue);
    }
    else if (key == Qt::Key_Enter && enterPressed) {
        password->setPalette(palWhite);
        password->setDisabled(true);
    }

    if (key == Qt::Key_Backspace && !enterPressed){
        QString text = username->text();
        text.chop(1);
        username->setText(text);
    }
    else if (key == Qt::Key_Backspace && enterPressed) {
        QString text = password->text();
        text.chop(1);
        password->setText(text);
    }
}
