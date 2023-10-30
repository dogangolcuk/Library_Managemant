#include "ui_formKategori.h"
#include "kategori.h"
#include "guiTools.h"
#include<QHeaderView>
class pencereKategori:public guiTools ,public Ui::FormKategori {
    Q_OBJECT
public:
//  guiTools yayinci;
    kategori *arama;

    pencereKategori() {
        setupUi(this);
        degistir= pBDegistir;
        kaydet =pBKaydet;
        wList.append(LeAd);
        wList.append(TeEk);

        setSorgu("SELECT * FROM kitapkategori");
        connectTable(tablo);
        tablo->addAction(actionSil);

        tablo->hideColumn(0);

        tablo->verticalHeader()->hide();
        tablo->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
        modInitial();
        arama = new kategori ();

        connect(pBKaydet,SIGNAL(clicked()),this,SLOT(Kaydet()));
        connect(arama_kutusu,SIGNAL(textChanged ( const QString &  )),this,SLOT(Ara(const QString &)));
        connect(pBSil,SIGNAL(clicked()),this,SLOT(Sil()));
        connect(pBiptal,SIGNAL(clicked()),this,SLOT(modInitial()));
        connect(pBDegistir,SIGNAL(clicked()),this,SLOT(Guncelle()));
        connect(tablo,SIGNAL(pressed ( const QModelIndex & )),this,SLOT(tablodolas(const QModelIndex &)));
        connect(tablo,SIGNAL(activated ( const QModelIndex & )),this,SLOT(tablodolas(const QModelIndex &)));
        connect(tablo->horizontalHeader(),SIGNAL ( sectionClicked ( int ) ),this,SLOT ( sirala ( int ) ));

    }
public slots:

    void tablodolas(const QModelIndex & index) {
        mapper->setCurrentModelIndex(index);
        modInitial();
    }
    void Guncelle() {
        if (modChange()) {
            QString tmp_id=getData(0).toString();
            kategori *y = new kategori(tmp_id,LeAd->text(),TeEk->toPlainText());
            y->Guncelle();
            refreshTable(getSorgu());
        }

    }

    void Kaydet() {
        if (modSave()) {
            kategori *y = new kategori(LeAd->text(),TeEk->toPlainText());
            if (!y->Kaydet()) {
                modSaveError();
            };
            refreshTable(getSorgu());
        }
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

    void Sil() {

        QString tmp_id=getData(0).toString();
        kategori *y = new kategori(tmp_id);
        y->Sil();
        refreshTable(getSorgu());
    }
    void on_actionSil_triggered() {
        Sil();
    }

};
