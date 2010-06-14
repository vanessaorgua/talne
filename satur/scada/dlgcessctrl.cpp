#include "dlgcessctrl.h"
#include "ui_dlgcessctrl.h"

#include "iodev.h"
#include <QTimer>


dlgCessCtrl::dlgCessCtrl(IoDev &source, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgCessCtrl),
    src(source)
{
    ui->setupUi(this);

    ui->s_SP_max->setValue(src.getValue16("V_26_max"));
    ui->s_SP_min->setValue(src.getValue16("V_26_min"));

    ui->s_sSP_max->setValue(src.getValueScaled("V_26_max"));
    ui->s_sSP_min->setValue(src.getValueScaled("V_26_min"));

    ui->s_V_26_tz->setTime(QTime().addSecs((src.getValue32("V_26_tz")/1000)));

    ui->s_Am_Q_09->setCurrentIndex(src.getValue16("Am_Q_09"));
    ui->s_Q_09->setCurrentIndex(src.getValue16("Q_09")?1:0);
    ui->s_Q_09->blockSignals(ui->s_Am_Q_09->currentIndex());

    connect(ui->s_SP_max,SIGNAL(valueChanged(int)),this,SLOT(slotSetSl(int)));
    connect(ui->s_SP_min,SIGNAL(valueChanged(int)),this,SLOT(slotSetSl(int)));
    connect(ui->s_sSP_max,SIGNAL(valueChanged(double)),this,SLOT(slotSetDs(double)));
    connect(ui->s_sSP_min,SIGNAL(valueChanged(double)),this,SLOT(slotSetDs(double)));
    connect(ui->s_V_26_tz,SIGNAL(timeChanged(QTime)),this,SLOT(slotSetTime(QTime)));

    connect(ui->s_Am_Q_09,SIGNAL(currentIndexChanged(int)),this,SLOT(slotSetBool(int)));
    connect(ui->s_Q_09,SIGNAL(currentIndexChanged(int)),this,SLOT(slotSetBool(int)));

    QTimer *tmr = new QTimer(this);
    tmr->setInterval(1000);
    tmr->start();
    connect(tmr,SIGNAL(timeout()),this,SLOT(slotUpdate()));

}

dlgCessCtrl::~dlgCessCtrl()
{
    delete ui;
}

void dlgCessCtrl::changeEvent(QEvent *e)
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
void dlgCessCtrl::slotUpdate() // в цьому слоті буде поновлюватися інформація на картинці
{
    ui->s_pV->setValue(src.getValueFloat("V_26"));
    ui->s_lV->setText(QString("%1").arg(src.getValueScaled("V_26"),3,'f',0));
    ui->s_I_09->setChecked(src.getValue16("I_09"));
    ui->s_I_11->setChecked(src.getValue16("I_11"));

    ui->s_V_26_t->setText(QTime(0,0,0,0).addMSecs(src.getValue32("V_26_t")).toString("hh:mm:ss"));

    if(ui->s_Am_Q_09->currentIndex())
    {
        ui->s_Q_09->setCurrentIndex(src.getValue16("Q_09")?1:0);
    }
}

void dlgCessCtrl::slotSetSl(int v)
{
    double td=v;
//    qDebug() << sender()->objectName();

    if(sender()->objectName()=="s_SP_min")
    {
        src.sendValue("V_26_min",qint16(v));
        ui->s_sSP_min->blockSignals(true);
        ui->s_sSP_min->setValue(td/4000.0*(src.scaleFull("V_26_min")-src.scaleZero("V_26_min"))+src.scaleZero("V_26_min"));
        ui->s_sSP_min->blockSignals(false);
//        qDebug() << "V_26_min" << src.scaleZero("V_26_min") << src.scaleFull("V_26_min");

    }
    else
    {
        src.sendValue("V_26_max",qint16(v));
        ui->s_sSP_max->blockSignals(true);
        ui->s_sSP_max->setValue(td/4000.0*(src.scaleFull("V_26_max")-src.scaleZero("V_26_max"))+src.scaleZero("V_26_max"));
        ui->s_sSP_max->blockSignals(false);
    }
}

void dlgCessCtrl::slotSetDs(double v)
{
    if(sender()->objectName()=="s_sSP_min")
    {
        src.sendValueScaled("V_26_min",v);
        ui->s_SP_min->blockSignals(true);
        ui->s_SP_min->setValue((v-src.scaleZero("V_26_min"))/(src.scaleFull("V_26_min")-src.scaleZero("V_26_min"))*4000.0);
        ui->s_SP_min->blockSignals(false);
    }
    else
    {
        src.sendValueScaled("V_26_max",v);
        ui->s_SP_max->blockSignals(true);
        ui->s_SP_max->setValue((v-src.scaleZero("V_26_max"))/(src.scaleFull("V_26_max")-src.scaleZero("V_26_max"))*4000.0);
        ui->s_SP_max->blockSignals(false);
    }
}


void dlgCessCtrl::slotSetBool(int v)
{
    src.sendValue(sender()->objectName().right(sender()->objectName().size()-2),qint16(-v)); // відправити значення

    if(sender()->objectName()=="s_Am_Q_09") // заблокувати при необхідності управління
    {
        ui->s_Q_09->blockSignals(ui->s_Am_Q_09->currentIndex());
    }
}

void dlgCessCtrl::slotSetTime(QTime v)
{
   qint32 t= QTime(0,0,0,0).msecsTo(v);

   src.sendValue("V_26_tz",t);
}

