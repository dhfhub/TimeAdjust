#include "mainwindow.h"
#include "ui_mainwindow.h"



// CRC 高位字节值表
static const quint8 auchCRCHi[] = {
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
} ;
// CRC 低位字节值表
static const quint8 auchCRCLo[] = {
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06,
    0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,
    0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
    0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,
    0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4,
    0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3,
    0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
    0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
    0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,
    0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED,
    0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
    0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60,
    0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,
    0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
    0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
    0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E,
    0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
    0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71,
    0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,
    0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
    0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,
    0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B,
    0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
    0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42,
    0x43, 0x83, 0x41, 0x81, 0x80, 0x40
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("时钟同步");

    setFixedSize(this->width(),this->height());

    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))
        {
            ui->portcomboBox->addItem(serial.portName());
            serial.close();
        }
    }
    ui->baudcomboBox->setCurrentIndex(7);
    ui->databitscomboBox->setCurrentIndex(1);
    ui->paritycomboBox->setCurrentIndex(1);
    ui->stopbitcomboBox->setCurrentIndex(0);
    ui->pBSetTime->setEnabled(false);


    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pBOpenPort_clicked()
{
    if(ui->pBOpenPort->text()==tr("打开串口"))
    {
        serial = new QSerialPort;
        serial->setPortName(ui->portcomboBox->currentText());
        serial->open(QIODevice::ReadWrite);
        serial->setBaudRate(ui->baudcomboBox->currentText().toInt());
        switch (ui->databitscomboBox->currentText().toInt()) {
        case 7:serial->setDataBits(QSerialPort::Data7);break;
        case 8:serial->setDataBits(QSerialPort::Data8);break;
        default:break;
        }
        switch (ui->paritycomboBox->currentIndex()) {
        case 0:serial->setParity(QSerialPort::NoParity);break;
        case 1:serial->setParity(QSerialPort::EvenParity);break;
        case 2:serial->setParity(QSerialPort::OddParity);break;
        case 3:serial->setParity(QSerialPort::MarkParity);break;
        case 4:serial->setParity(QSerialPort::SpaceParity);break;
        default:break;
        }
        switch (ui->stopbitcomboBox->currentIndex()) {
        case 0:serial->setStopBits(QSerialPort::OneStop);break;
        case 1:serial->setStopBits(QSerialPort::OneAndHalfStop);break;
        case 2:serial->setStopBits(QSerialPort::TwoStop);break;
        default:break;
        }
        serial->setFlowControl(QSerialPort::NoFlowControl);

        ui->baudcomboBox->setEnabled(false);
        ui->databitscomboBox->setEnabled(false);
        ui->paritycomboBox->setEnabled(false);
        ui->stopbitcomboBox->setEnabled(false);
        ui->pBOpenPort->setText("关闭串口");
        ui->pBSetTime->setEnabled(true);
        connect(serial,&QSerialPort::readyRead,this,&MainWindow::ReadData);


    }
    else
    {
        serial->clear();
        serial->close();
        serial->deleteLater();

        ui->baudcomboBox->setEnabled(true);
        ui->databitscomboBox->setEnabled(true);
        ui->paritycomboBox->setEnabled(true);
        ui->stopbitcomboBox->setEnabled(true);
        ui->pBOpenPort->setText("打开串口");
        ui->pBSetTime->setEnabled(false);

    }
}

void MainWindow::ReadData(void)
{
    QByteArray buf;
    buf = serial->readAll();
    ui->textEditPrint->clear();
    if(!buf.isEmpty())
    {
        QString str = ui->textEditPrint->toPlainText();
        //str+=tr(buf);//显示中文乱码
        str+=QString::fromLocal8Bit(buf);
        ui->textEditPrint->clear();
        ui->textEditPrint->append(str);
    }
    buf.clear();
}


void MainWindow::on_pBSetTime_clicked()
{
    int Timeset_data[15];
    QByteArray Timeset;
    Timeset.resize(15);
    QDate currentdate = QDate::currentDate();
    QTime currenttime = QTime::currentTime();
    Timeset_data[0] = 0xFC;
    Timeset_data[1] = 0xFD;
    Timeset_data[2] = 0x10;
    Timeset_data[3] = currenttime.second();
    Timeset_data[4] = currenttime.minute();
    Timeset_data[5] = currenttime.hour();
    Timeset_data[6] = currentdate.day();
    Timeset_data[7] = currentdate.month();
    Timeset_data[8] = currentdate.year() >> 8;
    Timeset_data[9] = currentdate.year() & 0xFF;
    Timeset_data[10] = currentdate.dayOfWeek();
    Timeset_data[11] = CRC16(Timeset_data,11) & 0xFF;
    Timeset_data[12] = CRC16(Timeset_data,11) >> 8;
    Timeset_data[13] = 0xFE;
    Timeset_data[14] = 0xFF;
    Timeset = intTobyte(Timeset_data,15);
    serial->write(Timeset,15);
}

QByteArray MainWindow::intTobyte(int *IntArray,int IntLen)
{
    QByteArray bytearray;
    bytearray.resize(IntLen);
    for(int i=0;i<IntLen;i++)
    {
        bytearray[i] = (uchar)IntArray[i];
    }
    return  bytearray;
}

quint16 MainWindow::CRC16(int *pushMsg,quint8 usDataLen)
{
    quint8 uchCRCHi = 0xFF;
    quint8 uchCRCLo = 0xFF;
    quint16 uIndex;
    while(usDataLen--)
    {
        uIndex = uchCRCLo ^ (quint8)(*pushMsg++);
        uchCRCLo = uchCRCHi^auchCRCHi[uIndex];
        uchCRCHi = auchCRCLo[uIndex];
    }
    return (uchCRCHi<<8|uchCRCLo);
}

void MainWindow::timerUpdate(void)
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->textEditTimeDisplay->setText(str);
}

