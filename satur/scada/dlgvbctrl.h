#ifndef DLGVBCTRL_H
#define DLGVBCTRL_H

#include <QDialog>

class IoDev;

namespace Ui {
    class dlgVbCtrl;
}

class dlgVbCtrl : public QDialog {
    Q_OBJECT
public:
    dlgVbCtrl(IoDev &source , int nValve = 0, QWidget *parent = 0);
    ~dlgVbCtrl();

public slots:
    void slotUpdate();
    void slotSet(int);
    void slotSet();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::dlgVbCtrl *ui;
    IoDev &src;
    int nI;
};

#endif // DLGVBCTRL_H
