#include "ui_formYayinevi.h"
#include "yayinevi.h"
#include "guiTools.h"
#include<QHeaderView>
class pencereYayinevi:public guiTools ,public Ui::FormYayinevi {
    Q_OBJECT
public:
    guiTools yayinci;
    yayinevi *arama;

    pencereYayinevi() {
        setupUi(this);
        degistir= pBDegistir;
        kaydet =pBKaydet;
        wList.append(LeAd);
        wList.append(TeEk);

        setSorgu("SELECT * FROM yayinevi");
        connectTable(yayinevi_tablo);
        yayinevi_tablo->addAction(actionSil);

        yayinevi_tablo->hideColumn(0);

        yayinevi_tablo->verticalHeader()->hide();
        yayinevi_tablo->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
        modInitial();
        arama = new yayinevi ();

        connect(pBKaydet,SIGNAL(clicked()),this,SLOT(Kaydet()));
        connect(arama_kutusu,SIGNAL(textChanged ( const QString &  )),this,SLOT(Ara(const QString &)));
        connect(pBSil,SIGNAL(clicked()),this,SLOT(Sil()));
        connect(pBiptal,SIGNAL(clicked()),this,SLOT(modInitial()));
        connect(pBDegistir,SIGNAL(clicked()),this,SLOT(Guncelle()));
        connect(yayinevi_tablo,SIGNAL(pressed ( const QModelIndex & )),this,SLOT(tablodolas(const QModelIndex &)));
        connect(yayinevi_tablo,SIGNAL(activated ( const QModelIndex & )),this,SLOT(tablodolas(const QModelIndex &)));
        connect(yayinevi_tablo->horizontalHeader(),SIGNAL ( sectionClicked ( int ) ),this,SLOT ( sirala ( int ) ));

    }
public slots:

    void tablodolas(const QModelIndex & index) {
        mapper->setCurrentModelIndex(index);
        modInitial();
    }
    void Guncelle() {
        if (modChange()) {
            QString tmp_id=getData(0).toString();
            yayinevi *y = new yayinevi(tmp_id,LeAd->text(),TeEk->toPlainText());
            y->Guncelle();
            refreshTable(getSorgu());
        }

    }

    void Kaydet() {
        if (modSave()) {
            yayinevi *y = new yayinevi(LeAd->text(),TeEk->toPlainText());
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
        yayinevi *y = new yayinevi(tmp_id);
        y->Sil();
        refreshTable(getSorgu());
    }
    void on_actionSil_triggered() {
        Sil();
    }

};
