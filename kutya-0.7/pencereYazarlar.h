#include "yazarlar.h"
#include "guiTools.h"
#include "ui_formYazarlar.h"
// #include<QHeaderView>

class pencereYazarlar:public guiTools, public Ui::FormYazarlar {
    Q_OBJECT
public:
    yazarlar *arama;
    ~pencereYazarlar() {
    }
    pencereYazarlar() {

        setupUi(this);

        wList.append(LeAd);
        wList.append(LeSoyad);
        wList.append(TeEk);

        degistir= pBDegistir;
        kaydet =pBKaydet;
        setSorgu("SELECT * FROM yazarlar ORDER by id DESC");

        connectTable(yazarlar_tablo);
        yazarlar_tablo->addAction(actionSil);

        yazarlar_tablo->verticalHeader()->hide();
        yazarlar_tablo->hideColumn(0);
        yazarlar_tablo->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

        modInitial();
        arama = new yazarlar ();

        connect(pBKaydet,SIGNAL(clicked()),this,SLOT(Kaydet()));
        connect(arama_kutusu,SIGNAL(textChanged ( const QString &  )),this,SLOT(Ara(const QString &)));
        connect(pBSil,SIGNAL(clicked()),this,SLOT(Sil()));
        connect(pBiptal,SIGNAL(clicked()),this,SLOT(modInitial()));
        connect(pBDegistir,SIGNAL(clicked()),this,SLOT(Guncelle()));
        connect(yazarlar_tablo,SIGNAL(pressed ( const QModelIndex & )),this,SLOT(tablodolas(const QModelIndex &)));
        connect(yazarlar_tablo,SIGNAL(activated ( const QModelIndex & )),this,SLOT(tablodolas(const QModelIndex &)));
        connect(yazarlar_tablo->horizontalHeader(),SIGNAL ( sectionClicked ( int ) ),this,SLOT ( sirala ( int ) ));




    }
public slots:
    void Kaydet() {
        if (modSave()) {
            yazarlar *yazar = new yazarlar(LeAd->text(),LeSoyad->text(),TeEk->toPlainText());
            if (!yazar->Kaydet()) {
                modSaveError();
            };
            refreshTable(getSorgu());
        }
    }
    void Sil() {
        QString tmp_id=getData(0).toString();
        yazarlar *yazar = new yazarlar(tmp_id);
        yazar->Sil();
        refreshTable(getSorgu());

    }
    void Guncelle() {
        if (modChange()) {
            QString tmp_id=getData(0).toString();
            yazarlar *yazar = new yazarlar(tmp_id,LeAd->text(),LeSoyad->text(),TeEk->toPlainText());
            yazar->Guncelle();
            refreshTable(getSorgu());
        }
    }
    void tablodolas(const QModelIndex & index) {
        mapper->setCurrentModelIndex(index);
        modInitial();
    }
    void sirala ( int header ) {
        if (modAzalan())
            arama->lookfor(header,arama_kutusu->text(), " ASC");
        else
            arama->lookfor(header,arama_kutusu->text(), " DESC");
        sorgu_model->clear();
        arama->Ara();
        refreshTable ( arama->getAramaSorgusu() );

    }

    void Ara(const QString & text ) {
        arama->lookfor(1,text," DESC");
        arama->Ara();
        refreshTable ( arama->getAramaSorgusu() );
    }
    void on_actionSil_triggered() {
        Sil();
    }

};
