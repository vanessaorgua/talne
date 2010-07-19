
#include "mnemo.h"
#include "ui_mnemo.h"

#include <IoNetClient.h>

#include "trendchart.h"
#include "panelReg.h"

// унікальні діалогові вікна
#include "dlgpumpctrl.h"
#include "dlgsusctrl.h"
#include "dlgcessctrl.h"
#include "dlgcessbleding.h"
#include "dlgvbctrl.h"
#include <QVBoxLayout>
#include <QPalette>
#include <QTimer>

Mnemo::Mnemo(IoNetClient &src, QWidget *p) : QLabel(p), m_ui(new Ui::mnemo),s(src)
{
    m_ui->setupUi(this);

    connect(&s,SIGNAL(updateDataRaw()),this,SLOT(updateDataRaw())); // при отриманні нових даних, засвітити їх на картинці
    connect(&s,SIGNAL(updateDataScaled()),this,SLOT(updateDataScaled())); // при отриманні нових даних, засвітити їх на картинці

    QVector<QPushButton*> pbc;
    pbc
            << m_ui->s_cX_01
            << m_ui->s_cX_02
            << m_ui->s_cX_03
            << m_ui->s_cX_04
            << m_ui->s_cX_05
            << m_ui->s_cX_06
            << m_ui->s_cX_07
            << m_ui->s_cX_08
            << m_ui->s_cX_09
            << m_ui->s_cX_10
            << m_ui->s_cX_11
            << m_ui->s_cX_12
            << m_ui->s_cX_13
            << m_ui->s_cX_14
            << m_ui->s_cX_15
            << m_ui->s_cX_16
            << m_ui->s_cX_18
            << m_ui->s_cX_19
            << m_ui->s_cX_20
            << m_ui->s_cX_21;

    foreach(QPushButton *p,pbc)
    {
        connect(p,SIGNAL(clicked()),this,SLOT(slotCallReg()));
    }

    connect(m_ui->s_cI_14,SIGNAL(clicked()),this,SLOT(slotCallPumpCtrl()));
    connect(m_ui->s_cI_17,SIGNAL(clicked()),this,SLOT(slotCallPumpCtrl()));
    connect(m_ui->s_cI_09,SIGNAL(clicked()),this,SLOT(slotCallQ09()));
    connect(m_ui->s_cI_10,SIGNAL(clicked()),this,SLOT(slotCallQ10()));
    connect(m_ui->s_cX_17,SIGNAL(clicked()),this,SLOT(slotCallX_17()));

    s_cI    << m_ui->s_cI_01
            << m_ui->s_cI_02
            << m_ui->s_cI_03
            << m_ui->s_cI_04
            << m_ui->s_cI_05
            << m_ui->s_cI_06
            << m_ui->s_cI_07
            << m_ui->s_cI_08;
    foreach(QPushButton *p,s_cI)
    {
        connect(p,SIGNAL(clicked()),this,SLOT(slotCallVb()));
    }

    s_cI    << m_ui->s_cI_09;


    le      << m_ui->s_V_01
            << m_ui->s_V_02
            << m_ui->s_V_03
            << m_ui->s_V_04
            << m_ui->s_V_05
            << m_ui->s_V_06
            << m_ui->s_V_07
            << m_ui->s_V_08
            << m_ui->s_V_09
            << m_ui->s_V_10
            << m_ui->s_V_11
            << m_ui->s_V_12
            << m_ui->s_V_13
            << m_ui->s_V_14
            << m_ui->s_V_15
            << m_ui->s_V_16
            << m_ui->s_V_17
            << m_ui->s_V_18
            << m_ui->s_V_19
            << m_ui->s_V_20
            << m_ui->s_V_21
            << m_ui->s_V_22
            << m_ui->s_V_23
            << m_ui->s_V_24
            << m_ui->s_V_25
            << m_ui->s_V_26
            << m_ui->s_V_27
            << m_ui->s_V_28
            << m_ui->s_V_29
            << m_ui->s_V_30
            << m_ui->s_V_31
            << m_ui->s_V_32
            << m_ui->s_V_33
            << m_ui->s_V_34
            << m_ui->s_V_35
            << m_ui->s_V_36
            << m_ui->s_V_37
            << m_ui->s_V_38
            << m_ui->s_V_39
            << m_ui->s_V_40
            << m_ui->s_V_41
            << m_ui->s_V_42
            << m_ui->s_V_43
            << m_ui->s_V_44
            << m_ui->s_V_45
            << m_ui->s_V_46
            << m_ui->s_V_47
            << m_ui->s_V_48
            << m_ui->s_V_49
            << m_ui->s_V_50
            << m_ui->s_V_51
            << m_ui->s_V_52
            << m_ui->s_V_53
            << m_ui->s_V_54;

        le_X << m_ui->s_X_01
            << m_ui->s_X_02
            << m_ui->s_X_03
            << m_ui->s_X_04
            << m_ui->s_X_05
            << m_ui->s_X_06
            << m_ui->s_X_07
            << m_ui->s_X_08
            << m_ui->s_X_09
            << m_ui->s_X_10
            << m_ui->s_X_11
            << m_ui->s_X_12
            << m_ui->s_X_13
            << m_ui->s_X_14
            << m_ui->s_X_15
            << m_ui->s_X_16
            << m_ui->s_X_17
            << m_ui->s_X_18
            << m_ui->s_X_19
            << m_ui->s_X_20
            << m_ui->s_X_21;
        cb
                << m_ui->s_Am_01
                << m_ui->s_Am_02
                << m_ui->s_Am_03
                << m_ui->s_Am_04
                << m_ui->s_Am_05
                << m_ui->s_Am_06
                << m_ui->s_Am_07
                << m_ui->s_Am_08
                << m_ui->s_Am_09
                << m_ui->s_Am_10
                << m_ui->s_Am_11
                << m_ui->s_Am_12
                << m_ui->s_Am_13
                << m_ui->s_Am_14
                << m_ui->s_Am_15
                << m_ui->s_Am_16
                << m_ui->s_Am_17
                << m_ui->s_Am_18
                << m_ui->s_Am_19
                << m_ui->s_Am_20
                << m_ui->s_Am_21
                << m_ui->s_Am_Q_09
                << m_ui->s_Am_Q_10
                << m_ui->s_Am_M_14
                << m_ui->s_Am_M_17
                << m_ui->s_I_11
                << m_ui->s_I_12
                << m_ui->s_I_13
                << m_ui->s_Q_01
                << m_ui->s_Q_02
                << m_ui->s_Q_03
                << m_ui->s_Q_04
                << m_ui->s_Q_05
                << m_ui->s_Q_06
                << m_ui->s_Q_07
                << m_ui->s_Q_08
                << m_ui->s_Q_09
                << m_ui->s_Q_10
                << m_ui->s_en_p_01
                << m_ui->s_en_p_02
                << m_ui->s_en_p_03
                << m_ui->s_en_p_04
                << m_ui->s_en_p_05
                << m_ui->s_en_p_06
                << m_ui->s_en_p_07
                << m_ui->s_en_p_08;

/*
                << m_ui->s_I_01
                << m_ui->s_I_02
                << m_ui->s_I_03
                << m_ui->s_I_04
                << m_ui->s_I_05
                << m_ui->s_I_06
                << m_ui->s_I_07
                << m_ui->s_I_08 */

        pb
            << m_ui->s_pV_19
            << m_ui->s_pV_20
            << m_ui->s_pV_21
            << m_ui->s_pV_22
            << m_ui->s_pV_24
            << m_ui->s_pV_25
            << m_ui->s_pV_26
            << m_ui->s_pV_27
            << m_ui->s_pV_28
            << m_ui->s_pV_29
            << m_ui->s_pV_30
            << m_ui->s_pV_31
            << m_ui->s_pV_33
            << m_ui->s_pV_34
            << m_ui->s_pV_36
            << m_ui->s_pV_41
            << m_ui->s_pV_42
            << m_ui->s_pV_45
            << m_ui->s_pV_51;

    QVector<QFrame *> f ;
         f  << m_ui->s_Tr_01
            << m_ui->s_Tr_02
            << m_ui->s_Tr_03
            << m_ui->s_Tr_04
            << m_ui->s_Tr_05
            << m_ui->s_Tr_06
            << m_ui->s_Tr_07;

    for(int i=0;i<7;++i)
    {
        TrendChart *t=new TrendChart(this);
        QVBoxLayout *vbl = new QVBoxLayout(f[i]);
        vbl->addWidget(t);
        f[i]->setLayout(vbl);
        trc << t;
    }

    // це сильно константне рішення
    QStringList stl;
    // 1 вапно на дефекацію
    stl << "V_49" <<  "X_06" <<"SP_06" <<  "V_16" << "Spr_06" ;
    trChTags << stl;

    // 2 відкачка з холодного
    stl.clear();
    stl << "V_37" <<	"X_18"	<< "SP_18"<< 	"Spr_18" <<	 "V_28"<<	"SP2_18";
    trChTags << stl;

      // 3 повернення соку 1 сатурації
    stl.clear();
    stl << "V_46" <<	"X_03" << "SP_03" <<	"Spr_03" <<"V_16" <<	"V_48"  ;
    trChTags << stl;

    //4 рН першрї сатурації
    stl.clear();
    stl << "V_53" <<	"X_10"  <<"SP_10"<< "V_37";
    trChTags << stl;

    //5 витрата на деф 2 сат
    stl.clear();
    stl << "V_38" <<	"X_19" << "SP_19" <<  "V_27" <<	"Spr_19" ;
    trChTags << stl;


    //6 рН 2 сатурації
    stl.clear();
    stl << "V_54" <<	"X_11" <<"SP_11"<< "V_38" ;
    trChTags << stl;

    //7 витрата суспензії 2 сат
    stl.clear();
    stl << "V_48" <<	"X_05"  <<"SP_05" ;
    trChTags << stl;


    QTimer *t = new QTimer(this);
    t->setInterval(5000);
    t->start();
    connect(t,SIGNAL(timeout()),this,SLOT(updateTrendChart()));
}

Mnemo::~Mnemo()
{
    delete m_ui;
}


void Mnemo::updateDataRaw()
{
    foreach(QProgressBar *p,pb)
    {
        p->setValue(s[0]->getValueFloat(p->objectName().right(p->objectName().size()-3)));
    }

    foreach(QCheckBox *p,cb)
    {
        p->setChecked(s[0]->getValue16(p->objectName().right(p->objectName().size()-2)));
    }


    QPalette pal_w,pal_y;
    pal_w.setColor(QPalette::Base,Qt::white);
    pal_y.setColor(QPalette::Base,Qt::yellow);

    foreach(QLineEdit *p,le_X)
    {
        p->setPalette(s[0]->getValue16(QString("Amr_%1").arg(p->objectName().right(2)))?pal_w:pal_y);
    }

    foreach(QPushButton* p,s_cI)
    {
        p->setIcon(QIcon(QPixmap(s[0]->getValue16(p->objectName().right(p->objectName().size()-3))
                ?":/valves/valve_green_20x32.png":":/valves/valve_off_20x32.png")));
    }

    m_ui->s_cI_10->setIcon(QIcon(QPixmap(s[0]->getValue16("I_10")
                ?":/valves/valve_green_20x32.png":":/valves/valve_off_20x32.png")));

    m_ui->s_cI_14->setIcon(QIcon(QPixmap(s[0]->getValue16("I_14")
                ?":/butons/pict/lib/pump_green_26x30.png":":/butons/pict/lib/pump_off_26x30.png")));

    m_ui->s_cI_17->setIcon(QIcon(QPixmap(s[0]->getValue16("I_17")
                ?":/butons/pict/lib/pump_green_26x30.png":":/butons/pict/lib/pump_off_26x30.png")));

    // індикація дискретних сигналів ЧП насосів
    QVector<QLineEdit*> s_drv;
        s_drv <<    m_ui->s_V_39
            << m_ui->s_V_40
            << m_ui->s_V_43
            << m_ui->s_V_44;


    QStringList t_w;
    t_w << "I_19"
                << "I_25"
                << "I_22"
                << "I_28";
    QStringList t_a;
    t_a << "I_21"
            << "I_27"
            << "I_24"
            << "I_30";

    for(int i=0;i<4;++i)
    {
        QPalette pal;
        if(s[0]->getValue16(t_a[i]))
        {
            pal.setColor(QPalette::Base,Qt::red);
        }
        else
        {
            if(s[0]->getValue16(t_w[i]))
            {
                pal.setColor(QPalette::Base,Qt::white);
            }
            else
            {
                pal.setColor(QPalette::Base,Qt::cyan);
            }
        }
        s_drv[i]->setPalette(pal);
    }

}

void Mnemo::updateDataScaled() // слот обновляє дані на мнемосхемі
{
    int l=0,f=0; // довжина та кількість знаків після коми
    foreach(QLineEdit *p,le)
    {
        if(s[0]->scaleFull(p->objectName().right(p->objectName().size()-2))>20.0)
        {
            l=3;
            f=0;
        }
        else
        {
            l=4;
            f=1;
        }
        p->setText(QString("%1").arg(s[0]->getValueScaled(p->objectName().right(p->objectName().size()-2)),l,'f',f));
    }

    foreach(QLineEdit *p,le_X)
    {
        p->setText(QString("%1").arg(s[0]->getValueScaled(p->objectName().right(p->objectName().size()-2)),3,'f',0));
    }

}

void Mnemo::updateTrendChart() // поновлення графіків
{
    QVector<double> v;
    int i=0;
    foreach(QStringList str,trChTags)
    {
        //qDebug() << str;
        v.clear();
        foreach(QString t,str)
        {
            v << s[0]->getValueFloat(t);
        }
        trc[i++]->addPoint(v);

    }
}


void Mnemo::slotCallReg()
{
    RpanelReg p(*s[0],sender()->objectName().right(2).toInt()-1,this);
    p.exec();
}

void Mnemo::slotCallPumpCtrl()
{
    QStringList v;
    if(sender()->objectName()=="s_cI_14")
    {
        v << "V_21"
                << "I_14"
                << "R_M_14"
                << "Am_M_14"
                << "V_21_min"
                << "V_21_max";
    }
    else
    {
        v << "V_25"
                << "I_17"
                << "R_M_17"
                << "Am_M_17"
                << "V_25_min"
                << "V_25_max";

    }

    dlgPumpCtrl p(*s[0],v,this);
    p.exec();
}


void Mnemo::slotCallQ10()
{
    dlgSusCtrl p(*s[0],this);
    p.exec();
}

void Mnemo::slotCallQ09()
{
    dlgCessCtrl p(*s[0],this);
    p.exec();
}

void Mnemo::slotCallX_17()
{
    dlgCessBleding  p(*s[0],this);
    p.exec();
}


void Mnemo::slotCallVb()
{
    dlgVbCtrl p(*s[0],sender()->objectName().right(2).toInt(),this);
    p.exec();
}

