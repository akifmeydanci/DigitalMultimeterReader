#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QtSerialPort/QSerialPort>
#include <QTime>
#include <QFile>
#include <QTextStream>
#include "mySerialPort.h"

mySerialPort *serial;            // Serial Port sınıfından serial nesnesi oluşturuyoruz.
QString filename="Data.csv";    // Serial porttan okunan verilerin aktarıldığı dosya oluşturuluyor.
QFile file( filename );

int nMilliseconds = 0;  // Başlangıçtan itibaren kaç mili sn geçtiğini tutacak olan integer oluşturuluyor.
float nSeconds = 0; //Ekranda geçen saniye zamanı göstermek için

int onetimestart=0;
QString received_data;   // Seriport tan alınan verinin tutulacağı string

QTime *myTimer;  // time sınıfından başlangıçtan itibaren süreyi takip etmek için nesne oluşturuluor.

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serial = new mySerialPort();
	myTimer = new QTime();
    myTimer->start();    //zamanlayıcı başlatılıyor.

    // Yazma işlemi için dosya açılıyor.
    file.open(QIODevice::ReadWrite);
}

MainWindow::~MainWindow()
{
    delete ui;
    serial->close();    //Serial Port kapatılıyor..
}

//Serialreceived Fonksiyonu ekleniyor..
void MainWindow::SerialReceived()
{

   received_data = serial->getSerialData();


    //Zamanlayıcı başlatıldığından itibaren geçen süre hesaplanıyor.
    nMilliseconds = myTimer->elapsed();
    nSeconds = nMilliseconds/1000;
    QString s = QString::number(nMilliseconds); //Süre string e çeviriliyor
     QString sn = QString::number(nSeconds); //Süre ekranda gösterilmek için  saniyeye cevirilyor.
    //Alınan değer ekranda gösteriliyor
    ui->label->setText(received_data);
    //ui->textBrowser->setText(received_data);

    //Dosyaya yazma işlemleri yapılıyor..
    if(!received_data.isEmpty())  //serial received fonksiyonu çalıştığı halde received_data boşsa işlem yapma.
        {
        //Boşluk ve new tab,endline temizleniyor...
        received_data = received_data.simplified();
        received_data = received_data.remove("\n");
        received_data = received_data.remove("\r");

        // csv dosyasına alınan veri işleniyor...
        QTextStream stream( &file );

        // Geçen zaman; No ; Vdd ; Vout ; Idd \n
        stream << s << ";"<< received_data << "\n" ;

    }

    received_data.clear();    // received_data stringi yeni değer alması için temizleniyor.

    serial->write("Ok!\n");

    ui->label_4->setText(sn);
}

void MainWindow::on_btnStart_clicked()
{
    if(serial->isUsed() == false) {
		if(serial->open(QIODevice::ReadWrite) == true) {
            serial->setUsedFlag(true);
		}
	}
    else {
        return;
    }

	//Seri Port Signal and Slotu bağlanıyor.
    connect(serial,SIGNAL(readyRead()),this,SLOT(SerialReceived()));
	
}

void MainWindow::on_btnStop_clicked()
{
    if(serial->isUsed() == true) {
		serial->close();    //Serial Port kapatılıyor..
	}
}
