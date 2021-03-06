#include "controllogic.h"
#include <string>
#include <iostream>
#include <sstream>
#include <QDebug>
#include <QProcess>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

ControlLogic::ControlLogic(QObject *parent) : QObject(parent)
{

}

ControlLogic::~ControlLogic()
{

}

QString ControlLogic::checkStatus(){
    qDebug("Checking status...");
    return "return from checkStatus";
}

QString ControlLogic::getNodeValue(){
    qDebug("Invoking getNodeValue");
    return "node value";
}

int ControlLogic::turnOn(QString target){
    qDebug("turnOn");

    std::string cmdTarget = target.toUtf8().constData();

    std::string cmd = "ods (" + cmdTarget + ") 1\r\n";

    char *portname = "/dev/ttymxc0";

    int fd = open (portname, O_RDWR | O_NOCTTY | O_SYNC);

    if (fd < 0)
    {
        qDebug("error opening port.\n");
        return -1;
    }

    set_interface_attribs (fd, B9600, 0);  // set speed to 9600 bps, 8n1 (no parity)
    set_blocking (fd, 0);                // set no blocking

    const void * a = cmd.c_str();

    write (fd, a, 13);           // send 7 character greeting

    usleep ((7 + 25) * 100);             // sleep enough to transmit the 7 plus
                                         // receive 25:  approx 100 uS per char transmit
    close(fd);
}


int ControlLogic::turnOff(QString target){
    qDebug("turnOff");

    std::string cmdTarget = target.toUtf8().constData();

    std::string cmd = "ods (" + cmdTarget + ") 0\r\n";

    char *portname = "/dev/ttymxc0";

    int fd = open (portname, O_RDWR | O_NOCTTY | O_SYNC);

    if (fd < 0)
    {
        qDebug("error opening port.\n");
        return -1;
    }

    set_interface_attribs (fd, B9600, 0);  // set speed to 9600 bps, 8n1 (no parity)
    set_blocking (fd, 0);                // set no blocking

    const void * a = cmd.c_str();

    write (fd, a, 13);           // send 7 character greeting

    usleep ((7 + 25) * 100);             // sleep enough to transmit the 7 plus
                                         // receive 25:  approx 100 uS per char transmit
    close(fd);

}


int ControlLogic::set_interface_attribs (int fd, int speed, int parity){
    struct termios tty;
    memset (&tty, 0, sizeof tty);
    if (tcgetattr (fd, &tty) != 0)
    {
        qDebug("error from tcgetattr.\n");
        return -1;
    }

    cfsetospeed (&tty, speed);
    cfsetispeed (&tty, speed);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
    // disable IGNBRK for mismatched speed tests; otherwise receive break
    // as \000 chars
    tty.c_iflag &= ~IGNBRK;         // disable break processing
    tty.c_lflag = 0;                // no signaling chars, no echo,
                                    // no canonical processing
    tty.c_oflag = 0;                // no remapping, no delays
    tty.c_cc[VMIN]  = 0;            // read doesn't block
    tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

    tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                    // enable reading
    tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
    tty.c_cflag |= parity;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if (tcsetattr (fd, TCSANOW, &tty) != 0)
    {
        qDebug("error from tcsetattr.\n");
        return -1;
    }
    return 0;
}

void ControlLogic::set_blocking (int fd, int should_block){
    struct termios tty;
    memset (&tty, 0, sizeof tty);
    if (tcgetattr (fd, &tty) != 0)
    {
        qDebug("error from tggetattr.\n");
        return;
    }

    tty.c_cc[VMIN]  = should_block ? 1 : 0;
    tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

    if (tcsetattr (fd, TCSANOW, &tty) != 0){
        qDebug("error setting term attributes.\n");
        return;
    }
}
