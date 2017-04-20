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

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
        ui(new Ui::MainWindow) {
          /*  QFont font = QApplication::font();
            font.setStyleStrategy(QFont::PreferQuality);
            QApplication::setFont(font);*/

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
int linie_count_altit;

int altit_max;


int id;
int Toto1Alive;
int Toto2Alive;
int Toto3Alive;
float lat = 46.9400, lon =  26.3500;
int map_update_count;

void MainWindow::on_fileButton_clicked() {

    for(int i=1; i<4; ++i){
        linie_count_hum[i]  = 10000;
        linie_count_temp[i] = 10000;

    }

    linie_count_altit = 10000;

    fileName = QFileDialog::getOpenFileName(this, tr("Open Log File"), "C:/", tr("Text (*.txt)"));

    if(fileName != NULL)
        date.addPath(fileName);

    //qInfo() << date.files();

    ui->fileBox->setText(fileName);

    QObject::connect(&date, SIGNAL(fileChanged(QString)), this, SLOT(fisierModificat()));

    QObject::connect(ui->zoom, SIGNAL(valueChanged(int)), this, SLOT(updateMap()));
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

void MainWindow::updateMap(){
    //https://www.openstreetmap.org/?mlat=46.9437&mlon=26.367#map=12/46.9437/26.3670
    int zoom = ui->zoom->value();
    QString url_string = "https://www.openstreetmap.org/?mlat=";
    url_string += QString::number(lat);
    url_string += "/&mlon=";
    url_string += QString::number(lon);
    url_string += "/#map=";
    url_string += QString::number(zoom);
    url_string += "/";
    url_string += QString::number(lat);
    url_string += "/";
    url_string += QString::number(lon);
    ui->map->setUrl(QUrl(url_string));
}


void MainWindow::fisierModificat() {

    for(int i=1; i<4; ++i){
        ++linie_count_hum[i];
        ++linie_count_temp[i];
    }
    //qInfo()<<"Fisier modificat";

    QVector<double> x_temp_1(linie_count_temp[1] + 100), y_temp_1(linie_count_temp[1] + 100);
    QVector<double> x_hum_1(linie_count_hum[1] + 100), y_hum_1(linie_count_hum[2] + 100);

    QVector<double> x_temp_2(linie_count_temp[2] + 100), y_temp_2(linie_count_temp[2] + 100);
    QVector<double> x_hum_2(linie_count_hum[2] + 100), y_hum_2(linie_count_hum[2] + 100);

    QVector<double> x_temp_3(linie_count_temp[3] + 100), y_temp_3(linie_count_temp[3] + 100);
    QVector<double> x_hum_3(linie_count_hum[3] + 100), y_hum_3(linie_count_hum[3] + 100);

    QVector<double> x_altit(linie_count_altit + 100), y_altit(linie_count_altit + 100);

    for(int i=1; i<4; ++i){
        linie_count_hum[i]  = 0;
        linie_count_temp[i] = 0;
    }

    linie_count_altit = 0;

    QFile inputFile(fileName);
    if (inputFile.open(QIODevice::ReadOnly)){
        QTextStream in(&inputFile);
        while (!in.atEnd()){
            bool ok = false;
            QString line = in.readLine();
            //qInfo()<<line;
            QStringList pieces = line.split(":");
            if(pieces.size() > 1){
                //qInfo()<<pieces[0];
                if(pieces[0] == "id"){
                    id = pieces[1].toInt();
                    //qInfo()<<id;
                }

                switch(id)
                {

                    case 1:{
                        if(pieces[0] == "temp"){
                            double temp = pieces[1].toDouble(&ok);
                            if(ok){
                                //qInfo()<<"temp"<<temp;
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
                                //qInfo()<<"hum"<<hum;
                                ++linie_count_hum[id];
                            }
                        }

                        break;
                    }

                    case 2:{
                        if(pieces[0] == "temp"){
                            double temp = pieces[1].toDouble(&ok);
                            if(ok){
                                //qInfo()<<"temp"<<temp;
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
                                //qInfo()<<"hum"<<hum;
                                ++linie_count_hum[id];
                            }
                        }

                        break;
                    }

                    case 3:{
                        if(pieces[0] == "temp"){
                            double temp = pieces[1].toDouble(&ok);
                            if(ok){
                                //qInfo()<<"temp"<<temp;
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
                                //qInfo()<<"hum"<<hum;
                                ++linie_count_hum[id];
                            }
                        }

                        break;
                    }
                }

               if(pieces[0] == "lat"){
                  if(pieces[1].toInt() > 1000){
                    QByteArray b = pieces[1].toLatin1();
                    QString latWithDecimal;
                    latWithDecimal += b[1];
                    latWithDecimal += b[2];
                    latWithDecimal += '.';
                    for(int i=3; i<b.length(); ++i)
                        latWithDecimal += b[i];
                    lat = latWithDecimal.toFloat();
                    ui->latitude->setText(latWithDecimal);
                  }
                }

                if(pieces[0] == "lon"){
                   if(pieces[1].toInt() > 1000){
                    QByteArray b = pieces[1].toLatin1();
                    QString lonWithDecimal;
                    lonWithDecimal += b[1];
                    lonWithDecimal += b[2];
                    lonWithDecimal += '.';
                    for(int i=3; i<b.length(); ++i)
                        lonWithDecimal += b[i];
                    lon = lonWithDecimal.toFloat();
                    ui->longitude->setText(lonWithDecimal);
                    }


                }

                if(pieces[0] == "alt"){
                    if(pieces[1].toInt() < 1500){
                        ui->altitude->setText(pieces[1]);
                        x_altit[linie_count_altit] = linie_count_altit;
                        y_altit[linie_count_altit] = pieces[1].toInt();
                        if(pieces[1].toInt() > altit_max) altit_max = pieces[1].toInt();
                        linie_count_altit += 1;
                    }
                }

                if(pieces[0] == "a_x"){
                    ui->accx->setText(pieces[1]);
                }

                if(pieces[0] == "a_y"){
                    ui->accy->setText(pieces[1]);
                }

                if(pieces[0] == "a_z"){
                    ui->accz->setText(pieces[1]);
                }

                if(pieces[0] == "g_x"){
                    ui->gyrox->setText(pieces[1]);
                }

                if(pieces[0] == "g_y"){
                    ui->gyroy->setText(pieces[1]);
                }

                if(pieces[0] == "g_z"){
                    ui->gyroz->setText(pieces[1]);
                }

                if(pieces[0] == "m_x"){
                    ui->magnetox->setText(pieces[1]);
                }

                if(pieces[0] == "m_y"){
                    ui->magnetoy->setText(pieces[1]);
                }

                if(pieces[0] == "m_z"){
                    ui->magnetoz->setText(pieces[1]);
                }

                if(pieces[0] == "P"){
                    ui->pressure->setText(pieces[1]);
                }

                if(pieces[0] == "T"){
                    int T = pieces[1].toInt();
                    if(T<0) T*=(-1);
                    float fT = T;
                    if(T > 10000) fT /=  float(100);
                    if(T > 1000)  fT /= float(10);
                    ui->temperature->setText(QString::number(fT));
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

    if(id == 1){
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
    }

    if(id == 2){
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

    }

    //A treia sonda
    if(id == 3){
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

    ui->Dorothy->addGraph();
    ui->Dorothy->graph(0)->setData(x_altit, y_altit);
    ui->Dorothy->xAxis->setRange(0, linie_count_altit);
    ui->Dorothy->yAxis->setRange(0, altit_max);
    ui->Dorothy->replot();



}


