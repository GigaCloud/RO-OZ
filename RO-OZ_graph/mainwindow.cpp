#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileSystemWatcher>
#include <QString>
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTime>
#include <QThread>
#include <QElapsedTimer>
#include <QWebEngineView>
#include <QWebChannel>
#include <QUrl>

QElapsedTimer timer;

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
        ui(new Ui::MainWindow) {
            ui->setupUi(this);
            setWindowTitle("RO-OZ");

            ui->map->setContextMenuPolicy(Qt::NoContextMenu);
            QWebEnginePage *page = new QWebEnginePage(this);
            ui->map->setPage(page);
            QWebChannel *channel = new QWebChannel(this);
            page->setWebChannel(channel);

            ui->map->setUrl(QUrl("https://www.openstreetmap.org"));

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


//Graph stuff
int linie_count_hum[4];
int linie_count_temp[4];
int id;
int Toto1Alive;
int Toto2Alive;
int Toto3Alive;
float lat, lon;

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
    timer.start();

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
    updateMap(46.94, 26.35, 8);

}

void MainWindow::on_fileButton_clicked() {

    fileName = QFileDialog::getOpenFileName(this, tr("Open Log File"), "C:/", tr("Text (*.txt)"));

    if(fileName != NULL)
    qInfo() << "opened: "<< date.addPath(fileName);

    qInfo() << date.files();

    ui->fileBox->setText(fileName);

    QObject::connect(&date, SIGNAL(fileChanged(QString)), this, SLOT(fisierModificat()));

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

void MainWindow::updateMap(float lat, float lon, int zoom){
//https://www.openstreetmap.org/?mlat=46.9437&mlon=26.367#map=12/46.9437/26.3670
    QString url_string = "https://www.openstreetmap.org/?mlat=";
    url_string += QString::number(lat);
    url_string += "/&mlon=";
    url_string += QString::number(lon);
    url_string += "/#map=";
    url_string += QString::number(zoom);
    ui->map->setUrl(QUrl(url_string));
}


void MainWindow::fisierModificat() {

    for(int i=1; i<4; ++i){
        ++linie_count_hum[i];
        ++linie_count_temp[i];
    }
    qInfo()<<"Fisier modificat";

    QVector<double> x_temp_1(linie_count_temp[1] + 100), y_temp_1(linie_count_temp[1] + 100);
    QVector<double> x_hum_1(linie_count_hum[1] + 100), y_hum_1(linie_count_hum[2] + 100);

    QVector<double> x_temp_2(linie_count_temp[2] + 100), y_temp_2(linie_count_temp[2] + 100);
    QVector<double> x_hum_2(linie_count_hum[2] + 100), y_hum_2(linie_count_hum[2] + 100);

    QVector<double> x_temp_3(linie_count_temp[3] + 100), y_temp_3(linie_count_temp[3] + 100);
    QVector<double> x_hum_3(linie_count_hum[3] + 100), y_hum_3(linie_count_hum[3] + 100);

    for(int i=1; i<4; ++i){
        linie_count_hum[i]  = 0;
        linie_count_temp[i] = 0;
    }


    QFile inputFile(fileName);
    if (inputFile.open(QIODevice::ReadOnly)){
        QTextStream in(&inputFile);
        while (!in.atEnd()){
            bool ok = false;
            QString line = in.readLine();
            qInfo()<<line;
            QStringList pieces = line.split(":");
            if(pieces.size() > 1){
                qInfo()<<pieces[0];
                if(pieces[0] == "id"){
                    id = pieces[1].toInt();
                    qInfo()<<id;
                }

                switch(id)
                {
                    case -1:{
                        qInfo()<<"Fara date de la sonda";
                    }

                    case 1:{
                        if(pieces[0] == "temp"){
                            double temp = pieces[1].toDouble(&ok);
                            if(ok){
                                qInfo()<<"temp"<<temp;
                                y_temp_1[linie_count_temp[id]] = temp;
                                x_temp_1[linie_count_temp[id]] = linie_count_temp[id];
                                ++linie_count_temp[id];
                            }
                        }

                        if(pieces[0] == "hum"){
                            double hum = pieces[1].toDouble(&ok);
                            if(ok){
                                y_hum_1[linie_count_hum[id]] = hum;
                                x_hum_1[linie_count_hum[id]] = linie_count_hum[id];
                                qInfo()<<"hum"<<hum;
                                ++linie_count_hum[id];
                            }
                        }

                        break;
                    }

                    case 2:{
                        if(pieces[0] == "temp"){
                            double temp = pieces[1].toDouble(&ok);
                            if(ok){
                                qInfo()<<"temp"<<temp;
                                y_temp_2[linie_count_temp[id]] = temp;
                                x_temp_2[linie_count_temp[id]] = linie_count_temp[id];
                                ++linie_count_temp[id];
                            }
                        }

                        if(pieces[0] == "hum"){
                            double hum = pieces[1].toDouble(&ok);
                            if(ok){
                                y_hum_2[linie_count_hum[id]] = hum;
                                x_hum_2[linie_count_hum[id]] = linie_count_hum[id];
                                qInfo()<<"hum"<<hum;
                                ++linie_count_hum[id];
                            }
                        }

                        break;
                    }

                    case 3:{
                        if(pieces[0] == "temp"){
                            double temp = pieces[1].toDouble(&ok);
                            if(ok){
                                qInfo()<<"temp"<<temp;
                                y_temp_3[linie_count_temp[id]] = temp;
                                x_temp_3[linie_count_temp[id]] = linie_count_temp[id];
                                ++linie_count_temp[id];
                            }
                        }

                        if(pieces[0] == "hum"){
                            double hum = pieces[1].toDouble(&ok);
                            if(ok){
                                y_hum_3[linie_count_hum[id]] = hum;
                                x_hum_3[linie_count_hum[id]] = linie_count_hum[id];
                                qInfo()<<"hum"<<hum;
                                ++linie_count_hum[id];
                            }
                        }

                        break;
                    }
                }

                if(pieces[0] == "lat"){
                    lat = pieces[1].toInt();
                }

                if(pieces[0] == "lon"){
                    lon = pieces[1].toInt();
                }

                if(pieces[0] == "lat_p"){
                    ui->latitude->setText(pieces[1]);
                }

                if(pieces[0] == "a_x"){
                    ui->accx->setText(pieces[1]);
                }

                if(pieces[0] == "a_y"){

                }

                if(pieces[0] == "a_z"){

                }

                if(pieces[0] == "g_x"){

                }

                if(pieces[0] == "g_y"){

                }

                if(pieces[0] == "g_z"){

                }

                if(pieces[0] == "m_x"){

                }

                if(pieces[0] == "m_y"){

                }

                if(pieces[0] == "m_z"){

                }

                if(pieces[0] == "P"){

                }

                if(pieces[0] == "T"){

                }


            }

        }
        inputFile.close();
    }


    //Prima sonda
    ui->Toto1Text->setTextColor(Qt::darkGreen);
    ui->Toto1Text->update();

    QPalette greenAF    = palette();
    QPalette yellowAF   = palette();
    QPalette redAF      = palette();

    greenAF.setColor(QPalette::Background, Qt::darkGreen);
    yellowAF.setColor(QPalette::Background, Qt::yellow);
    redAF.setColor(QPalette::Background, Qt::darkRed);


    if(id == 1){
        ui->Toto1Color->setAutoFillBackground(true);
        ui->Toto1Color->setPalette(greenAF);
        ui->Toto1Color->show();
        Toto1Alive = 0;
    }

    if(id == 2){
        ui->Toto2Color->setAutoFillBackground(true);
        ui->Toto2Color->setPalette(greenAF);
        ui->Toto2Color->show();
        Toto2Alive = 0;
    }

    if(id == 3){
        ui->Toto3Color->setAutoFillBackground(true);
        ui->Toto3Color->setPalette(greenAF);
        ui->Toto3Color->show();
        Toto3Alive = 0;
    }

    if(Toto1Alive > 2){

        if(Toto1Alive > 4){
            ui->Toto1Color->setAutoFillBackground(true);
            ui->Toto1Color->setPalette(redAF);
            ui->Toto1Color->show();

        }

        else{
            ui->Toto1Color->setAutoFillBackground(true);
            ui->Toto1Color->setPalette(yellowAF);
            ui->Toto1Color->show();

        }

    }

    if(Toto2Alive > 2){

        if(Toto2Alive > 4){
            ui->Toto2Color->setAutoFillBackground(true);
            ui->Toto2Color->setPalette(redAF);
            ui->Toto2Color->show();

        }

        else{
            ui->Toto2Color->setAutoFillBackground(true);
            ui->Toto2Color->setPalette(yellowAF);
            ui->Toto2Color->show();

        }

    }

    if(Toto3Alive > 2){

        if(Toto3Alive > 4){
            ui->Toto3Color->setAutoFillBackground(true);
            ui->Toto3Color->setPalette(redAF);
            ui->Toto3Color->show();

        }

        else{
            ui->Toto3Color->setAutoFillBackground(true);
            ui->Toto3Color->setPalette(yellowAF);
            ui->Toto3Color->show();

        }

    }

    ++Toto1Alive;
    ++Toto2Alive;
    ++Toto3Alive;


    ui->Toto1Text->setAutoFillBackground(true);
    ui->Toto1Text->setPalette(greenAF);
    ui->Toto1Text->show();

    ui->Toto1->addGraph();
    ui->Toto1->graph(0)->setData(x_temp_1, y_temp_1);
    ui->Toto1->graph(0)->setPen(QColor(255,0,0,255));

    ui->Toto1->xAxis->setRange(0, (linie_count_hum[1] > linie_count_temp[1])? linie_count_hum[1]:linie_count_temp[1]);
    ui->Toto1->yAxis->setRange(0, maximumValue(y_hum_1, y_temp_1, linie_count_hum[1], linie_count_temp[1]));

    ui->Toto1->addGraph();
    ui->Toto1->graph(1)->setData(x_hum_1, y_hum_1);

    ui->Toto1->xAxis->setLabel("Valoare");
    ui->Toto1->yAxis->setLabel("Temp, Hum");

    ui->Toto1->replot();


    //A doua sonda
    ui->Toto2->addGraph();
    ui->Toto2->graph(0)->setData(x_temp_2, y_temp_2);
    ui->Toto2->graph(0)->setPen(QColor(255,0,0,255));

    ui->Toto2->xAxis->setRange(0, (linie_count_hum[2] > linie_count_temp[2])? linie_count_hum[2]:linie_count_temp[2]);
    ui->Toto2->yAxis->setRange(0, maximumValue(y_hum_2, y_temp_2, linie_count_hum[2], linie_count_temp[2]));

    ui->Toto2->addGraph();
    ui->Toto2->graph(1)->setData(x_hum_2, y_hum_2);

    ui->Toto2->xAxis->setLabel("Valoare");
    ui->Toto2->yAxis->setLabel("Temp, Hum");

    ui->Toto2->replot();


    //A treia sonda
    ui->Toto3->addGraph();
    ui->Toto3->graph(0)->setData(x_temp_3, y_temp_3);
    ui->Toto3->graph(0)->setPen(QColor(255,0,0,255));

    ui->Toto3->xAxis->setRange(0, (linie_count_hum[3] > linie_count_temp[3])? linie_count_hum[3] : linie_count_temp[3]);
    ui->Toto3->yAxis->setRange(0, maximumValue(y_hum_3, y_temp_3, linie_count_hum[3], linie_count_temp[3]));

    ui->Toto3->addGraph();
    ui->Toto3->graph(1)->setData(x_hum_3, y_hum_3);

    ui->Toto3->xAxis->setLabel("Valoare");
    ui->Toto3->yAxis->setLabel("Temp, Hum");

    ui->Toto3->replot();


}


