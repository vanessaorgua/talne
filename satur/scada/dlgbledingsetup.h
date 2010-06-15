#ifndef DLGBLEDINGSETUP_H
#define DLGBLEDINGSETUP_H

#include <QDialog>

#include <QTime>
class IoDev;
class QTimeEdit;
class QComboBox;

#include <QVector>

namespace Ui {
    class dlgBledingSetup;
}

class dlgBledingSetup : public QDialog {
    Q_OBJECT
public:
    dlgBledingSetup(IoDev &source, QWidget *parent = 0);
    ~dlgBledingSetup();

public slots:
    //void slotUpdate(); // в цьому слоті буде поновлюватися інформація на картинці
    void slotSet(int);
    void slotSet(QTime);
    void updateList();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::dlgBledingSetup *ui;
    IoDev &src;

    QVector<QTimeEdit*> te_m,te_p;
    QVector<QComboBox*> cb_e,cb_k;

};

#endif // DLGBLEDINGSETUP_H
