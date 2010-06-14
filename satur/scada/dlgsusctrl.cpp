#include "dlgsusctrl.h"
#include "ui_dlgsusctrl.h"
#include "iodev.h"
#include "QTimer"
dlgSusCtrl::dlgSusCtrl(IoDev &source,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgSusCtrl),
    src(source)
{
    ui->setupUi(this);

    ui->s_V_32_max->setValue(src.getValueScaled("V_32_max"));
    ui->s_V_32_min->setValue(src.getValueScaled("V_32_min"));
    ui->s_Am_Q_10->setCurrentIndex(src.getValue16("Am_Q_10"));
    ui->s_Q_10->setCurrentIndex(src.getValue16("Q_10"));
    ui->s_Q_10->blockSignals(ui->s_Am_Q_10->currentIndex())    ;

    connect(ui->s_V_32_min,SIGNAL(valueChanged(double)),this,SLOT(slotSendDouble(double)));
    connect(ui->s_V_32_max,SIGNAL(valueChanged(double)),this,SLOT(slotSendDouble(double)));

    connect(ui->s_Am_Q_10,SIGNAL(currentIndexChanged(int)),this,SLOT(slotSendBool(int)));
    connect(ui->s_Q_10,SIGNAL(currentIndexChanged(int)),this,SLOT(slotSendBool(int)));

    QTimer *tmr=new QTimer(this);
    tmr->setInterval(1000);
    tmr->start()            ;
    connect(tmr,SIGNAL(timeout()),this,SLOT(slotUpdate()));

}

dlgSusCtrl::~dlgSusCtrl()
{
    delete ui;
}

void dlgSusCtrl::changeEvent(QEvent *e)
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

void dlgSusCtrl::slotUpdate()
{
    ui->s_V_32->setText(QString("%1").arg(src.getValueScaled("V_32"),5,'f',1));
    ui->s_I_10->setText(src.getValue16("I_10")?tr("Відкрито"):tr("Закрито"));
    if(ui->s_Am_Q_10->currentIndex())
    {
        ui->s_Q_10->setCurrentIndex(src.getValue16("Q_10")?1:0);
    }

}

void dlgSusCtrl::slotSendDouble(double v)
{
    src.sendValueScaled(sender()->objectName().right(sender()->objectName().size()-2),v);
}

void dlgSusCtrl::slotSendBool(int v)
{
    src.sendValue(sender()->objectName().right(sender()->objectName().size()-2),qint16(-v)); // відправити значення

    if(sender()->objectName()=="s_Am_Q_10") // заблокувати при необхідності управління
    {
        ui->s_Q_10->blockSignals(ui->s_Am_Q_10->currentIndex());
    }
}
