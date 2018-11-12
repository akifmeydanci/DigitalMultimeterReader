
#include "mySerialPort.h"

mySerialPort::mySerialPort(QString str) {
	COMPortName = str;
	this->setPortName(str);
    this->setBaudRate(QSerialPort::Baud9600);
    this->setDataBits(QSerialPort::Data8);
    this->setParity(QSerialPort::NoParity);
    this->setStopBits(QSerialPort::OneStop);
    this->setFlowControl(QSerialPort::NoFlowControl);
}

mySerialPort::mySerialPort() {
	this->setPortName("COM56");
    this->setBaudRate(QSerialPort::Baud9600);
    this->setDataBits(QSerialPort::Data8);
    this->setParity(QSerialPort::NoParity);
    this->setStopBits(QSerialPort::OneStop);
    this->setFlowControl(QSerialPort::NoFlowControl);	
}

mySerialPort::updatePortName(QString str) {
	this->setPortName(str);
}

QString mySerialPort::getSerialData() {
	QString str;
	  while(this->canReadLine())
    {
    str.append(this->readAll());
    }
	
	return str;
}

bool mySerialPort::isUsed() {
	return portIsUsed;
}

mySerialPort::setUsedFlag(bool state) {
	portIsUsed = state;
}
