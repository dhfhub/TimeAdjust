#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>
#include <qdatetime.h>

#include <iostream>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pBOpenPort_clicked();
    void on_pBSetTime_clicked();
    void timerUpdate(void);
    void ReadData(void);

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
    QByteArray intTobyte(int *IntArray,int IntLen);
    quint16 CRC16(int *pushMsg,quint8 usDataLen);
};

#endif // MAINWINDOW_H
