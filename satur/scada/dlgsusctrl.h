#ifndef DLGSUSCTRL_H
#define DLGSUSCTRL_H

#include <QDialog>

class IoDev;

namespace Ui {
    class dlgSusCtrl;
}

class dlgSusCtrl : public QDialog {
    Q_OBJECT
public:
    dlgSusCtrl(IoDev &source, QWidget *parent = 0);
    ~dlgSusCtrl();

protected:
    void changeEvent(QEvent *e);
public slots:
    void slotUpdate();
    void slotSendDouble(double);
    void slotSendBool(int);

private:
    Ui::dlgSusCtrl *ui;
    IoDev &src;
};

#endif // DLGSUSCTRL_H
