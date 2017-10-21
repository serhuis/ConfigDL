#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QProgressBar>
#include <QDebug>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //status bar
    QLabel *statusLabel = new QLabel(this);

    statusProgBar = new QProgressBar(this);
//    statusProgBar->setTextVisible(false);
    statusProgBar->setFormat("%m%");
///    statusProgBar->setInvertedAppearance(true);
    ui->statusBar->addPermanentWidget(statusLabel);
    ui->statusBar->addPermanentWidget(statusProgBar);



    //timer
    mCnt = 0;
    mTimer = new QTimer(this);
    mTimer->setInterval(50);
    connect(mTimer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    mTimer->start();

    //serial port find
    mPort = new QSerialPort(this);

    foreach(QSerialPortInfo portinfo, QSerialPortInfo::availablePorts()){
        ui->portsComboBox->addItem(QString("%1").arg(portinfo.portName()));
       qDebug() << "Ports"<< QString("%1 ").arg(portinfo.manufacturer() +' '+portinfo.portName());
       if(portinfo.hasProductIdentifier() && portinfo.hasVendorIdentifier()){
           if(0x6001==portinfo.productIdentifier() && 0x0403==portinfo.vendorIdentifier()){
               mPort->setPortName(portinfo.portName());
               qDebug() << "BSPK-1 found on " << mPort->portName();
//               mPort->setBaudRate(QSerialPort::Baud9600);
//               mPort->setDataBits(QSerialPort::Data8);
//               mPort->setFlowControl(QSerialPort::NoFlowControl);
//               mPort->setParity(QSerialPort::NoParity);
//               mPort->setStopBits(QSerialPort::OneStop);
               ui->portsComboBox->setCurrentText(mPort->portName());
           }
       }
    }
   statusLabel->setText("БСПК-1 на " + mPort->portName());

    connect(mPort, SIGNAL(readyRead()), this, SLOT(readyRead()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readyRead(){

    QByteArray input;
    mInBuffer.resize(mPort->readBufferSize());
    mInBuffer = mPort->readAll();

    serialParser(mInBuffer);
}

void MainWindow::serialParser(QByteArray &buffer){

}

void MainWindow::timerSlot(){
    if(100 > mCnt){
        mCnt++;

    }
    else
    {
        mCnt=0;
        statusProgBar->setInvertedAppearance(!statusProgBar->invertedAppearance());
    }
    statusProgBar->setFormat("%v");
    statusProgBar->setValue(mCnt);
}
