#include "dlgbledingsetup.h"
#include "ui_dlgbledingsetup.h"
#include "iodev.h"
//#include <QTimer>
#include <QDateTime>

dlgBledingSetup::dlgBledingSetup(IoDev &source,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgBledingSetup),
    src(source)
{
    ui->setupUi(this);
    // ініціалізація
    cb_e  << ui->en_p_01
            << ui->en_p_02
            << ui->en_p_03
            << ui->en_p_04
            << ui->en_p_05
            << ui->en_p_06
            << ui->en_p_07
            << ui->en_p_08;

    cb_k    << ui->kr_p_01
            << ui->kr_p_02
            << ui->kr_p_03
            << ui->kr_p_04
            << ui->kr_p_05
            << ui->kr_p_06
            << ui->kr_p_07
            << ui->kr_p_08;

    te_p      << ui->Tp_zd_01
            << ui->Tp_zd_02
            << ui->Tp_zd_03
            << ui->Tp_zd_04
            << ui->Tp_zd_05
            << ui->Tp_zd_06
            << ui->Tp_zd_07
            << ui->Tp_zd_08;

    te_m        << ui->Tm_zd_01
            << ui->Tm_zd_02
            << ui->Tm_zd_03
            << ui->Tm_zd_04
            << ui->Tm_zd_05
            << ui->Tm_zd_06
            << ui->Tm_zd_07
            << ui->Tm_zd_08;

    foreach(QTimeEdit* v,te_m)
    {
        v->setTime(QTime().addSecs(src.getValue16(v->objectName())*60));
        connect(v,SIGNAL(timeChanged(QTime)),this,SLOT(slotSet(QTime)));

    }

    foreach(QTimeEdit* v,te_p)
    {
        v->setTime(QTime().addSecs(src.getValue16(v->objectName())));
        connect(v,SIGNAL(timeChanged(QTime)),this,SLOT(slotSet(QTime)));

    }

    foreach(QComboBox *v,cb_e)
    {
        v->setCurrentIndex(src.getValue16(v->objectName())?1:0);
        connect(v,SIGNAL(currentIndexChanged(int)),this,SLOT(slotSet(int)));
    }

    QHash<int,int> s;
    s[1440]=0;
    s[720]=1;
    s[480]=2;
    s[360]=3;
    s[240]=4;
    s[180]=5;
    s[120]=6;

    foreach(QComboBox *v,cb_k)
    {
        v->setCurrentIndex(s.contains(src.getValue16(v->objectName()))?s[src.getValue16(v->objectName())]:0);
        connect(v,SIGNAL(currentIndexChanged(int)),this,SLOT(slotSet(int)));
    }

    // синхронізація годинника контролера, це би зробити автоматично......
    QVector<qint16> time;
    QDateTime ct=QDateTime::currentDateTime();
    time << ct.date().year() << ct.date().month() << ct.date().day() << ct.time().hour() << ct.time().minute() << ct.time().second() << -1;
    src.sendValue("yy_s",time);
    updateList();
}

dlgBledingSetup::~dlgBledingSetup()
{
    delete ui;
}

void dlgBledingSetup::changeEvent(QEvent *e)
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


void dlgBledingSetup::slotSet(int v)
{
    if(sender()->objectName().left(2)=="en")
    {
        src.sendValue(sender()->objectName(),qint16(-v));
    }
    else
    {
        QVector<qint16> vi;
        vi << 1440 << 720 << 480 << 360 << 240  << 180 << 120;
        src.sendValue(sender()->objectName(),vi[v]);
    }
    src.sendValue("Save",qint16(-1));
    updateList();
}

void dlgBledingSetup::slotSet(QTime v)
{
    qint16 t=0;
    if(sender()->objectName().left(2)=="Tm")
        t= QTime(0,0,0,0).msecsTo(v)/60000;
    else
        t= QTime(0,0,0,0).msecsTo(v)/1000;

    src.sendValue(sender()->objectName(),t);
    src.sendValue("Save",qint16(-1));
    updateList();
}

void dlgBledingSetup::updateList()
{
    QStringList tankName        ;
    tankName << tr("6-та зона ПДБМ")
            << tr("Теплий дефекатор")
            << tr("Гарячий А")
            << tr("Гарячий Б")
            << tr("1-й сатуратор")
            << tr("Дефекатор 2 сат.")
            << tr("2-й сатуратор")
            << tr("Відстійник 2-сат.");

    QVector<qint16> vi;
    vi << 1440 << 720 << 480 << 360 << 240  << 180 << 120;


    QVector<int> time;
    QVector<QString> name;
    for(int i=0;i<8;++i)
    {
        if(cb_e[i]->currentIndex()) // перевірити чи включена продувка
        {
            int start = QTime(0,0,0,0).msecsTo(te_m[i]->time())/60000; // отримати час пуску
            int kr = vi[cb_k[i]->currentIndex()];  // отримати кратність
            for(int j=0;j<1440/kr;++j) // крутить в циклі
            {
                int k;
                for(k=0;k<time.size();++k) // знайти наше місце
                {
                    if(time[k]>start)
                        break;
                }
                // вставити знайдені значення

                time.insert(k,start);
                name.insert(k,tankName[i]);
                // розрахувати
                start+=kr;
                start %=1440;
            }
        }
    }
    ui->teList->clear();
    for(int i=0;i<time.size();++i)
    {
        ui->teList->append(QString("%1. %2:%3\t%4").arg(i+1,3).arg(time[i]/60,2,10,QChar('0')).arg(time[i]%60,2,10,QChar('0')).arg(name[i]));
    }

}
