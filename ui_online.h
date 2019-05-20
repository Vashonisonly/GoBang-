/********************************************************************************
** Form generated from reading UI file 'online.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ONLINE_H
#define UI_ONLINE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Online
{
public:
    QTextBrowser *textBrowser;
    QLineEdit *lineEdit;
    QPushButton *sendBtn;
    QPushButton *returnBtn;
    QListWidget *listWidget;
    QLabel *blackLabel;
    QLabel *whiteLabel;
    QLabel *label;
    QLabel *fireLabel;
    QLabel *label_2;
    QPushButton *pushButton;
    QPushButton *giveUpBtn;
    QPushButton *regretBtn;
    QPushButton *forPeaceBtn;
    QPushButton *creatRoom;
    QPushButton *joinRoom;

    void setupUi(QWidget *Online)
    {
        if (Online->objectName().isEmpty())
            Online->setObjectName(QString::fromUtf8("Online"));
        Online->resize(1200, 704);
        textBrowser = new QTextBrowser(Online);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(800, 420, 246, 211));
        textBrowser->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 59, 32,150);\n"
"border-color: rgb(85,59,32,150);"));
        textBrowser->setLineWidth(1);
        lineEdit = new QLineEdit(Online);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(800, 650, 191, 31));
        lineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 59, 32,150);\n"
"border-color: rgb(85,59,32,150);"));
        sendBtn = new QPushButton(Online);
        sendBtn->setObjectName(QString::fromUtf8("sendBtn"));
        sendBtn->setGeometry(QRect(990, 650, 61, 31));
        sendBtn->setStyleSheet(QString::fromUtf8("background-color: rgb(149, 134, 118);"));
        returnBtn = new QPushButton(Online);
        returnBtn->setObjectName(QString::fromUtf8("returnBtn"));
        returnBtn->setGeometry(QRect(30, 320, 151, 61));
        returnBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/images/Return.png);"));
        listWidget = new QListWidget(Online);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(800, 0, 246, 191));
        listWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 59, 32);"));
        blackLabel = new QLabel(Online);
        blackLabel->setObjectName(QString::fromUtf8("blackLabel"));
        blackLabel->setGeometry(QRect(850, 100, 54, 51));
        blackLabel->setStyleSheet(QString::fromUtf8("border-image: url(:/images/black.png);"));
        whiteLabel = new QLabel(Online);
        whiteLabel->setObjectName(QString::fromUtf8("whiteLabel"));
        whiteLabel->setGeometry(QRect(940, 100, 54, 51));
        whiteLabel->setStyleSheet(QString::fromUtf8("border-image: url(:/images/white.png);"));
        label = new QLabel(Online);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(840, 20, 171, 51));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\232\266\344\271\246"));
        font.setPointSize(14);
        label->setFont(font);
        fireLabel = new QLabel(Online);
        fireLabel->setObjectName(QString::fromUtf8("fireLabel"));
        fireLabel->setGeometry(QRect(806, 31, 141, 131));
        fireLabel->setStyleSheet(QString::fromUtf8("border-image: url(:/images/fire.png);"));
        label_2 = new QLabel(Online);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(899, 31, 135, 128));
        label_2->setStyleSheet(QString::fromUtf8("border-image: url(:/images/fire.png);"));
        pushButton = new QPushButton(Online);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(30, 200, 151, 61));
        pushButton->setStyleSheet(QString::fromUtf8("border-image: url(:/images/Readly.png);"));
        giveUpBtn = new QPushButton(Online);
        giveUpBtn->setObjectName(QString::fromUtf8("giveUpBtn"));
        giveUpBtn->setGeometry(QRect(400, 610, 131, 41));
        giveUpBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/images/Fall.png);"));
        regretBtn = new QPushButton(Online);
        regretBtn->setObjectName(QString::fromUtf8("regretBtn"));
        regretBtn->setGeometry(QRect(550, 610, 131, 41));
        regretBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/images/Regret.png);"));
        forPeaceBtn = new QPushButton(Online);
        forPeaceBtn->setObjectName(QString::fromUtf8("forPeaceBtn"));
        forPeaceBtn->setGeometry(QRect(250, 610, 131, 41));
        forPeaceBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/images/ForPlace.png);"));
        creatRoom = new QPushButton(Online);
        creatRoom->setObjectName(QString::fromUtf8("creatRoom"));
        creatRoom->setGeometry(QRect(805, 382, 111, 38));
        joinRoom = new QPushButton(Online);
        joinRoom->setObjectName(QString::fromUtf8("joinRoom"));
        joinRoom->setGeometry(QRect(925, 382, 111, 38));

        retranslateUi(Online);

        QMetaObject::connectSlotsByName(Online);
    } // setupUi

    void retranslateUi(QWidget *Online)
    {
        Online->setWindowTitle(QApplication::translate("Online", "Form", nullptr));
        textBrowser->setHtml(QApplication::translate("Online", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; font-weight:600; font-style:italic; text-decoration: underline; color:#9a3810;\">\346\210\221\347\210\261\345\260\217\345\200\251\345\200\251\357\274\201</span></p></body></html>", nullptr));
        sendBtn->setText(QApplication::translate("Online", "\345\217\221\351\200\201", nullptr));
        returnBtn->setText(QString());
        blackLabel->setText(QString());
        whiteLabel->setText(QString());
        label->setText(QApplication::translate("Online", "\345\205\210\345\207\206\345\244\207\350\200\205\351\273\221\346\243\213\345\205\210\346\211\213\357\274\201", nullptr));
        fireLabel->setText(QString());
        label_2->setText(QString());
        pushButton->setText(QString());
        giveUpBtn->setText(QString());
        regretBtn->setText(QString());
        forPeaceBtn->setText(QString());
        creatRoom->setText(QApplication::translate("Online", "\345\210\233\345\273\272\346\210\277\351\227\264", nullptr));
        joinRoom->setText(QApplication::translate("Online", "\345\212\240\345\205\245\346\210\277\351\227\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Online: public Ui_Online {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ONLINE_H
