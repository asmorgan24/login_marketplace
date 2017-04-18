#include <QtGamepad/QtGamepad>

#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "keyboard.h"
#include "pugixml.hpp"
#include "InputConfig.h"
#include <thread>
#include "devicepoller.h"
#include "vectortypedef.h"

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
 //   QMainWindow::showMaximized();


    DevicePoller *devicePoller = new DevicePoller();
    devicePoller->moveToThread(&pollThread);

    qRegisterMetaType<StringArray>("StringArray");

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

void LoginWindow::handleInput(StringArray inputs) {
    if (inputs.size() != 1) {
        return;
    }
    for(std::vector<std::string>::iterator it = inputs.begin(); it!=inputs.end(); ++it) {
        if(*it == "up") {
            keyb->up();
            std::cout << "UP" << std::endl;
        }
        else if (*it == "down") {
            keyb->down();
            std::cout << "DOWN" << std::endl;
        }
        else if (*it == "left") {
            keyb->left();
            std::cout << "LEFT" << std::endl;
        }
        else if (*it == "right") {
            keyb->right();
            std::cout << "RIGHT" << std::endl;
        }
        else if (*it == "a") {
            keyb->select();
            std::cout << "SELECT" << std::endl;
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
        //TODO: do the processing here to see if we should call anything good.
        std::system("~/workspace/EmulationStation-Marketplace/emulationstation");
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
