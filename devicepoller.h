#ifndef DEVICEPOLLER_H
#define DEVICEPOLLER_H

#include <QObject>
#include "QThread"
#include <QVector>
#include "vectortypedef.h"

class DevicePoller : public QObject
{
    Q_OBJECT
public:
    explicit DevicePoller(QObject *parent = 0);

private:


signals:
   void keyPressed(StringArray keys);

public slots:
   void doin();
};

#endif // DEVICEPOLLER_H
