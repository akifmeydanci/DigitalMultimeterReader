#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QtSerialPort/QSerialPort>
#include <QTime>
#include <QFile>
#include <QTextStream>

QSerialPort *serial;            // Serial Port sınıfından serial nesnesi oluşturuyoruz.
QString filename="Data.csv";    // Serial porttan okunan verilerin aktarıldığı dosya oluşturuluyor.
QFile file( filename );

int nMilliseconds = 0;  // Başlangıçtan itibaren kaç mili sn geçtiğini tutacak olan integer oluşturuluyor.
float nSeconds = 0; //Ekranda geçen saniye zamanı göstermek için

QString str ;   // Seriport tan alınan verinin tutulacağı string

QTime myTimer;  // time sınıfından başlangıçtan itibaren süreyi takip etmek için nesne oluşturuluor.

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myTimer.start();    //zamanlayıcı başlatılıyor.

    //Serial Port Ayarları yapılıyor..
    serial = new QSerialPort(this);
    serial->setPortName("COM4");
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    serial->open(QIODevice::ReadWrite); //Seri Port açılıyor

    //Seri Port Signal and Slotu bağlanıyor.
    connect(serial,SIGNAL(readyRead()),this,SLOT(SerialReceived()));

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
    //Okuma alanında veri olduğu sürece str verisi dolduruluyor.
    while(serial->canReadLine())
    {
    str.append(serial->readAll());
    }
    //Zamanlayıcı başlatıldığından itibaren geçen süre hesaplanıyor.
    nMilliseconds = myTimer.elapsed();
    nSeconds = nMilliseconds/1000;
    QString s = QString::number(nMilliseconds); //Süre string e çeviriliyor
     QString sn = QString::number(nSeconds); //Süre ekranda gösterilmek için  saniyeye cevirilyor.
    //Alınan değer ekranda gösteriliyor
    ui->label->setText(str);
    //ui->textBrowser->setText(str);

    //Dosyaya yazma işlemleri yapılıyor..
    if(!str.isEmpty())  //serial received fonksiyonu çalıştığı halde str boşsa işlem yapma.
        {
        //Boşluk ve new tab,endline temizleniyor..
        str = str.simplified();
        str = str.remove("\n");
        str = str.remove("\r");

        // csv dosyasına alınan veri işleniyor..
        QTextStream stream( &file );

        // Geçen zaman; No ; Vdd ; Vout ; Idd \n
        stream << s << ";"<< str << "\n" ;

    }

    str.clear();    // str stringi yeni değer alması için temizleniyor.

    ui->label_4->setText(sn);
}
