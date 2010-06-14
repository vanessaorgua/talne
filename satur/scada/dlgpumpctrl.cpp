#include "dlgpumpctrl.h"
#include "ui_dlgpumpctrl.h"
#include "iodev.h"
#include <QTimer>

#include <QDebug>

dlgPumpCtrl::dlgPumpCtrl(IoDev &source, QStringList &tags,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgPumpCtrl),
    src(source),
    t(tags)
{
    ui->setupUi(this);
    // ініціалізувати все
    ui->s_SP_max->setValue(src.getValue16(t[Pc::Max]));
    ui->s_SP_min->setValue(src.getValue16(t[Pc::Min]));
    ui->s_sSP_max->setValue(src.getValueScaled(t[Pc::Max]));
    ui->s_sSP_min->setValue(src.getValueScaled(t[Pc::Min]));

    ui->s_AM->setCurrentIndex(src.getValue16(t[Pc::Am])?1:0);
    ui->s_R_M->setCurrentIndex(src.getValue16(t[Pc::Q])?1:0);

    connect(ui->s_SP_max,SIGNAL(valueChanged(int)),this,SLOT(slotSetSl(int)));
    connect(ui->s_SP_min,SIGNAL(valueChanged(int)),this,SLOT(slotSetSl(int)));
    connect(ui->s_sSP_max,SIGNAL(valueChanged(double)),this,SLOT(slotSetDs(double)));
    connect(ui->s_sSP_min,SIGNAL(valueChanged(double)),this,SLOT(slotSetDs(double)));

    connect(ui->s_AM,SIGNAL(currentIndexChanged(int)),this,SLOT(slotSetBool(int)));
    connect(ui->s_R_M,SIGNAL(currentIndexChanged(int)),this,SLOT(slotSetBool(int)));
    ui->s_R_M->blockSignals(ui->s_AM->currentIndex());

    QTimer *tmr = new QTimer(this);
    tmr->setInterval(1000);
    tmr->start();
    connect(tmr,SIGNAL(timeout()),this,SLOT(slotUpdate()));
}

dlgPumpCtrl::~dlgPumpCtrl()
{
    delete ui;
}

void dlgPumpCtrl::changeEvent(QEvent *e)
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

void dlgPumpCtrl::slotUpdate() // в цьому слоті буде поновлюватися інформація на картинці
{
    ui->s_pV->setValue(src.getValueFloat(t[Pc::V]));
    ui->s_lV->setText(QString("%1").arg(src.getValueScaled(t[Pc::V]),3,'f',0));
    ui->s_I->setChecked(src.getValue16(t[Pc::I]));
    if(ui->s_AM->currentIndex())
    {
        ui->s_R_M->setCurrentIndex(src.getValue16(t[Pc::Q])?1:0);
    }
}

void dlgPumpCtrl::slotSetSl(int v)
{
    double td=v;
//    qDebug() << sender()->objectName();

    if(sender()->objectName()=="s_SP_min")
    {
        src.sendValue(t[Pc::Min],qint16(v));
        ui->s_sSP_min->blockSignals(true);
        ui->s_sSP_min->setValue(td/4000.0*(src.scaleFull(t[Pc::Min])-src.scaleZero(t[Pc::Min]))+src.scaleZero(t[Pc::Min]));
        ui->s_sSP_min->blockSignals(false);
//        qDebug() << t[Pc::Min] << src.scaleZero(t[Pc::Min]) << src.scaleFull(t[Pc::Min]);

    }
    else
    {
        src.sendValue(t[Pc::Max],qint16(v));
        ui->s_sSP_max->blockSignals(true);
        ui->s_sSP_max->setValue(td/4000.0*(src.scaleFull(t[Pc::Max])-src.scaleZero(t[Pc::Max]))+src.scaleZero(t[Pc::Max]));
        ui->s_sSP_max->blockSignals(false);
    }
}

void dlgPumpCtrl::slotSetDs(double v)
{
    if(sender()->objectName()=="s_sSP_min")
    {
        src.sendValueScaled(t[Pc::Min],v);
        ui->s_SP_min->blockSignals(true);
        ui->s_SP_min->setValue((v-src.scaleZero(t[Pc::Min]))/(src.scaleFull(t[Pc::Min])-src.scaleZero(t[Pc::Min]))*4000.0);
        ui->s_SP_min->blockSignals(false);
    }
    else
    {
        src.sendValueScaled(t[Pc::Max],v);
        ui->s_SP_max->blockSignals(true);
        ui->s_SP_max->setValue((v-src.scaleZero(t[Pc::Max]))/(src.scaleFull(t[Pc::Max])-src.scaleZero(t[Pc::Max]))*4000.0);
        ui->s_SP_max->blockSignals(false);
    }
}


void dlgPumpCtrl::slotSetBool(int v)
{
    if(sender()->objectName()=="s_AM")
    {
        src.sendValue(t[Pc::Am],qint16(-v));
        ui->s_R_M->blockSignals(v);
    }
    else
    {
        src.sendValue(t[Pc::Q],qint16(-v));
    }

}


