#ifndef CONTROLLOGIC_H
#define CONTROLLOGIC_H

#include <QObject>

class ControlLogic : public QObject
{
    Q_OBJECT
public:
    explicit ControlLogic(QObject *parent = 0);
    ~ControlLogic();

signals:

public slots:
    QString checkStatus();
    QString getNodeValue();
    int turnOn(QString target);
    int turnOff(QString target);
    void set_blocking (int fd, int should_block);
    int set_interface_attribs (int fd, int speed, int parity);
};

#endif // CONTROLLOGIC_H
