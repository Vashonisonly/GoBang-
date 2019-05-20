#ifndef DEPLOY_H
#define DEPLOY_H

#include <QWidget>

namespace Ui {
class Deploy;
}

class Deploy : public QWidget
{
    Q_OBJECT

public:
    explicit Deploy(QWidget *parent = nullptr);
    ~Deploy();

    void setBackGround();
signals:
    void valueChanged(int);
    void closed();

public slots:
    void returnBtnClicked();
private:
    Ui::Deploy *ui;
};

#endif // DEPLOY_H
