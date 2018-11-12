
#include <QtSerialPort/QSerialPort>


class mySerialPort : public QSerialPort {
	private:
	QString COMPortName;
	bool	portIsUsed;
	public:
	mySerialPort();
    mySerialPort(QString str);
	updatePortName(QString str);
	QString getSerialData();
	bool isUsed();
	setUsedFlag(bool state);
};



