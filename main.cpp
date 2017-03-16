#include "loginwindow.h"
#include <QApplication>
#include <thread>
#include <iostream>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow w;
    w.show();
    return a.exec();
}
