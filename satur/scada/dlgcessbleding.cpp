#include "dlgcessbleding.h"
#include "ui_dlgcessbleding.h"
#include "iodev.h"
#include <QTimer>

dlgCessBleding::dlgCessBleding(IoDev &source, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgCessBleding),
    src(source)
{
    ui->setupUi(this);

    ui->Am_17->setCurrentIndex(src.getValue16("Am_17")?1:0);
    ui->X_zd_17->setValue(src.getValueScaled("X_zd_17"));
    ui->Ton_X_17->setTime(QTime().addSecs(src.getValue32("Ton_X_17")/1000));
    ui->Toff_X_17->setTime(QTime().addSecs(src.getValue32("Toff_X_17")/1000));

    ui->sX_17->blockSignals(ui->Am_17->currentIndex());
    ui->dX_17->blockSignals(ui->Am_17->currentIndex());

    connect(ui->Am_17,SIGNAL(currentIndexChanged(int)),this,SLOT(slotSet(int)));
    connect(ui->X_zd_17,SIGNAL(valueChanged(double)),this,SLOT(slotSet(double)));
    connect(ui->Ton_X_17,SIGNAL(timeChanged(QTime)),this,SLOT(slotSet(QTime)));
    connect(ui->Toff_X_17,SIGNAL(timeChanged(QTime)),this,SLOT(slotSet(QTime)));

    connect(ui->sX_17,SIGNAL(valueChanged(int)),this,SLOT(slotSet(int)));
    connect(ui->dX_17,SIGNAL(valueChanged(double)),this,SLOT(slotSet(double)));

    QTimer *tmr = new QTimer(this);
    tmr->setInterval(1000);
    tmr->start();
    connect(tmr,SIGNAL(timeout()),this,SLOT(slotUpdate()));


}

dlgCessBleding::~dlgCessBleding()
{
    delete ui;
}

void dlgCessBleding::changeEvent(QEvent *e)
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

void dlgCessBleding::slotUpdate() // в цьому слоті буде поновлюватися інформація на картинці
{
    if(ui->Am_17) // в автоматичному режисобновляти значення у віджетах
    {
        ui->sX_17->setValue(src.getValueFloat("X_17"));
        ui->dX_17->setValue(src.getValueScaled("X_17"));
    }
}

void dlgCessBleding::slotSet(int v)
{
    if(sender()->objectName()=="sX_17")
    {
        src.sendValue("X_17",(double)v );
        ui->dX_17->blockSignals(true);
        ui->dX_17->setValue((double)v *(src.scaleFull("X_17")-src.scaleZero("X_17"))/4000.0+src.scaleZero("X_17"));
        ui->dX_17->blockSignals(false);
    }
    if(sender()->objectName()=="Am_17")
    {
        src.sendValue("Am_17",qint16(-v));
        ui->sX_17->blockSignals(v);
        ui->dX_17->blockSignals(v);
    }
}

void dlgCessBleding::slotSet(double v)
{
    src.sendValueScaled(sender()->objectName(),v);

    if(sender()->objectName()=="dX_17")
    {
        ui->sX_17->blockSignals(true)    ;
        ui->sX_17->setValue((v-src.scaleZero("X_17"))/(src.scaleFull("X_17")-src.scaleZero("X_17"))*4000.0);
        ui->sX_17->blockSignals(false)    ;
    }
}

void dlgCessBleding::slotSet(QTime v)
{
    qint32 t= QTime(0,0,0,0).msecsTo(v);

    src.sendValue(sender()->objectName(),t);
}


