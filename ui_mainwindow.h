/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTextBrowser *rulesBrowser;
    QPushButton *playButton;
    QPushButton *restartButton;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QSpinBox *spinBoxPlayers;
    QLineEdit *lineEditPlayerNames;
    QLabel *label_4;
    QTextBrowser *resultsBrowser;
    QTextBrowser *top5playersBrowser;
    QSpinBox *spinBoxCards;
    QLCDNumber *lcdNumberMin;
    QLabel *label_6;
    QLabel *label_7;
    QTextBrowser *roundInfoBrowser;
    QLabel *label_8;
    QLabel *label_9;
    QLCDNumber *lcdNumberSec;
    QLabel *label_10;
    QLabel *label_11;
    QPushButton *pushButtonClose;
    QLabel *label_5;
    QTextBrowser *turnBrowser;
    QPushButton *newturnButton;
    QGraphicsView *graphicsView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1104, 653);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        rulesBrowser = new QTextBrowser(centralwidget);
        rulesBrowser->setObjectName(QString::fromUtf8("rulesBrowser"));
        rulesBrowser->setGeometry(QRect(15, 1, 311, 141));
        playButton = new QPushButton(centralwidget);
        playButton->setObjectName(QString::fromUtf8("playButton"));
        playButton->setGeometry(QRect(380, 10, 181, 31));
        restartButton = new QPushButton(centralwidget);
        restartButton->setObjectName(QString::fromUtf8("restartButton"));
        restartButton->setGeometry(QRect(380, 50, 181, 31));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(650, 0, 111, 20));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(650, 30, 131, 17));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(650, 60, 111, 17));
        spinBoxPlayers = new QSpinBox(centralwidget);
        spinBoxPlayers->setObjectName(QString::fromUtf8("spinBoxPlayers"));
        spinBoxPlayers->setGeometry(QRect(780, 30, 45, 26));
        lineEditPlayerNames = new QLineEdit(centralwidget);
        lineEditPlayerNames->setObjectName(QString::fromUtf8("lineEditPlayerNames"));
        lineEditPlayerNames->setGeometry(QRect(780, 60, 113, 21));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(840, 370, 101, 17));
        QFont font;
        font.setPointSize(11);
        label_4->setFont(font);
        resultsBrowser = new QTextBrowser(centralwidget);
        resultsBrowser->setObjectName(QString::fromUtf8("resultsBrowser"));
        resultsBrowser->setGeometry(QRect(640, 470, 181, 131));
        top5playersBrowser = new QTextBrowser(centralwidget);
        top5playersBrowser->setObjectName(QString::fromUtf8("top5playersBrowser"));
        top5playersBrowser->setGeometry(QRect(850, 470, 171, 131));
        spinBoxCards = new QSpinBox(centralwidget);
        spinBoxCards->setObjectName(QString::fromUtf8("spinBoxCards"));
        spinBoxCards->setGeometry(QRect(780, 0, 45, 26));
        lcdNumberMin = new QLCDNumber(centralwidget);
        lcdNumberMin->setObjectName(QString::fromUtf8("lcdNumberMin"));
        lcdNumberMin->setGeometry(QRect(940, 390, 61, 21));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(QFont::Weight::Normal);
        lcdNumberMin->setFont(font1);
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(640, 120, 400, 20));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(850, 450, 171, 17));
        roundInfoBrowser = new QTextBrowser(centralwidget);
        roundInfoBrowser->setObjectName(QString::fromUtf8("roundInfoBrowser"));
        roundInfoBrowser->setGeometry(QRect(640, 390, 181, 41));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(640, 450, 181, 17));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(640, 370, 181, 17));
        lcdNumberSec = new QLCDNumber(centralwidget);
        lcdNumberSec->setObjectName(QString::fromUtf8("lcdNumberSec"));
        lcdNumberSec->setGeometry(QRect(940, 420, 64, 23));
        lcdNumberSec->setFont(font1);
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(840, 390, 62, 17));
        label_11 = new QLabel(centralwidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(840, 420, 62, 17));
        pushButtonClose = new QPushButton(centralwidget);
        pushButtonClose->setObjectName(QString::fromUtf8("pushButtonClose"));
        pushButtonClose->setGeometry(QRect(950, 10, 121, 41));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(650, 90, 51, 17));
        turnBrowser = new QTextBrowser(centralwidget);
        turnBrowser->setObjectName(QString::fromUtf8("turnBrowser"));
        turnBrowser->setGeometry(QRect(780, 90, 111, 31));
        newturnButton = new QPushButton(centralwidget);
        newturnButton->setObjectName(QString::fromUtf8("newturnButton"));
        newturnButton->setGeometry(QRect(380, 90, 181, 41));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(640, 160, 400, 200));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1104, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(pushButtonClose, SIGNAL(clicked()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        playButton->setText(QCoreApplication::translate("MainWindow", "PLAY!", nullptr));
        restartButton->setText(QCoreApplication::translate("MainWindow", "RESTART", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Amount of cards:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Amount of players:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Player names:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Time passed:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "State of game:", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Top 5 players of all time:", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Results:", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Round/general info:", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Minutes", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Seconds", nullptr));
        pushButtonClose->setText(QCoreApplication::translate("MainWindow", "Close", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "In turn:", nullptr));
        newturnButton->setText(QCoreApplication::translate("MainWindow", "SWITCH TURN", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
