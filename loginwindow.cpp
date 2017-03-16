#include <QtGamepad/QtGamepad>

#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "keyboard.h"
#include "pugixml.hpp"
#include "InputConfig.h"
#include <thread>

#include <iostream>
using namespace std;

void LoginWindow::poll() {
    SDL_Event event;
    std::vector<std::string> data;
    while(SDL_PollEvent(&event))
    {
        std::cout << "got in here" <<std::endl;
        switch(event.type)
        {
            case SDL_JOYHATMOTION:
            case SDL_JOYBUTTONDOWN:
            case SDL_JOYBUTTONUP:
            case SDL_KEYDOWN:
            case SDL_KEYUP:
            case SDL_JOYAXISMOTION:
            case SDL_TEXTINPUT:
            case SDL_TEXTEDITING:
            case SDL_JOYDEVICEADDED:
            case SDL_JOYDEVICEREMOVED:
                data = InputManager::getInstance()->parseEvent(event);
                break;
            //Save that shit into a vector, then call the handleInput Function
        }
        handleInput(data);
    }
}

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



    //im->init();
    //ic->anything();



}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::handleInput(std::vector<std::string> inputs) {


    for(std::vector<string>::iterator it = inputs.begin(); it!=inputs.end(); ++it) {
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
