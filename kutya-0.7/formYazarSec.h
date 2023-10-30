#include "ui_YazarSec.h"
#include <QtSql>
#include "guiTools.h"
#include<QHeaderView>
#include <QCloseEvent>
class formYazarSec :public QDialog ,public Ui::FormYazarSec {
    Q_OBJECT
    int id;
    QString ad;
    QString soyad;
    QList<int> idList;
    QStringList adList;
    guiTools yazarsec;
public:
    formYazarSec(QWidget *parent):QDialog(parent) {

        setupUi(this);

        connect(arama_kutusu,SIGNAL(textChanged ( const QString &  )),this,SLOT(Ara(const QString &)));
        connect(tVYayinci,SIGNAL(clicked ( const QModelIndex & )),this,SLOT(tablodolas(const QModelIndex &)));
        connect(tVYayinci,SIGNAL(activated ( const QModelIndex & )),this,SLOT(tablodolas(const QModelIndex &)));
        connect(tVYayinci,SIGNAL(pressed ( const QModelIndex & )),this,SLOT(tablodolas(const QModelIndex &)));
        connect(pBSec,SIGNAL(clicked()),this,SLOT(sec()));
        connect(pBekle,SIGNAL(clicked()),this,SLOT(Ekle()));
        connect(pBTemizle,SIGNAL(clicked()),this,SLOT(temizle()));

        yazarsec.setSorgu("SELECT id,ad,soyad FROM yazarlar");
        yazarsec.connectTable(tVYayinci);
        tVYayinci->addAction(actionEkle);
        tVYayinci->verticalHeader()->hide();
        tVYayinci->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
        tVYayinci->hideColumn(0);

    }

protected:
    void closeEvent(QCloseEvent *event) {
        sec();
        event->accept();

    }


public slots:
    void tablodolas(const QModelIndex & index) {
        id=yazarsec.getData(0).toInt();
        ad=yazarsec.getData(1).toString();
        soyad=yazarsec.getData(2).toString();
    }
    void sec() {
        emit yazarSelected(idList,adList);
        this->hide();
    }
    void Ara(const QString & text ) {
        QString lowerText = text.toLower();
        QString upperText = text.toUpper();
        QSqlQuery tmp_arama;
        QString find_str;

        find_str.append("lower(ad) LIKE '%"+lowerText+"%'");
        find_str.append("OR upper(ad) LIKE '%"+upperText+"%'");

        find_str.append("OR lower(soyad) LIKE '%"+lowerText+"%'");
        find_str.append("OR upper(soyad) LIKE '%"+upperText+"%'");


        tmp_arama.prepare("SELECT id,ad,soyad FROM yazarlar WHERE "+find_str);
        tmp_arama.exec();

        yazarsec.refreshTable(tmp_arama);

    }
    void Ekle() {
        LwSecilenler->addItem(ad + " " + soyad);
        idList.append(id);
        adList.append(ad+" "+soyad);

    }
    void on_actionEkle_triggered() {
        Ekle();
    }
    void temizle() {
        LwSecilenler->clear();
        idList.clear();
        adList.clear();

    }
    void mevcutYazarlar(QString kitap_id) {
        temizle();
        QSqlQuery sorgu;
        sorgu.prepare("SELECT y.id,y.ad,y.soyad FROM yazar_kitap,yazarlar y WHERE y.id=yazar_id AND kitap_id = " + kitap_id);
        sorgu.exec();
        while (sorgu.next()) {
            QString idStr=sorgu.value(0).toString();
            int id=sorgu.value(0).toInt();
            QString ad =sorgu.value(1).toString();
            QString soyad=sorgu.value(2).toString();
            LwSecilenler->addItem(ad + " " + soyad);
            idList.append(id);
            adList.append(ad+" "+soyad);
        }

    }
signals:
    void yazarSelected(QList<int> ,QStringList);
};
