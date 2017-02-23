#include "keyboard.h"
#include <iostream>

#include <QGridLayout>
#include <QSignalMapper>
#include <QPushButton>
#include "QDesktopWidget"

#define NEXT_ROW_MARKER 0

struct KeyboardLayoutEntry{
    int key;
    const char *label;
};

KeyboardLayoutEntry keyboardLayout[] = {
    { Qt::Key_1, "1" },
    { Qt::Key_2, "2" },
    { Qt::Key_3, "3" },
    { Qt::Key_4, "4" },
    { Qt::Key_5, "5" },
    { Qt::Key_6, "6" },
    { Qt::Key_7, "7" },
    { Qt::Key_8, "8" },
    { Qt::Key_9, "9" },
    { Qt::Key_0, "0" },
    { Qt::Key_Backspace, "<-" },
    { NEXT_ROW_MARKER, 0 },
    { Qt::Key_Q, "q" },
    { Qt::Key_W, "w" },
    { Qt::Key_E, "e" },
    { Qt::Key_R, "r" },
    { Qt::Key_T, "t" },
    { Qt::Key_Y, "y" },
    { Qt::Key_U, "u" },
    { Qt::Key_I, "i" },
    { Qt::Key_O, "o" },
    { Qt::Key_P, "p" },
    { NEXT_ROW_MARKER, 0 },
    { Qt::Key_A, "a" },
    { Qt::Key_S, "s" },
    { Qt::Key_D, "d" },
    { Qt::Key_F, "f" },
    { Qt::Key_G, "g" },
    { Qt::Key_H, "h" },
    { Qt::Key_J, "j" },
    { Qt::Key_K, "k" },
    { Qt::Key_L, "l" },
    { NEXT_ROW_MARKER, 0 },
    { Qt::Key_Z, "z" },
    { Qt::Key_X, "x" },
    { Qt::Key_C, "c" },
    { Qt::Key_V, "v" },
    { Qt::Key_B, "b" },
    { Qt::Key_N, "n" },
    { Qt::Key_M, "m" },
    { Qt::Key_Enter, "Enter" }
};

const static int layoutSize = (sizeof(keyboardLayout) / sizeof(KeyboardLayoutEntry));

static QString keyToCharacter(int key)
{
    for (int i = 0; i < layoutSize; ++i) {
        if (keyboardLayout[i].key == key)
            return QString::fromLatin1(keyboardLayout[i].label);
    }

    return QString();
}

Keyboard::Keyboard(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::WindowDoesNotAcceptFocus | Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::BypassWindowManagerHint);

    QGridLayout *gridLayout = new QGridLayout(this);
    blue.setColor(QPalette::Background, Qt::blue);
    white.setColor(QPalette::Background, Qt::white);

    QSignalMapper *mapper = new QSignalMapper(this);
    connect(mapper, SIGNAL(mapped(int)), SLOT(buttonClicked(int)));

    int row = 0;
    int column = 0;

    QDesktopWidget desktop;

    for (int i = 0; i < layoutSize; ++i) {
        if (keyboardLayout[i].key == NEXT_ROW_MARKER) {
            row++;
            rowLengths.push_back(column);
            column = 0;
            continue;
        }

        QPushButton *button = new QPushButton;
        button->setFixedWidth(desktop.width()/13);
        button->setFixedHeight(desktop.height()/2/6);
        button->setText(QString::fromLatin1(keyboardLayout[i].label));
        button->setFocusPolicy(Qt::FocusPolicy::NoFocus);

        mapper->setMapping(button, keyboardLayout[i].key);
        connect(button, SIGNAL(clicked()), mapper, SLOT(map()));
        buttonVec.push_back(button);
        gridLayout->addWidget(button, row, column);
        column++;
    }
    buttonVec.at(position)->setPalette(blue);
}

void Keyboard::showKeyboard()
{
    QWidget::show();
}

void Keyboard::hideKeyboard()
{
    QWidget::hide();
}

bool Keyboard::keyboardVisible() const
{
    return QWidget::isVisible();
}


void Keyboard::up(){
    buttonVec.at(position)->setPalette(white);
    position = position-rowLengths.at(getRow()-1);
    if (position < 0) {
        position = 0;
    }
    buttonVec.at(position)->setPalette(blue);

}

void Keyboard::down(){
    buttonVec.at(position)->setPalette(white);
    position = position+rowLengths.at(getRow());
    if (position > buttonVec.length()) {
        position = buttonVec.length();
    }
    buttonVec.at(position)->setPalette(blue);

}

void Keyboard::right(){
    buttonVec.at(position)->setPalette(white);
    position++;
    if (position > buttonVec.length()) {
        position = buttonVec.length();
    }
    buttonVec.at(position)->setPalette(blue);

}

void Keyboard::left(){
    buttonVec.at(position)->setPalette(white);
    position--;
    if (position < 0) {
        position = 0;
    }
    buttonVec.at(position)->setPalette(blue);


}

void Keyboard::select(){

    if (buttonVec.at(position)->text().toStdString() == "Enter" || buttonVec.at(position)->text().toStdString() == "<-") {
        emit specialKeyClicked(keyboardLayout[position+getRow()].key);
    }
    else {
        emit keyClicked(keyToCharacter(keyboardLayout[position+getRow()].key));
    }

}

/**
 * @brief Keyboard::getRow
 * @return zero based index of current row based on position variable
 */
int Keyboard::getRow() const {
    int tmpPosition = position;
    int row = -1;

    for (QVector<int>::const_iterator it = rowLengths.begin(); it != rowLengths.end() && tmpPosition >= 0; ++it) {
        tmpPosition -= *it;
        row++;
    }

    return row >= 0 ? row : 0;
}


void Keyboard::buttonClicked(int key)
{
    if ((key == Qt::Key_Enter) || (key == Qt::Key_Backspace)) {
        emit specialKeyClicked(key);
    }
    else {
        emit keyClicked(keyToCharacter(key));
    }
}

