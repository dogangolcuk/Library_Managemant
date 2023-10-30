#include "ui_formGeriAl.h"
#include "guiTools.h"
#include "gerial.h"
#include <QMessageBox>
#include <QHeaderView>
#include <QDate>
class formGeriAl:public guiTools ,public Ui::FormGeriAl {
    Q_OBJECT
public:
    gerial *arama;
    guiTools getirilenKitaplar;
    guiTools getirilmeyenKitaplar;
    QString uyeid;
    int GeId;
    formGeriAl() {
        setupUi(this);
        arama = new gerial();
        setSorgu("SELECT id,uye_no,ad,soyad FROM uyeler");
        connectTable(TvUyeler);
        TvUyeler->hideColumn(0);
        TvUyeler->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
        TvGetirilmeyenler->addAction(actionGetirdi);
        TvGetirilenler->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
        TvGetirilmeyenler->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

        connect(arama_kutusu,SIGNAL(textChanged ( const QString &  )),this,SLOT(Ara(const QString &)));
        connect ( TvUyeler->horizontalHeader(),SIGNAL ( sectionClicked ( int ) ),this,SLOT ( sirala ( int ) ));
        connect(TvUyeler,SIGNAL(pressed ( const QModelIndex & )),this,SLOT(tablodolas(const QModelIndex &)));
        connect(TvUyeler,SIGNAL(activated ( const QModelIndex & )),this,SLOT(tablodolas(const QModelIndex &)));
        connect(TvGetirilmeyenler,SIGNAL(activated ( const QModelIndex & )),this,SLOT(tablodolasGe(const QModelIndex &)));
        connect(TvGetirilmeyenler,SIGNAL(pressed ( const QModelIndex & )),this,SLOT(tablodolasGe(const QModelIndex &)));

    }
public slots:

    void tablodolas(const QModelIndex & index) {

        mapper->setCurrentModelIndex(index);
        uyeid =getData("id").toString();
        getirilmeyenler(uyeid);
        getirilenler(uyeid);

    }

    void tablodolasGe(const QModelIndex & index) {
        getirilmeyenKitaplar.mapper->setCurrentModelIndex(index);
        GeId=getirilmeyenKitaplar.getData(0).toInt();

    }
    void Ara(const QString & text ) {
        arama->lookfor(1,text," DESC");
        arama->Ara();
        refreshTable ( arama->getAramaSorgusu() );

    }
    void sirala ( int header ) {
        if (modAzalan())
            arama->lookfor(header,arama_kutusu->text(), " ASC");
        else
            arama->lookfor(header,arama_kutusu->text(), " DESC");
        arama->Ara();
        refreshTable ( arama->getAramaSorgusu() );
    }

    void getirilmeyenler(QString uyeid) {
        getirilmeyenKitaplar.setSorgu("SELECT o.id,o.uye_id,k.ad AS Kitap,o.verme_tarihi FROM odunc_al_ver o,kitaplar k WHERE o.verdi_vermedi=false and o.uye_id="+uyeid +"and k.id=o.kitap_id");
        getirilmeyenKitaplar.connectTable(TvGetirilmeyenler);
        TvGetirilmeyenler->hideColumn(0);
        TvGetirilmeyenler->hideColumn(1);


    }

    void getirilenler(QString uyeid) {
        getirilenKitaplar.setSorgu("SELECT o.id,o.uye_id,k.ad AS Kitap,o.alma_tarihi FROM odunc_al_ver o,kitaplar k WHERE o.verdi_vermedi=true and o.uye_id="+uyeid +"and k.id=o.kitap_id");
        getirilenKitaplar.connectTable(TvGetirilenler);
        TvGetirilenler->hideColumn(0);
        TvGetirilenler->hideColumn(1);

    }
    void getirdi() {
        QDate localDate = QDate::currentDate();
        gerial *getir= new gerial(GeId,localDate);
        getir->Guncelle();
        getirilmeyenler(uyeid);
        getirilenler(uyeid);

    }
    void on_actionGetirdi_triggered() {
        getirdi();
    }



};

