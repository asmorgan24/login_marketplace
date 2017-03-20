#ifndef DEVICEPOLLER_H
#define DEVICEPOLLER_H

#include <QObject>
#include "QThread"
#include <QVector>

class DevicePoller : public QObject
{
    Q_OBJECT
public:
    explicit DevicePoller(QObject *parent = 0);

private:


signals:
   void keyPressed(QVector<std::string> keys);

public slots:
   void doin();
};

#endif // DEVICEPOLLER_H
