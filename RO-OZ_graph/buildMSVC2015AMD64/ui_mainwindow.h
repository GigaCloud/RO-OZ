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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "../../qcustomplot.h"

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
    QHBoxLayout *horizontalLayout;
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
    QWidget *widget;
    QVBoxLayout *DorothyGPS;
    QLineEdit *latitude;
    QLineEdit *longitude;
    QLineEdit *altitude;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1920, 1080);
        MainWindow->setMinimumSize(QSize(1920, 1080));
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
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        openPort = new QPushButton(layoutWidget1);
        openPort->setObjectName(QStringLiteral("openPort"));

        horizontalLayout->addWidget(openPort);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        comList = new QComboBox(layoutWidget1);
        comList->setObjectName(QStringLiteral("comList"));

        verticalLayout->addWidget(comList);

        baudList = new QComboBox(layoutWidget1);
        baudList->setObjectName(QStringLiteral("baudList"));

        verticalLayout->addWidget(baudList);


        horizontalLayout->addLayout(verticalLayout);

        searchButton = new QPushButton(layoutWidget1);
        searchButton->setObjectName(QStringLiteral("searchButton"));

        horizontalLayout->addWidget(searchButton);

        portName = new QLineEdit(layoutWidget1);
        portName->setObjectName(QStringLiteral("portName"));

        horizontalLayout->addWidget(portName);

        readButton = new QPushButton(layoutWidget1);
        readButton->setObjectName(QStringLiteral("readButton"));

        horizontalLayout->addWidget(readButton);

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
        Toto1Text->setGeometry(QRect(0, 0, 81, 31));
        Toto1Text->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Toto1Text->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Toto1Text->setAcceptRichText(true);
        Toto1Text->setTextInteractionFlags(Qt::NoTextInteraction);
        Toto2Color = new QWidget(widget_plot);
        Toto2Color->setObjectName(QStringLiteral("Toto2Color"));
        Toto2Color->setGeometry(QRect(230, 950, 101, 31));
        Toto2Text = new QTextBrowser(Toto2Color);
        Toto2Text->setObjectName(QStringLiteral("Toto2Text"));
        Toto2Text->setGeometry(QRect(0, 0, 81, 31));
        Toto2Text->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Toto2Text->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Toto2Text->setAcceptRichText(true);
        Toto2Text->setTextInteractionFlags(Qt::NoTextInteraction);
        Toto3Color = new QWidget(widget_plot);
        Toto3Color->setObjectName(QStringLiteral("Toto3Color"));
        Toto3Color->setGeometry(QRect(1590, 480, 101, 31));
        Toto3Text = new QTextBrowser(Toto3Color);
        Toto3Text->setObjectName(QStringLiteral("Toto3Text"));
        Toto3Text->setGeometry(QRect(0, 0, 81, 31));
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
        DorothyText->setGeometry(QRect(0, 0, 91, 31));
        DorothyText->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        DorothyText->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        DorothyText->setAcceptRichText(true);
        DorothyText->setTextInteractionFlags(Qt::NoTextInteraction);
        widget = new QWidget(widget_plot);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(1030, 290, 135, 83));
        DorothyGPS = new QVBoxLayout(widget);
        DorothyGPS->setSpacing(6);
        DorothyGPS->setContentsMargins(11, 11, 11, 11);
        DorothyGPS->setObjectName(QStringLiteral("DorothyGPS"));
        DorothyGPS->setContentsMargins(0, 0, 0, 0);
        latitude = new QLineEdit(widget);
        latitude->setObjectName(QStringLiteral("latitude"));

        DorothyGPS->addWidget(latitude);

        longitude = new QLineEdit(widget);
        longitude->setObjectName(QStringLiteral("longitude"));

        DorothyGPS->addWidget(longitude);

        altitude = new QLineEdit(widget);
        altitude->setObjectName(QStringLiteral("altitude"));

        DorothyGPS->addWidget(altitude);

        MainWindow->setCentralWidget(widget_plot);
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
        latitude->raise();
        longitude->raise();
        altitude->raise();
        latitude->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1920, 23));
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
        latitude->setText(QString());
        longitude->setText(QString());
        altitude->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
