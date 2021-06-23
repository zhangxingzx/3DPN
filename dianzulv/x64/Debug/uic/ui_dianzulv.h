/********************************************************************************
** Form generated from reading UI file 'dianzulv.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIANZULV_H
#define UI_DIANZULV_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <qchartview.h>

QT_BEGIN_NAMESPACE

class Ui_dianzulvClass
{
public:
    QWidget *centralWidget;
    QChartView *widget;
    QLineEdit *lineEdit_min_U;
    QLineEdit *lineEdit_max_U;
    QLineEdit *lineEdit_avg_U;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit_avg_2;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *lineEdit_min_P;
    QLabel *label_6;
    QLineEdit *lineEdit_max_P;
    QLabel *label_7;
    QLineEdit *lineEdit_avg_P;
    QChartView *widget_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *dianzulvClass)
    {
        if (dianzulvClass->objectName().isEmpty())
            dianzulvClass->setObjectName(QString::fromUtf8("dianzulvClass"));
        dianzulvClass->resize(990, 355);
        centralWidget = new QWidget(dianzulvClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        widget = new QChartView(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(20, 40, 471, 281));
        lineEdit_min_U = new QLineEdit(centralWidget);
        lineEdit_min_U->setObjectName(QString::fromUtf8("lineEdit_min_U"));
        lineEdit_min_U->setGeometry(QRect(80, 10, 61, 20));
        lineEdit_max_U = new QLineEdit(centralWidget);
        lineEdit_max_U->setObjectName(QString::fromUtf8("lineEdit_max_U"));
        lineEdit_max_U->setGeometry(QRect(190, 10, 61, 20));
        lineEdit_avg_U = new QLineEdit(centralWidget);
        lineEdit_avg_U->setObjectName(QString::fromUtf8("lineEdit_avg_U"));
        lineEdit_avg_U->setGeometry(QRect(300, 10, 61, 20));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 71, 16));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(150, 10, 54, 12));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(260, 10, 54, 12));
        lineEdit_avg_2 = new QLineEdit(centralWidget);
        lineEdit_avg_2->setObjectName(QString::fromUtf8("lineEdit_avg_2"));
        lineEdit_avg_2->setGeometry(QRect(440, 10, 51, 20));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(370, 10, 71, 16));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(570, 10, 71, 16));
        lineEdit_min_P = new QLineEdit(centralWidget);
        lineEdit_min_P->setObjectName(QString::fromUtf8("lineEdit_min_P"));
        lineEdit_min_P->setGeometry(QRect(650, 10, 61, 20));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(720, 10, 54, 12));
        lineEdit_max_P = new QLineEdit(centralWidget);
        lineEdit_max_P->setObjectName(QString::fromUtf8("lineEdit_max_P"));
        lineEdit_max_P->setGeometry(QRect(770, 10, 61, 20));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(840, 10, 54, 12));
        lineEdit_avg_P = new QLineEdit(centralWidget);
        lineEdit_avg_P->setObjectName(QString::fromUtf8("lineEdit_avg_P"));
        lineEdit_avg_P->setGeometry(QRect(900, 10, 61, 20));
        widget_2 = new QChartView(centralWidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(520, 40, 461, 281));
        dianzulvClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(dianzulvClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 990, 23));
        dianzulvClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(dianzulvClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        dianzulvClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(dianzulvClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        dianzulvClass->setStatusBar(statusBar);

        retranslateUi(dianzulvClass);

        QMetaObject::connectSlotsByName(dianzulvClass);
    } // setupUi

    void retranslateUi(QMainWindow *dianzulvClass)
    {
        dianzulvClass->setWindowTitle(QApplication::translate("dianzulvClass", "dianzulv", nullptr));
        label->setText(QApplication::translate("dianzulvClass", "\347\224\265\345\216\213\346\234\200\345\260\217\345\200\274", nullptr));
        label_2->setText(QApplication::translate("dianzulvClass", "\346\234\200\345\244\247\345\200\274", nullptr));
        label_3->setText(QApplication::translate("dianzulvClass", "\345\271\263\345\235\207\345\200\274", nullptr));
        label_4->setText(QApplication::translate("dianzulvClass", "\347\241\205\347\211\207PN\347\261\273\345\236\213", nullptr));
        label_5->setText(QApplication::translate("dianzulvClass", "\347\224\265\351\230\273\347\216\207\346\234\200\345\260\217\345\200\274", nullptr));
        label_6->setText(QApplication::translate("dianzulvClass", "\346\234\200\345\244\247\345\200\274", nullptr));
        label_7->setText(QApplication::translate("dianzulvClass", "\345\271\263\345\235\207\345\200\274", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dianzulvClass: public Ui_dianzulvClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIANZULV_H
