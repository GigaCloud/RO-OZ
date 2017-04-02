#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileSystemWatcher>
#include <QString>
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTime>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("RO-OZ");

}

MainWindow::~MainWindow()
{
    delete ui;
}

QFileSystemWatcher date;
QString fileName = NULL; //not taking any chances
QSerialPort port;
QSerialPortInfo portInfo;
QString portN;
QString data_string;


//Graph stuff

int linie_count_temp = 10000;
int linie_count_hum  = 10000;


bool searchPort(QString portName)
{
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

bool openPort(int baud)
{
    port.close();
    port.setPort(portInfo);
    port.setBaudRate(baud);
    bool success = port.open(QIODevice::ReadWrite);
    qInfo()<<"Baud: "<<baud;
    qInfo()<<"Port state: "<<success;
    return success;
}

void MainWindow::portRead(){
    port.blockSignals(true);
    QByteArray data = port.readAll();
    data_string = QString::fromLatin1(data.data());
    //qInfo() << data_string;

    if(fileName != NULL){
        QFile outputFile(fileName);
        port.blockSignals(true);
        if (outputFile.open(QIODevice::Append)){
            QTextStream out(&outputFile);
            out<<data_string;
        }
        QThread::msleep(150);
        outputFile.close();
        port.blockSignals(false);
    }



}

void MainWindow::on_openPort_clicked() //try to make connection - button
{
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

void MainWindow::on_portName_returnPressed() //Enter <=> press button
{
    MainWindow::on_openPort_clicked();
}



void MainWindow::on_readButton_clicked()
{

    QObject::connect(&port, SIGNAL (readyRead()), this, SLOT(portRead()));

    /*
    portRead();

    QString bufferString = QString::fromLocal8Bit(buffer);
    qInfo() << bufferString;
    ui->serialText->appendPlainText(bufferString);
    */
}

void MainWindow::on_searchButton_clicked()
{
    ui->comList->clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
           qInfo() << "Name : " << info.portName();
           ui->comList->addItem(info.portName());
    }

}


double maximumValue(QVector<double> vector1, QVector<double> vector2, int linie_count_1, int linie_count_2){
    double maxim1 = 0;
    double maxim2 = 0;
    for(int i=0; i<linie_count_1; ++i)
        if(vector1[i] > maxim1)
            maxim1 = vector1[i];
    for(int i=0; i<linie_count_2; ++i)
        if(vector2[i] > maxim2)
            maxim2 = vector2[i];
    maxim1 += 1;
    maxim2 += 1;
    return (maxim1>maxim2)? maxim1 : maxim2;
}


void MainWindow::on_fileButton_clicked()
{

    fileName = QFileDialog::getOpenFileName(this, tr("Open Log File"), "C:/", tr("Text (*.txt)"));

    if(fileName != NULL)
        qInfo() << "opened: "<< date.addPath(fileName);

    qInfo() << date.files();

    ui->fileBox->setText(fileName);

    QObject::connect(&date, SIGNAL(fileChanged(QString)), this, SLOT(fisierModificat()));

}



void MainWindow::fisierModificat(){

    date.blockSignals(true);

    ++linie_count_temp;
    ++linie_count_hum;

    QVector<double> x_temp(linie_count_temp), y_temp(linie_count_temp);
    QVector<double> x_hum(linie_count_hum), y_hum(linie_count_hum);

    linie_count_temp = 0;
    linie_count_hum  = 0;

    QFile inputFile(fileName);
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd()){
          bool ok = false;
          QString line = in.readLine();
          QStringList pieces = line.split(":");
          if(pieces.size() > 1){

              if(pieces[0] == "id"){
                 int id = pieces[1].toInt();
                 qInfo()<<id;
             }

             if(pieces[0] == " temp"){
                  double temp = pieces[1].toDouble(&ok);
                  if(ok){
                     qInfo()<<"temp"<<temp;
                     y_temp[linie_count_temp] = temp;
                     x_temp[linie_count_temp] = linie_count_temp;
                     ++linie_count_temp;
                  }
             }

             if(pieces[0] == " hum"){
                  double hum = pieces[1].toDouble(&ok);
                  if(ok){
                     y_hum[linie_count_hum] = hum;
                     x_hum[linie_count_hum] = linie_count_hum;
                     qInfo()<<"hum"<<hum;
                     ++linie_count_hum;
                  }
             }

          }
       }

       inputFile.close();
    }



    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x_temp, y_temp);
    ui->customPlot->graph(0)->setPen(QColor(255,0,0,255));

    ui->customPlot->xAxis->setRange(0, (linie_count_hum > linie_count_temp)? linie_count_hum:linie_count_temp);
    ui->customPlot->yAxis->setRange(0, maximumValue(y_hum, y_temp, linie_count_hum, linie_count_temp));

    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setData(x_hum, y_hum);

    ui->customPlot->xAxis->setLabel("Valoare");
    ui->customPlot->yAxis->setLabel("Temp, Hum");

    ui->customPlot->replot();

    date.blockSignals(false);

}


