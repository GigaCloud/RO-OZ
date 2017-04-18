#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileSystemWatcher>
#include <QFileDialog>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTime>
#include <QThread>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
        ui(new Ui::MainWindow) {
          /*  QFont font = QApplication::font();
            font.setStyleStrategy(QFont::PreferQuality);
            QApplication::setFont(font);*/

            ui->setupUi(this);
            setWindowTitle("RO-OZ");

        }

MainWindow::~MainWindow() {
    delete ui;
}

QFileSystemWatcher date;
QString fileName = NULL; //not taking any chances
QSerialPort port;
QSerialPortInfo portInfo;
QString portN;
QString data_string;


bool searchPort(QString portName) {
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        qInfo() << "Name : " << info.portName();
        qInfo() << "Description : " << info.description();
        qInfo() << "Manufacturer: " << info.manufacturer();
        if(info.portName() == portName){
            portInfo = info;
            qInfo() << "Am gasit";
            return true;
        }
    }
    return false;

}

bool openPort(int baud) {
    port.close();
    port.setPort(portInfo);
    port.setBaudRate(baud);
    bool success = port.open(QIODevice::ReadWrite);
    qInfo()<<"Baud: "<<baud;
    qInfo()<<"Port state: "<<success;
    return success;
}

void MainWindow::portRead() {
    port.blockSignals(true);
    QByteArray data = port.readAll();
    data_string = QString::fromLatin1(data.data());
    //qInfo() << data_string;
    if(fileName != NULL){
        ui->portName->setText("Reading");
        QFile outputFile(fileName);
        port.blockSignals(true);
        if (outputFile.open(QIODevice::Append)){
            QTextStream out(&outputFile);
            out<<data_string;
        }
        QThread::msleep(150);
        outputFile.close();
        //ui->portName->setText("OPENED");
        port.blockSignals(false);
    }
}

void MainWindow::on_openPort_clicked(){ /*"try to make connection" - button*/

    portN = ui->comList->currentText();
    qInfo()<<portN;
    if(searchPort(portN)){
        if(openPort(ui->baudList->currentText().toInt())){
            qInfo() << "Success!";
            ui->portName->clear();
            ui->portName->setText("OPENED");
        }
        else{
            qInfo() << "Failed to open";
            ui->portName->setText("FAILED");
        }
    }
    else{
        qInfo() << "Port not found";
        ui->portName->setText("NOT FND");
    }
}

void MainWindow::on_portName_returnPressed() {/*Enter <=> press button*/
    MainWindow::on_openPort_clicked();
}

void MainWindow::on_readButton_clicked() {
    QObject::connect(&port, SIGNAL (readyRead()), this, SLOT(portRead()));
    /*
    portRead();

    QString bufferString = QString::fromLocal8Bit(buffer);
    qInfo() << bufferString;
    ui->serialText->appendPlainText(bufferString);
    */
}

void MainWindow::on_searchButton_clicked() {
    ui->comList->clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        qInfo() << "Name : " << info.portName();
        ui->comList->addItem(info.portName());
    }
}

void MainWindow::on_fileButton_clicked() {

    fileName = QFileDialog::getOpenFileName(this, tr("Open Log File"), "C:/", tr("Text (*.txt)"));

    if(fileName != NULL)
    qInfo() << "opened: "<< date.addPath(fileName);

    qInfo() << date.files();

    ui->fileBox->setText(fileName);
}
