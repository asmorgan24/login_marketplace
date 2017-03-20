#include <QtGamepad/QtGamepad>

#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "keyboard.h"
#include "pugixml.hpp"
#include "InputConfig.h"
#include <thread>
#include "devicepoller.h"

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

    im = InputManager::getInstance();
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


    DevicePoller *devicePoller = new DevicePoller();
    devicePoller->moveToThread(&pollThread);
    connect (devicePoller,&DevicePoller::keyPressed,this, &LoginWindow::handleInput);
    connect (this, &LoginWindow::poll, devicePoller, &DevicePoller::doin);
    connect (&pollThread, &QThread::finished, devicePoller, &QObject::deleteLater);
    connect (&pollThread, &QThread::started, devicePoller, &DevicePoller::doin);


    emit poll();
    pollThread.start();


}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::handleInput(QVector<std::string> inputs) {
    for(QVector<string>::iterator it = inputs.begin(); it!=inputs.end(); ++it) {
        if(*it == "up") {
            std::cout << "we got in here ooh yeah" << std::endl;
        }
        else if (*it == "down") {
            std::cout << "we got in here ooh yeah" << std::endl;
        }
        else if (*it == "left") {
            std::cout << "we got in here ooh yeah" << std::endl;
        }
        else if (*it == "right") {
            std::cout << "we got in here ooh yeah" << std::endl;
        }
        else if (*it == "a") {
            std::cout << "we got in here ooh yeah" << std::endl;
        }

    }


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
