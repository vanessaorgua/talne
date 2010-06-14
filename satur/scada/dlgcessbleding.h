#ifndef DLGCESSBLEDING_H
#define DLGCESSBLEDING_H

#include <QDialog>
#include <QTime>

class IoDev;

namespace Ui {
    class dlgCessBleding;
}

class dlgCessBleding : public QDialog {
    Q_OBJECT
public:
    dlgCessBleding(IoDev &source, QWidget *parent = 0);
    ~dlgCessBleding();

public slots:
    void slotUpdate(); // в цьому слоті буде поновлюватися інформація на картинці
    void slotSet(int);
    void slotSet(double);
    void slotSet(QTime);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::dlgCessBleding *ui;
    IoDev &src;
};

#endif // DLGCESSBLEDING_H
