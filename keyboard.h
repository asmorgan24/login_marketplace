#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QWidget>
#include <qwidget.h>
#include <QPushButton>

class Keyboard : public QWidget
{
    Q_OBJECT

public:
    explicit Keyboard(QWidget *parent = Q_NULLPTR);
    void up();
    void down();
    void left();
    void right();
    void select();


private:
    QVector <QPushButton*> buttonVec;
    QVector <int> rowLengths;
    QPalette white;
    QPalette blue;
    int position = 0;
    int getRow() const;

public slots:
    void showKeyboard();
    void hideKeyboard();
    bool keyboardVisible() const;

signals:
    void specialKeyClicked(int key);
    void keyClicked(const QString &text);

private slots:
    void buttonClicked(int key);
};

#endif
