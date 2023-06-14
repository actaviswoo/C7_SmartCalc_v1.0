/********************************************************************************
** Form generated from reading UI file 'creditwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREDITWINDOW_H
#define UI_CREDITWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_CreditWindow
{
public:
    QDoubleSpinBox *doubleSpinBox_1;
    QDoubleSpinBox *doubleSpinBox_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QSpinBox *spinBox;

    void setupUi(QDialog *CreditWindow)
    {
        if (CreditWindow->objectName().isEmpty())
            CreditWindow->setObjectName(QString::fromUtf8("CreditWindow"));
        CreditWindow->resize(494, 373);
        doubleSpinBox_1 = new QDoubleSpinBox(CreditWindow);
        doubleSpinBox_1->setObjectName(QString::fromUtf8("doubleSpinBox_1"));
        doubleSpinBox_1->setGeometry(QRect(30, 50, 181, 21));
        doubleSpinBox_1->setMinimum(1000.000000000000000);
        doubleSpinBox_1->setMaximum(1000000000.000000000000000);
        doubleSpinBox_1->setSingleStep(1000.000000000000000);
        doubleSpinBox_2 = new QDoubleSpinBox(CreditWindow);
        doubleSpinBox_2->setObjectName(QString::fromUtf8("doubleSpinBox_2"));
        doubleSpinBox_2->setGeometry(QRect(30, 100, 181, 21));
        doubleSpinBox_2->setMinimum(1.000000000000000);
        doubleSpinBox_2->setMaximum(99.989999999999995);
        label = new QLabel(CreditWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 190, 71, 31));
        label_2 = new QLabel(CreditWindow);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 240, 71, 31));
        label_3 = new QLabel(CreditWindow);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 290, 71, 31));
        spinBox = new QSpinBox(CreditWindow);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(30, 150, 181, 22));
        spinBox->setMinimum(1);
        spinBox->setMaximum(360);

        retranslateUi(CreditWindow);

        QMetaObject::connectSlotsByName(CreditWindow);
    } // setupUi

    void retranslateUi(QDialog *CreditWindow)
    {
        CreditWindow->setWindowTitle(QCoreApplication::translate("CreditWindow", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("CreditWindow", "TextLabel", nullptr));
        label_2->setText(QCoreApplication::translate("CreditWindow", "TextLabel", nullptr));
        label_3->setText(QCoreApplication::translate("CreditWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreditWindow: public Ui_CreditWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREDITWINDOW_H
