#ifndef __MNEMO_H__
#define __MNEMO_H__

#include <QLabel>
#include <QVector>

class TrendChart;
class IoNetClient;
class QCheckBox;
class QLineEdit;
class QLineEdit;
class QCheckBox;
class QProgressBar;
class QPushButton;

class TrendChart;

namespace Ui {
    class mnemo;
}

class Mnemo: public QLabel
{
    Q_OBJECT
public:
    Mnemo(IoNetClient &src, QWidget *p=NULL);
    ~Mnemo();

public slots:
    void updateDataRaw(); // слот обновляє дані на мнемосхемі
    void updateDataScaled(); // слот обновляє дані на мнемосхемі
    void updateTrendChart(); // поновлення графіків
    void slotCallReg();
    void slotCallPumpCtrl();
    void slotCallQ09();
    void slotCallQ10();
    void slotCallX_17();
    void slotCallVb();
private:
    Ui::mnemo *m_ui;
    IoNetClient &s;


    QVector<QLineEdit*> le;
    QVector<QCheckBox*> cb;

    QVector<QLineEdit*> le_X;
    QVector<QProgressBar*> pb;

    QVector<TrendChart*> trc;
    QVector<QPushButton*> s_cI;
    QVector<QStringList> trChTags;
};

#endif
