#include "ui_formUyeler.h"
#include "uyeler.h"
#include "guiTools.h"
#include <QDate>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>

class pencereUyeler:public guiTools, public Ui::FormUyeler {
    Q_OBJECT
public:
    int LeSinifId;//sinif tablosundan foreign key olarak int geliyor.
    uyeler *arama;
    int EnSonSiralama;
    QString EnSonAramaMod;
    pencereUyeler() {

        LeSinifId=0;
        setupUi ( this );

        wList.append ( LeUyeNo );
        wList.append ( LeAd );
        wList.append ( LeSoyad );
        wList.append ( Lesinif );
//         wList.append ( DeUyelikTarihi );
        wList.append ( LeUyelikTipi );
        wList.append ( LeTel );
        wList.append ( LeCeptel );
        wList.append ( LeEmail );
        wList.append ( TeAdres );
        wList.append ( TeEk );


        degistir= pBDegistir;
        kaydet =pBKaydet;
        //Burada girdiÄim sorguya gÃ¶re tablo baÄlanÄ±lÄ±yor.
        setSorgu ( "SELECT * FROM uyeler ORDER by id DESC" );
        connectTable ( uyeler_tablo );

        uyeler_tablo->addAction ( actionSil );
        uyeler_tablo->hideColumn(0);
        uyeler_tablo->hideColumn(7);
        uyeler_tablo->hideColumn(8);
        uyeler_tablo->hideColumn(9);
        uyeler_tablo->hideColumn(10);
        uyeler_tablo->hideColumn(11);
        uyeler_tablo->horizontalHeader()->setResizeMode(QHeaderView::Stretch);


        QDate localDate = QDate::currentDate();
        DeUyelikTarihi->setDate ( localDate );

        modInitial();

        cBdb();

        arama = new uyeler ();

        connect ( pBKaydet,SIGNAL ( clicked() ),this,SLOT ( Kaydet() ) );
        connect ( pBSil,SIGNAL ( clicked() ),this,SLOT ( Sil() ) );
        connect ( pBiptal,SIGNAL ( clicked() ),this,SLOT ( modInitial() ) );
        connect ( pBDegistir,SIGNAL ( clicked() ),this,SLOT ( Guncelle() ) );
        connect ( arama_kutusu,SIGNAL ( textChanged ( const QString & ) ),this,SLOT ( Ara ( const QString & ) ) );
        connect ( uyeler_tablo,SIGNAL ( pressed ( const QModelIndex & ) ),this,SLOT ( tablodolas ( const QModelIndex & ) ) );
        connect ( uyeler_tablo,SIGNAL ( activated ( const QModelIndex & ) ),this,SLOT ( tablodolas ( const QModelIndex & ) ) );
        connect ( uyeler_tablo->horizontalHeader(),SIGNAL ( sectionClicked ( int ) ),this,SLOT ( sirala ( int ) ));

        connect(Lesinif,SIGNAL(currentIndexChanged(int)),this,SLOT(sinifSet(int)));
    }
public slots:

    void sinifSet(int i) {
        LeSinifId=Lesinif->model()->data(Lesinif->model()->index(Lesinif->currentIndex(), 1)).toInt() ;



    }
    void tablodolas ( const QModelIndex & index ) {

        mapper->setCurrentModelIndex ( index );
        setSinifText();
        LeSinifId=getData("sinif").toInt();
//         QString sinifText = getData(4).toString();
//         int sinifIndex=Lesinif->findText ( sinifText );
//         Lesinif->setCurrentIndex ( sinifIndex );
//  	Lesinif->setItemText(0,sinifText);
        modInitial();
    }
    void setSinifText() {


        QStringList tmp_list=getDataList("sinif","SELECT ad FROM sinif Where id=:key_id");
//         LeYayinlayan->setText(tmp_list.at(0));
        Lesinif->setEditText(tmp_list.at(0));
// CbYayinci->model()->index(


    }
    void sirala ( int header ) {
        if (modAzalan()) {
            arama->lookfor(header,arama_kutusu->text(), " ASC");
            EnSonAramaMod="ASC";
        } else {
            arama->lookfor(header,arama_kutusu->text(), " DESC");
// 	sorgu_model->clear();
            EnSonAramaMod="DESC";
        }
        arama->Ara();
        EnSonSiralama=header;
        refreshTable ( arama->getAramaSorgusu() );

    }
    void Guncelle() {

        if ( modChange() ) {
            QString tmp_id= sorgu_model->data ( sorgu_model->index ( selectionModel->currentIndex().row(), 0 ) ).toString();
            uyeler *uye = new uyeler ( tmp_id,LeUyeNo->text(),LeAd->text(),LeSoyad->text(),LeSinifId,DeUyelikTarihi->date(),LeUyelikTipi->text(),LeTel->text(),LeCeptel->text(),LeEmail->text(),TeAdres->toPlainText(),TeEk->toPlainText() );
            uye->Guncelle();
            refreshTable ( getSorgu() );
        }
    }

    void Kaydet() {
        if ( modSave() ) {
            uyeler *uye = new uyeler ( LeUyeNo->text(),LeAd->text(),LeSoyad->text(),LeSinifId,DeUyelikTarihi->date(),LeUyelikTipi->text(),LeTel->text(),LeCeptel->text(),LeEmail->text(),TeAdres->toPlainText(),TeEk->toPlainText() );

            if ( !uye->Kaydet() ) {
                modSaveError();
            };
            refreshTable ( getSorgu() );
        }
    }

    void Ara ( const QString & text ) {

//         sorgu_model->clear();
// 	arama->lookfor(EnSonSiralama,text," DESC");
        arama->lookfor(EnSonSiralama,text,EnSonAramaMod);
        arama->Ara();
        refreshTable ( arama->getAramaSorgusu() );
    }

    void Sil() {

        QString tmp_id= sorgu_model->data ( sorgu_model->index ( selectionModel->currentIndex().row(), 0 ) ).toString();
//burda ÃÂÃÂÃÂÃÂ¼yenin getirmediÃÂÃÂÃÂÃÂi kitap varmÃÂÃÂÃÂÃÂ± ona bakÃÂÃÂÃÂÃÂ±yorum.
        QString uye_no= sorgu_model->data ( sorgu_model->index ( selectionModel->currentIndex().row(), 1 ) ).toString();

        QSqlQuery sorgu ( "SELECT count(*)  FROM getirilmeyenler WHERE uye_no='"+ uye_no+"'" );
        sorgu.exec();
        sorgu.next();
        if ( sorgu.lastError().isValid() );
        qDebug() << sorgu.lastError() <<"sorgu";

        int getirilmeyen_kitap_sayisi=sorgu.value ( 0 ).toInt();
        QString Sgetirilmeyen_kitap_sayisi=sorgu.value ( 0 ).toString();
        if ( getirilmeyen_kitap_sayisi>0 ) {
            if (
                QMessageBox::question (
                    this,
                    trUtf8 ( "Uyar" ),
                    trUtf8 ( "Bu üyeye ait<b> %1 adet getirilmemiş</b> kitap bulunuyor."
                             "Daha detaylı bilgi için <u>Raporlar</u>'a bakabilirsiniz."
                             "Bu kaydı silerseniz kullanıcı ile ilgili <b>tüm kayıtlar</b>      silinecektir."
                             "Buna rağmen silmek istiyor musunuz?" ).arg ( Sgetirilmeyen_kitap_sayisi ),
                    trUtf8 ( "Evet" ),
                    trUtf8 ( "Hayır" ),
                    QString(), 1, 0 | QMessageBox::Default | QMessageBox::Escape ) == 0
            ) {
                uyeler *uye = new uyeler ( tmp_id );
                uye->Sil();
                refreshTable ( getSorgu() );
            }
        } else {
            uyeler *uye = new uyeler ( tmp_id );
            uye->Sil();
            refreshTable ( getSorgu() );
        }
    }
    void on_actionSil_triggered() {
        Sil();
    }

    void cBdb() {
        QSqlQueryModel *model = new QSqlQueryModel;
        model->setQuery("SELECT ad,id FROM sinif");
        Lesinif->setModel(model);
    }
};
