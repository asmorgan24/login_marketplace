#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QDesktopWidget>
#include <iostream>
using namespace std;

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

QMainWindow::showFullScreen();


}

LoginWindow::~LoginWindow()
{
    delete ui;
}
