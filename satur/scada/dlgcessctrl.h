#ifndef DLGCESSCTRL_H
#define DLGCESSCTRL_H

#include <QDialog>

class IoDev;
#include <QTime>

namespace Ui {
    class dlgCessCtrl;
}

class dlgCessCtrl : public QDialog {
    Q_OBJECT
public:
    dlgCessCtrl(IoDev &source, QWidget *parent = 0);
    ~dlgCessCtrl();
public slots:
    void slotUpdate(); // в цьому слоті буде поновлюватися інформація на картинці
    void slotSetSl(int);
    void slotSetDs(double);
    void slotSetBool(int);
    void slotSetTime(QTime);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::dlgCessCtrl *ui;
    IoDev &src;
};

#endif // DLGCESSCTRL_H
