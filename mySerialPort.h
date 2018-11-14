
#include <QtSerialPort/QSerialPort>


class mySerialPort : public QSerialPort {
	private:
	QString COMPortName;
	bool	portIsUsed;
	public:
	mySerialPort();
    mySerialPort(QString str);
    void updatePortName(QString str);
	QString getSerialData();
	bool isUsed();
    void setUsedFlag(bool state);
};



