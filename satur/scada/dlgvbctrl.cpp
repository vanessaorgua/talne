#include "dlgvbctrl.h"
#include "ui_dlgvbctrl.h"

#include "iodev.h"
#include <QTimer>

dlgVbCtrl::dlgVbCtrl(IoDev &source , int nValve , QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgVbCtrl),
    src(source),
    nI(nValve)
{
    ui->setupUi(this);
    ui->en_p->setCurrentIndex(src.getValue16(QString("en_p_%1").arg(nI,2,10,QChar('0')))?1:0);

    QTimer *tmr=new QTimer(this);
    tmr->setInterval(1000);
    tmr->start()            ;
    connect(tmr,SIGNAL(timeout()),this,SLOT(slotUpdate()));

    connect(ui->en_p,SIGNAL(currentIndexChanged(int)),this,SLOT(slotSet(int)));
    connect(ui->Q,SIGNAL(clicked()),this,SLOT(slotSet()));


}

dlgVbCtrl::~dlgVbCtrl()
{
    delete ui;
}

void dlgVbCtrl::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void dlgVbCtrl::slotUpdate()
{
    ui->Q->setIcon(QIcon(
            QPixmap(src.getValue16(QString("Q_%1").arg(nI,2,10,QChar('0')))
                                  ?":/butons/pict/klapan_diskrette_vert_on_na_25x26.png"
                                      :":/butons/pict/klapan_diskrette_vert_off_na_25x46.png")));

    ui->I->setChecked(src.getValue16(QString("I_%1").arg(nI,2,10,QChar('0'))));
}

void dlgVbCtrl::slotSet(int v)
{
    src.sendValue(QString("en_p_%1").arg(nI,2,10,QChar('0')),qint16(-v));
}

void dlgVbCtrl::slotSet()
{
    qint16 v = src.getValue16(QString("Q_%1").arg(nI,2,10,QChar('0')))?0:-1;
    qDebug() << v;
    src.sendValue(QString("Q_%1").arg(nI,2,10,QChar('0')),v);
}


