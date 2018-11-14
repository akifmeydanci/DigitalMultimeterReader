
#include "mySerialPort.h"

mySerialPort::mySerialPort(QString str) {
	COMPortName = str;
	this->setPortName(str);
    this->setBaudRate(QSerialPort::Baud9600);
    this->setDataBits(QSerialPort::Data8);
    this->setParity(QSerialPort::NoParity);
    this->setStopBits(QSerialPort::OneStop);
    this->setFlowControl(QSerialPort::NoFlowControl);
    portIsUsed = false;
}

mySerialPort::mySerialPort() {
	this->setPortName("COM56");
    this->setBaudRate(QSerialPort::Baud9600);
    this->setDataBits(QSerialPort::Data8);
    this->setParity(QSerialPort::NoParity);
    this->setStopBits(QSerialPort::OneStop);
    this->setFlowControl(QSerialPort::NoFlowControl);
    COMPortName = "COM56";
    portIsUsed = false;
}

void mySerialPort::updatePortName(QString str) {
	this->setPortName(str);
}

QString mySerialPort::getSerialData() {
    QString str;

    str.append(this->readAll());

	return str;
}

bool mySerialPort::isUsed() {
	return portIsUsed;
}

void mySerialPort::setUsedFlag(bool state) {
	portIsUsed = state;
}
