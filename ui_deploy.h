/********************************************************************************
** Form generated from reading UI file 'deploy.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEPLOY_H
#define UI_DEPLOY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Deploy
{
public:
    QPushButton *effectBtn;
    QPushButton *musicBtn;
    QPushButton *backGroundBtn;
    QPushButton *returnBtn;
    QSlider *horizontalSlider;

    void setupUi(QWidget *Deploy)
    {
        if (Deploy->objectName().isEmpty())
            Deploy->setObjectName(QString::fromUtf8("Deploy"));
        Deploy->resize(1200, 740);
        effectBtn = new QPushButton(Deploy);
        effectBtn->setObjectName(QString::fromUtf8("effectBtn"));
        effectBtn->setGeometry(QRect(530, 50, 151, 61));
        musicBtn = new QPushButton(Deploy);
        musicBtn->setObjectName(QString::fromUtf8("musicBtn"));
        musicBtn->setGeometry(QRect(530, 210, 151, 61));
        backGroundBtn = new QPushButton(Deploy);
        backGroundBtn->setObjectName(QString::fromUtf8("backGroundBtn"));
        backGroundBtn->setGeometry(QRect(530, 360, 151, 61));
        returnBtn = new QPushButton(Deploy);
        returnBtn->setObjectName(QString::fromUtf8("returnBtn"));
        returnBtn->setGeometry(QRect(530, 510, 151, 61));
        horizontalSlider = new QSlider(Deploy);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(530, 120, 160, 22));
        horizontalSlider->setValue(30);
        horizontalSlider->setOrientation(Qt::Horizontal);

        retranslateUi(Deploy);

        QMetaObject::connectSlotsByName(Deploy);
    } // setupUi

    void retranslateUi(QWidget *Deploy)
    {
        Deploy->setWindowTitle(QApplication::translate("Deploy", "Form", nullptr));
        effectBtn->setText(QApplication::translate("Deploy", "\346\214\211\351\224\256\351\237\263\351\207\217", nullptr));
        musicBtn->setText(QApplication::translate("Deploy", "\351\200\211\346\213\251\351\237\263\344\271\220", nullptr));
        backGroundBtn->setText(QApplication::translate("Deploy", "\351\200\211\346\213\251\350\203\214\346\231\257", nullptr));
        returnBtn->setText(QApplication::translate("Deploy", "\350\277\224\345\233\236\344\270\273\350\217\234\345\215\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Deploy: public Ui_Deploy {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEPLOY_H
