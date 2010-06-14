#ifndef DLGPUMPCTRL_H
#define DLGPUMPCTRL_H

#include <QDialog>

class IoDev;

namespace Ui {
    class dlgPumpCtrl;
}


namespace Pc
{
    enum iX{
        V = 0,
        I = 1,
        Q = 2,
        Am = 3,
        Min = 4,
        Max = 5
    };
}

class dlgPumpCtrl : public QDialog {
    Q_OBJECT
public:
    dlgPumpCtrl(IoDev &source, QStringList &tags, QWidget *parent = 0);
    ~dlgPumpCtrl();

protected:
    void changeEvent(QEvent *e);
public slots:
    void slotUpdate(); // в цьому слоті буде поновлюватися інформація на картинці
    void slotSetSl(int);
    void slotSetDs(double);
    void slotSetBool(int);

private:
    Ui::dlgPumpCtrl *ui;
    QStringList &t;
    IoDev &src;

};

#endif // DLGPUMPCTRL_H
