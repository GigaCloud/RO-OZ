/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"
#include "qwebengineview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *widget_plot;
    QWidget *layoutWidget;
    QVBoxLayout *fileStuff;
    QPushButton *fileButton;
    QLineEdit *fileBox;
    QWidget *layoutWidget1;
    QHBoxLayout *PortStuff;
    QPushButton *openPort;
    QVBoxLayout *verticalLayout;
    QComboBox *comList;
    QComboBox *baudList;
    QPushButton *searchButton;
    QLineEdit *portName;
    QPushButton *readButton;
    QCustomPlot *Toto2;
    QCustomPlot *Toto3;
    QCustomPlot *Toto1;
    QWidget *Toto1Color;
    QTextBrowser *Toto1Text;
    QWidget *Toto2Color;
    QTextBrowser *Toto2Text;
    QWidget *Toto3Color;
    QTextBrowser *Toto3Text;
    QCustomPlot *Dorothy;
    QWidget *DorothyColor;
    QTextBrowser *DorothyText;
    QWebEngineView *map;
    QWidget *widget;
    QVBoxLayout *MagnetoGyro;
    QHBoxLayout *Magneto;
    QVBoxLayout *Lables_6;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QVBoxLayout *DorothyGPS_6;
    QLineEdit *magnetox;
    QLineEdit *magnetoy;
    QLineEdit *magnetoz;
    QFrame *line_3;
    QHBoxLayout *Gyro;
    QVBoxLayout *Lables_5;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QVBoxLayout *DorothyGPS_5;
    QLineEdit *gyrox;
    QLineEdit *gyroy;
    QLineEdit *gyroz;
    QWidget *widget1;
    QVBoxLayout *GPS_PTA_Acc;
    QHBoxLayout *LatLonAlt;
    QVBoxLayout *Lables;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QVBoxLayout *DorothyGPS;
    QLineEdit *latitude;
    QLineEdit *longitude;
    QLineEdit *altitude;
    QFrame *line_2;
    QHBoxLayout *PTA;
    QVBoxLayout *Lables_2;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QVBoxLayout *DorothyGPS_2;
    QLineEdit *pressure;
    QLineEdit *temperature;
    QLineEdit *altitude_2;
    QFrame *line;
    QHBoxLayout *Acc;
    QVBoxLayout *Lables_3;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QVBoxLayout *DorothyGPS_3;
    QLineEdit *accx;
    QLineEdit *accy;
    QLineEdit *accz;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1920, 1080);
        MainWindow->setMinimumSize(QSize(1000, 1000));
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        MainWindow->setMouseTracking(false);
        MainWindow->setStyleSheet(QStringLiteral("font: 10pt \"Segoe UI\";"));
        widget_plot = new QWidget(MainWindow);
        widget_plot->setObjectName(QStringLiteral("widget_plot"));
        layoutWidget = new QWidget(widget_plot);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 110, 58));
        fileStuff = new QVBoxLayout(layoutWidget);
        fileStuff->setSpacing(6);
        fileStuff->setContentsMargins(11, 11, 11, 11);
        fileStuff->setObjectName(QStringLiteral("fileStuff"));
        fileStuff->setContentsMargins(0, 0, 0, 0);
        fileButton = new QPushButton(layoutWidget);
        fileButton->setObjectName(QStringLiteral("fileButton"));

        fileStuff->addWidget(fileButton);

        fileBox = new QLineEdit(layoutWidget);
        fileBox->setObjectName(QStringLiteral("fileBox"));
        fileBox->setReadOnly(true);

        fileStuff->addWidget(fileBox);

        layoutWidget1 = new QWidget(widget_plot);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(740, 10, 449, 60));
        PortStuff = new QHBoxLayout(layoutWidget1);
        PortStuff->setSpacing(6);
        PortStuff->setContentsMargins(11, 11, 11, 11);
        PortStuff->setObjectName(QStringLiteral("PortStuff"));
        PortStuff->setContentsMargins(0, 0, 0, 0);
        openPort = new QPushButton(layoutWidget1);
        openPort->setObjectName(QStringLiteral("openPort"));

        PortStuff->addWidget(openPort);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        comList = new QComboBox(layoutWidget1);
        comList->setObjectName(QStringLiteral("comList"));

        verticalLayout->addWidget(comList);

        baudList = new QComboBox(layoutWidget1);
        baudList->setObjectName(QStringLiteral("baudList"));

        verticalLayout->addWidget(baudList);


        PortStuff->addLayout(verticalLayout);

        searchButton = new QPushButton(layoutWidget1);
        searchButton->setObjectName(QStringLiteral("searchButton"));

        PortStuff->addWidget(searchButton);

        portName = new QLineEdit(layoutWidget1);
        portName->setObjectName(QStringLiteral("portName"));

        PortStuff->addWidget(portName);

        readButton = new QPushButton(layoutWidget1);
        readButton->setObjectName(QStringLiteral("readButton"));

        PortStuff->addWidget(readButton);

        Toto2 = new QCustomPlot(widget_plot);
        Toto2->setObjectName(QStringLiteral("Toto2"));
        Toto2->setGeometry(QRect(50, 570, 501, 361));
        Toto3 = new QCustomPlot(widget_plot);
        Toto3->setObjectName(QStringLiteral("Toto3"));
        Toto3->setGeometry(QRect(1350, 100, 502, 361));
        Toto1 = new QCustomPlot(widget_plot);
        Toto1->setObjectName(QStringLiteral("Toto1"));
        Toto1->setGeometry(QRect(50, 100, 501, 361));
        Toto1Color = new QWidget(widget_plot);
        Toto1Color->setObjectName(QStringLiteral("Toto1Color"));
        Toto1Color->setGeometry(QRect(230, 480, 101, 31));
        Toto1Text = new QTextBrowser(Toto1Color);
        Toto1Text->setObjectName(QStringLiteral("Toto1Text"));
        Toto1Text->setGeometry(QRect(0, 0, 91, 31));
        Toto1Text->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Toto1Text->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Toto1Text->setAcceptRichText(true);
        Toto1Text->setTextInteractionFlags(Qt::NoTextInteraction);
        Toto2Color = new QWidget(widget_plot);
        Toto2Color->setObjectName(QStringLiteral("Toto2Color"));
        Toto2Color->setGeometry(QRect(230, 950, 101, 31));
        Toto2Text = new QTextBrowser(Toto2Color);
        Toto2Text->setObjectName(QStringLiteral("Toto2Text"));
        Toto2Text->setGeometry(QRect(0, 0, 91, 31));
        Toto2Text->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Toto2Text->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Toto2Text->setAcceptRichText(true);
        Toto2Text->setTextInteractionFlags(Qt::NoTextInteraction);
        Toto3Color = new QWidget(widget_plot);
        Toto3Color->setObjectName(QStringLiteral("Toto3Color"));
        Toto3Color->setGeometry(QRect(1590, 480, 101, 31));
        Toto3Text = new QTextBrowser(Toto3Color);
        Toto3Text->setObjectName(QStringLiteral("Toto3Text"));
        Toto3Text->setGeometry(QRect(0, 0, 91, 31));
        Toto3Text->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Toto3Text->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Toto3Text->setAcceptRichText(true);
        Toto3Text->setTextInteractionFlags(Qt::NoTextInteraction);
        Dorothy = new QCustomPlot(widget_plot);
        Dorothy->setObjectName(QStringLiteral("Dorothy"));
        Dorothy->setGeometry(QRect(1350, 570, 502, 361));
        DorothyColor = new QWidget(widget_plot);
        DorothyColor->setObjectName(QStringLiteral("DorothyColor"));
        DorothyColor->setGeometry(QRect(1580, 950, 111, 31));
        DorothyText = new QTextBrowser(DorothyColor);
        DorothyText->setObjectName(QStringLiteral("DorothyText"));
        DorothyText->setGeometry(QRect(0, 0, 111, 31));
        DorothyText->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        DorothyText->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        DorothyText->setAcceptRichText(true);
        DorothyText->setTextInteractionFlags(Qt::NoTextInteraction);
        map = new QWebEngineView(widget_plot);
        map->setObjectName(QStringLiteral("map"));
        map->setGeometry(QRect(650, 570, 601, 361));
        widget = new QWidget(widget_plot);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(970, 150, 221, 191));
        MagnetoGyro = new QVBoxLayout(widget);
        MagnetoGyro->setSpacing(6);
        MagnetoGyro->setContentsMargins(11, 11, 11, 11);
        MagnetoGyro->setObjectName(QStringLiteral("MagnetoGyro"));
        MagnetoGyro->setContentsMargins(0, 0, 0, 0);
        Magneto = new QHBoxLayout();
        Magneto->setSpacing(6);
        Magneto->setObjectName(QStringLiteral("Magneto"));
        Lables_6 = new QVBoxLayout();
        Lables_6->setSpacing(6);
        Lables_6->setObjectName(QStringLiteral("Lables_6"));
        label_16 = new QLabel(widget);
        label_16->setObjectName(QStringLiteral("label_16"));
        QFont font;
        font.setFamily(QStringLiteral("Segoe UI"));
        font.setPointSize(10);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        label_16->setFont(font);

        Lables_6->addWidget(label_16);

        label_17 = new QLabel(widget);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setFont(font);

        Lables_6->addWidget(label_17);

        label_18 = new QLabel(widget);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setFont(font);

        Lables_6->addWidget(label_18);


        Magneto->addLayout(Lables_6);

        DorothyGPS_6 = new QVBoxLayout();
        DorothyGPS_6->setSpacing(6);
        DorothyGPS_6->setObjectName(QStringLiteral("DorothyGPS_6"));
        magnetox = new QLineEdit(widget);
        magnetox->setObjectName(QStringLiteral("magnetox"));

        DorothyGPS_6->addWidget(magnetox);

        magnetoy = new QLineEdit(widget);
        magnetoy->setObjectName(QStringLiteral("magnetoy"));

        DorothyGPS_6->addWidget(magnetoy);

        magnetoz = new QLineEdit(widget);
        magnetoz->setObjectName(QStringLiteral("magnetoz"));

        DorothyGPS_6->addWidget(magnetoz);


        Magneto->addLayout(DorothyGPS_6);


        MagnetoGyro->addLayout(Magneto);

        line_3 = new QFrame(widget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        MagnetoGyro->addWidget(line_3);

        Gyro = new QHBoxLayout();
        Gyro->setSpacing(6);
        Gyro->setObjectName(QStringLiteral("Gyro"));
        Lables_5 = new QVBoxLayout();
        Lables_5->setSpacing(6);
        Lables_5->setObjectName(QStringLiteral("Lables_5"));
        label_13 = new QLabel(widget);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setFont(font);

        Lables_5->addWidget(label_13);

        label_14 = new QLabel(widget);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setFont(font);

        Lables_5->addWidget(label_14);

        label_15 = new QLabel(widget);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setFont(font);

        Lables_5->addWidget(label_15);


        Gyro->addLayout(Lables_5);

        DorothyGPS_5 = new QVBoxLayout();
        DorothyGPS_5->setSpacing(6);
        DorothyGPS_5->setObjectName(QStringLiteral("DorothyGPS_5"));
        gyrox = new QLineEdit(widget);
        gyrox->setObjectName(QStringLiteral("gyrox"));

        DorothyGPS_5->addWidget(gyrox);

        gyroy = new QLineEdit(widget);
        gyroy->setObjectName(QStringLiteral("gyroy"));

        DorothyGPS_5->addWidget(gyroy);

        gyroz = new QLineEdit(widget);
        gyroz->setObjectName(QStringLiteral("gyroz"));

        DorothyGPS_5->addWidget(gyroz);


        Gyro->addLayout(DorothyGPS_5);


        MagnetoGyro->addLayout(Gyro);

        widget1 = new QWidget(widget_plot);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(740, 150, 221, 287));
        GPS_PTA_Acc = new QVBoxLayout(widget1);
        GPS_PTA_Acc->setSpacing(6);
        GPS_PTA_Acc->setContentsMargins(11, 11, 11, 11);
        GPS_PTA_Acc->setObjectName(QStringLiteral("GPS_PTA_Acc"));
        GPS_PTA_Acc->setContentsMargins(0, 0, 0, 0);
        LatLonAlt = new QHBoxLayout();
        LatLonAlt->setSpacing(6);
        LatLonAlt->setObjectName(QStringLiteral("LatLonAlt"));
        Lables = new QVBoxLayout();
        Lables->setSpacing(6);
        Lables->setObjectName(QStringLiteral("Lables"));
        label = new QLabel(widget1);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font);

        Lables->addWidget(label);

        label_2 = new QLabel(widget1);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);

        Lables->addWidget(label_2);

        label_3 = new QLabel(widget1);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);

        Lables->addWidget(label_3);


        LatLonAlt->addLayout(Lables);

        DorothyGPS = new QVBoxLayout();
        DorothyGPS->setSpacing(6);
        DorothyGPS->setObjectName(QStringLiteral("DorothyGPS"));
        latitude = new QLineEdit(widget1);
        latitude->setObjectName(QStringLiteral("latitude"));

        DorothyGPS->addWidget(latitude);

        longitude = new QLineEdit(widget1);
        longitude->setObjectName(QStringLiteral("longitude"));

        DorothyGPS->addWidget(longitude);

        altitude = new QLineEdit(widget1);
        altitude->setObjectName(QStringLiteral("altitude"));

        DorothyGPS->addWidget(altitude);


        LatLonAlt->addLayout(DorothyGPS);


        GPS_PTA_Acc->addLayout(LatLonAlt);

        line_2 = new QFrame(widget1);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        GPS_PTA_Acc->addWidget(line_2);

        PTA = new QHBoxLayout();
        PTA->setSpacing(6);
        PTA->setObjectName(QStringLiteral("PTA"));
        Lables_2 = new QVBoxLayout();
        Lables_2->setSpacing(6);
        Lables_2->setObjectName(QStringLiteral("Lables_2"));
        label_4 = new QLabel(widget1);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font);

        Lables_2->addWidget(label_4);

        label_5 = new QLabel(widget1);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font);

        Lables_2->addWidget(label_5);

        label_6 = new QLabel(widget1);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setFont(font);

        Lables_2->addWidget(label_6);


        PTA->addLayout(Lables_2);

        DorothyGPS_2 = new QVBoxLayout();
        DorothyGPS_2->setSpacing(6);
        DorothyGPS_2->setObjectName(QStringLiteral("DorothyGPS_2"));
        pressure = new QLineEdit(widget1);
        pressure->setObjectName(QStringLiteral("pressure"));

        DorothyGPS_2->addWidget(pressure);

        temperature = new QLineEdit(widget1);
        temperature->setObjectName(QStringLiteral("temperature"));

        DorothyGPS_2->addWidget(temperature);

        altitude_2 = new QLineEdit(widget1);
        altitude_2->setObjectName(QStringLiteral("altitude_2"));

        DorothyGPS_2->addWidget(altitude_2);


        PTA->addLayout(DorothyGPS_2);


        GPS_PTA_Acc->addLayout(PTA);

        line = new QFrame(widget1);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        GPS_PTA_Acc->addWidget(line);

        Acc = new QHBoxLayout();
        Acc->setSpacing(6);
        Acc->setObjectName(QStringLiteral("Acc"));
        Lables_3 = new QVBoxLayout();
        Lables_3->setSpacing(6);
        Lables_3->setObjectName(QStringLiteral("Lables_3"));
        label_7 = new QLabel(widget1);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setFont(font);

        Lables_3->addWidget(label_7);

        label_8 = new QLabel(widget1);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setFont(font);

        Lables_3->addWidget(label_8);

        label_9 = new QLabel(widget1);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setFont(font);

        Lables_3->addWidget(label_9);


        Acc->addLayout(Lables_3);

        DorothyGPS_3 = new QVBoxLayout();
        DorothyGPS_3->setSpacing(6);
        DorothyGPS_3->setObjectName(QStringLiteral("DorothyGPS_3"));
        accx = new QLineEdit(widget1);
        accx->setObjectName(QStringLiteral("accx"));

        DorothyGPS_3->addWidget(accx);

        accy = new QLineEdit(widget1);
        accy->setObjectName(QStringLiteral("accy"));

        DorothyGPS_3->addWidget(accy);

        accz = new QLineEdit(widget1);
        accz->setObjectName(QStringLiteral("accz"));

        DorothyGPS_3->addWidget(accz);


        Acc->addLayout(DorothyGPS_3);


        GPS_PTA_Acc->addLayout(Acc);

        MainWindow->setCentralWidget(widget_plot);
        layoutWidget->raise();
        Toto1->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        Toto2->raise();
        Toto3->raise();
        Toto1Color->raise();
        Toto2Color->raise();
        Toto3Color->raise();
        Dorothy->raise();
        DorothyColor->raise();
        map->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1920, 20));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "RO-OZ Ground Control Center", Q_NULLPTR));
        fileButton->setText(QApplication::translate("MainWindow", "Open File", Q_NULLPTR));
        openPort->setText(QApplication::translate("MainWindow", "OpenPort", Q_NULLPTR));
        baudList->clear();
        baudList->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "9600", Q_NULLPTR)
         << QApplication::translate("MainWindow", "19200", Q_NULLPTR)
         << QApplication::translate("MainWindow", "38400", Q_NULLPTR)
         << QApplication::translate("MainWindow", "57600", Q_NULLPTR)
         << QApplication::translate("MainWindow", "74880", Q_NULLPTR)
         << QApplication::translate("MainWindow", "115200", Q_NULLPTR)
         << QApplication::translate("MainWindow", "230400", Q_NULLPTR)
         << QApplication::translate("MainWindow", "250000", Q_NULLPTR)
        );
        searchButton->setText(QApplication::translate("MainWindow", "Search Ports", Q_NULLPTR));
        portName->setText(QString());
        readButton->setText(QApplication::translate("MainWindow", "Read", Q_NULLPTR));
        Toto1Text->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt; font-weight:600;\">TOTO 1</span></p></body></html>", Q_NULLPTR));
        Toto2Text->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt; font-weight:600;\">TOTO 2</span></p></body></html>", Q_NULLPTR));
        Toto3Text->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt; font-weight:600;\">TOTO 3</span></p></body></html>", Q_NULLPTR));
        DorothyText->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt; font-weight:600;\">Dorothy</span></p></body></html>", Q_NULLPTR));
        label_16->setText(QApplication::translate("MainWindow", "Magneto X:    ", Q_NULLPTR));
        label_17->setText(QApplication::translate("MainWindow", "Magneto Y:", Q_NULLPTR));
        label_18->setText(QApplication::translate("MainWindow", "Magneto Z:", Q_NULLPTR));
        magnetox->setText(QString());
        magnetoy->setText(QString());
        magnetoz->setText(QString());
        label_13->setText(QApplication::translate("MainWindow", "Gyro X - Roll:", Q_NULLPTR));
        label_14->setText(QApplication::translate("MainWindow", "Gyro Y - Pitch:", Q_NULLPTR));
        label_15->setText(QApplication::translate("MainWindow", "Gyro Z - Yaw:", Q_NULLPTR));
        gyrox->setText(QString());
        gyroy->setText(QString());
        gyroz->setText(QString());
        label->setText(QApplication::translate("MainWindow", "Latitude:          ", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Longitude:", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Altitude:", Q_NULLPTR));
        latitude->setText(QString());
        longitude->setText(QString());
        altitude->setText(QString());
        label_4->setText(QApplication::translate("MainWindow", "Pressure:", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "Temperature:   ", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "Altitude:", Q_NULLPTR));
        pressure->setText(QString());
        temperature->setText(QString());
        altitude_2->setText(QString());
        label_7->setText(QApplication::translate("MainWindow", "Acceleration X:", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "Acceleration Y: ", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "Acceleration Z:", Q_NULLPTR));
        accx->setText(QString());
        accy->setText(QString());
        accz->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
