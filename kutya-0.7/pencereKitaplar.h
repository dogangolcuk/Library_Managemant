#include "ui_formKitaplar.h"
#include "formYazarSec.h"
#include "kitaplar.h"
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include "guiTools.h"
#include <QModelIndex>
class pencereKitaplar:public guiTools, public Ui::FormKitaplar {
    Q_OBJECT
public:
    int LeYayinciId;//yayinevi tablosundan foreign key olarak int geliyor.
    int LeKategoriId;
    int LeGirisSekliId;
    QStringList yazaradListesi;
    QList<int> yazaridListesi;
    kitaplar *arama;
//     QString LeYayinciIdTe;
    pencereKitaplar() {

        LeYayinciId=0;//yayinevi tablosundan foreign key olarak int geliyor.
        LeKategoriId=0;
        LeGirisSekliId=0;

        setupUi(this);

        wList.append(LeAd);
        wList.append(LeIsbn);
        wList.append(LeBarkod);
        wList.append(dETarih);
        wList.append(sBAdet);
        wList.append(LeRaf);
        wList.append(sBBaski);
        wList.append(cBgirissekli);
        wList.append(dEGiris);
        wList.append(ek);
        wList.append(CbYayinci);
        wList.append(CbKategori);

        degistir= pBDegistir;
        kaydet =pBKaydet;
        //Burada girdiÃÂÃÂÃÂÃÂim sorguya gÃÂÃÂÃÂÃÂ¶re tablo baÃÂÃÂÃÂÃÂlanÃÂÃÂÃÂÃÂ±lÃÂÃÂÃÂÃÂ±yor.
        setSorgu ( "SELECT * FROM kitaplar ORDER by id DESC" );
        connectTable ( tablo );

        tablo->addAction ( actionSil );
        tablo->hideColumn(0);
        tablo->hideColumn(10);
        tablo->hideColumn(11);
        tablo->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

        QDate localDate = QDate::currentDate();
        dETarih->setDate(localDate);
        dEGiris->setDate(localDate);

        modInitial();
        arama = new kitaplar ();

//         cBDoldur();
        connectComboBoxDb(CbYayinci,"SELECT ad,id FROM yayinevi");
        connectComboBoxDb(CbKategori,"SELECT ad,id FROM kitapkategori");
        connectComboBoxDb(cBgirissekli,"SELECT ad,id FROM kitapgirissekli");

        connect(tBYazarSec,SIGNAL(clicked()),this,SLOT(YazarSecForm()));
        connect(pBKaydet,SIGNAL(clicked()),this,SLOT(Kaydet()));
        connect(arama_kutusu,SIGNAL(textChanged ( const QString &  )),this,SLOT(Ara(const QString &)));
        connect(pBSil,SIGNAL(clicked()),this,SLOT(Sil()));
        connect(pBiptal,SIGNAL(clicked()),this,SLOT(modInitial()));
        connect(pBDegistir,SIGNAL(clicked()),this,SLOT(Guncelle()));
        connect(tablo,SIGNAL(clicked ( const QModelIndex & )),this,SLOT(tablodolas(const QModelIndex &)));
        connect(tablo,SIGNAL(activated ( const QModelIndex & )),this,SLOT(tablodolas(const QModelIndex &)));
        connect ( tablo->horizontalHeader(),SIGNAL ( sectionClicked ( int ) ),this,SLOT ( sirala ( int ) ));
        connect(CbYayinci,SIGNAL(currentIndexChanged(int)),this,SLOT(yayinciSet(int)));
        connect(CbKategori,SIGNAL(currentIndexChanged(int)),this,SLOT(kategoriSet(int)));
        connect(cBgirissekli,SIGNAL(currentIndexChanged(int)),this,SLOT(giris_sekliSet(int)));
    }
public slots:

//     void YayinciSecForm() {
//         widgetYayinciSec *wY = new widgetYayinciSec(this);
//         connect(wY,SIGNAL(yayinciSelected(int ,QString)),this,SLOT(yayinciSet(int,QString)));
//         wY->show();

//     }
    void YazarSecForm() {

        formYazarSec *fYs = new formYazarSec(this);

        connect(fYs,SIGNAL(yazarSelected(QList<int> ,QStringList)),this,SLOT(yazarSet(QList<int> ,QStringList)));
        connect(this,SIGNAL(kitap_id_yolla(QString)),fYs,SLOT(mevcutYazarlar(QString)));

        QString tmp_id=getData("id").toString();
        emit kitap_id_yolla(tmp_id);

        fYs->show();

    }
    void tablodolas(const QModelIndex & index) {

        mapper->setCurrentModelIndex(index);
        setForeignKeyComboBoxText();
        setYazarlarText();
        LeYayinciId=getData("yayinci").toInt();//Foreign key olarak x tablodan deÄer.
        LeKategoriId=getData("kategori").toInt();
        LeGirisSekliId=getData("giris_sekli").toInt();
//         qDebug("%d , %d, %d",LeYayinciId,LeKategoriId,LeGirisSekliId);
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
       //  qDebug("Hata sirala" + arama->getAramaSorgusu() ;
    }
    void Guncelle() {

        if (modChange()) {
            QString tmp_id = getData("id").toString();
            kitaplar *kitap = new kitaplar(tmp_id,LeAd->text(),LeIsbn->text(),LeBarkod->text(),dETarih->date(),sBAdet->value(),LeRaf->text(),sBBaski->value(),LeGirisSekliId,dEGiris->date(),ek->toPlainText(),LeYayinciId,LeKategoriId);
            if (kitap->Guncelle())
                yazar_kitap_degistir();
            refreshTable ( getSorgu() );
        }
    }

    void Kaydet() {
        if (modSave()) {
            kitaplar *kitap = new
            kitaplar(LeAd->text(),LeIsbn->text(),LeBarkod->text(),dETarih->date(),sBAdet->value(),LeRaf->text(),sBBaski->value(),LeGirisSekliId,dEGiris->date(),ek->toPlainText(),LeYayinciId,LeKategoriId);
            if (kitap->Kaydet()) {
                yazar_kitap_kaydet();
            } else {
                modSaveError();
            };
            refreshTable ( getSorgu() );
        }

    }

    void Ara(const QString & text ) {
        arama->lookfor(1,text," DESC");
        arama->Ara();
        refreshTable ( arama->getAramaSorgusu() );

    }

    void Sil() {
        QString tmp_id= getData("id").toString();
//burda kitabÃÂÃÂÃÂÃÂ±n herhangi bir ÃÂÃÂÃÂÃÂ¼yede olup olmadÃÂÃÂÃÂÃÂ±ÃÂÃÂÃÂÃÂÃÂÃÂÃÂÃÂ±na  bakÃÂÃÂÃÂÃÂ±yorum.
        QString kitap_ad= getData("ad").toString();

        QSqlQuery sorgu("SELECT count(*)  FROM getirilmeyenler WHERE kitap='"+ kitap_ad+"'");
        sorgu.exec();
        sorgu.next();
        if (sorgu.lastError().isValid());
        qDebug() << sorgu.lastError();

        int uyelerdeki_kitap_sayisi=sorgu.value(0).toInt();
        if (uyelerdeki_kitap_sayisi>0) {
            if (
                QMessageBox::question(
                    this,
                    trUtf8("Uyarı"),
                    trUtf8("Bu kitap(%1 adeti) Üye/Üyeler tarafından <b>getirilmemiş</b> gözüküyor."
                           "Daha detaylı bilgi için <u>Raporlar</u>'a bakabilirsiniz."
                           "Bu kaydı silerseniz kitap ile ilgili <b>tüm kayıtlar</b> silinecektir."
                           "Buna rağmen silmek istiyor musunuz?").arg(uyelerdeki_kitap_sayisi),
                    trUtf8("Evet"),
                    trUtf8("Hayır"),
                    QString(), 1, 0 | QMessageBox::Default | QMessageBox::Escape) == 0
            ) {
                kitaplar *kitap = new kitaplar(tmp_id);
                kitap->Sil();
                refreshTable ( getSorgu() );
            }
        } else {
            kitaplar *kitap = new kitaplar(tmp_id);
            kitap->Sil();
            refreshTable ( getSorgu() );
        }

    }

    void setYazarlarText() {
        QStringList tmp_list=getDataList("id","SELECT ad ,soyad FROM yazar_kitap, yazarlar WHERE yazar_id=id and kitap_id=:key_id");
        LwYazarlar->clear();
        LwYazarlar->addItems(tmp_list);
    }
    void yazarSet(QList<int> idListesi,QStringList adListesi) {
        yazaridListesi=idListesi;
        yazaradListesi=adListesi;
        LwYazarlar->addItems(adListesi);
    }
    void yazar_kitap_kaydet() {
        QSqlQuery insert_olayi_yazarKitap;
        sorgu_model->setQuery("SELECT * FROM kitaplar ORDER BY id DESC LIMIT 1");
        sorgu_model->query();
        int enSonKitapid=sorgu_model->data(sorgu_model->index(0, 0)).toInt();
        if (!yazaridListesi.isEmpty()) {
            QSqlDatabase::database().transaction();

            insert_olayi_yazarKitap.prepare("INSERT INTO yazar_kitap ( yazar_id, kitap_id)"
                                            "VALUES (  :yazar_id, :kitap_id )");
            for (int i = 0; i < yazaridListesi.size(); ++i) {
                insert_olayi_yazarKitap.bindValue(":yazar_id",yazaridListesi.at(i));
                insert_olayi_yazarKitap.bindValue(":kitap_id",enSonKitapid);
                insert_olayi_yazarKitap.exec();

//                 qDebug("yazar_kitapa kayÃÂÃÂÃÂÃÂ±t yapÃÂÃÂÃÂÃÂ±ldÃÂÃÂÃÂÃÂ±");
            }
            QSqlDatabase::database().commit();
        } else {
//             qDebug("yazar listesi boÃÂÃÂÃÂÃÂ");
        }

    }
    void  yazar_kitap_degistir() {

        if (!yazaridListesi.isEmpty()) {
            QSqlDatabase::database().transaction();

            QSqlQuery delete_olayi;
            QString tmp_id= sorgu_model->data(sorgu_model->index(selectionModel->currentIndex().row(), 0)).toString();
            delete_olayi.prepare("DELETE FROM yazar_kitap WHERE kitap_id = " + tmp_id );


            delete_olayi.exec();


            QSqlQuery insert_olayi_yazarKitap;

            insert_olayi_yazarKitap.prepare("INSERT INTO yazar_kitap ( yazar_id, kitap_id)"
                                            "VALUES (  :yazar_id, :kitap_id )");
            for (int i = 0; i < yazaridListesi.size(); ++i) {
                insert_olayi_yazarKitap.bindValue(":yazar_id",yazaridListesi.at(i));
                insert_olayi_yazarKitap.bindValue(":kitap_id",tmp_id);
                insert_olayi_yazarKitap.exec();
            }
            QSqlDatabase::database().commit();
        } else {
//             qDebug("yazar listesi boÃÂÃÂÃÂÃÂ");
        }

    }

    void on_actionSil_triggered() {
        Sil();
    }
//Combobox a veritabanÄ± ekleyip foreign key deÄerine karÅÄ±lÄ±k gelen veriyi

    void yayinciSet(int id) {
        LeYayinciId=CbYayinci->model()->data(CbYayinci->model()->index(CbYayinci->currentIndex(), 1)).toInt() ;
//         qDebug("%d , %d, %d",LeYayinciId,LeKategoriId,LeGirisSekliId);
    }
    void kategoriSet(int id) {
        LeKategoriId=CbKategori->model()->data(CbKategori->model()->index(CbKategori->currentIndex(), 1)).toInt() ;
//         qDebug("%d , %d, %d",LeYayinciId,LeKategoriId,LeGirisSekliId);
    }
    void giris_sekliSet(int id) {
        LeGirisSekliId=cBgirissekli->model()->data(cBgirissekli->model()->index(cBgirissekli->currentIndex(), 1)).toInt() ;
//         qDebug("%d , %d, %d",LeYayinciId,LeKategoriId,LeGirisSekliId);

    }
    void setForeignKeyComboBoxText() {

        QStringList tmp_list=getDataList("yayinci","SELECT ad FROM yayinevi Where id=:key_id");
        QStringList tmp_list_kategori=getDataList("kategori","SELECT ad FROM kitapkategori Where id=:key_id");
        QStringList tmp_list_girissekli=getDataList("giris_sekli","SELECT ad FROM kitapgirissekli Where id=:key_id");

        CbYayinci->setEditText(tmp_list.at(0));
        CbKategori->setEditText(tmp_list_kategori.at(0));
        cBgirissekli->setEditText(tmp_list_girissekli.at(0));
    }
signals:
    void kitap_id_yolla(QString);
};
