#include "ui_formOduncVer.h"
#include "guiTools.h"
#include "oduncver.h"
#include <QDate>
#include <QLocale>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
class formOduncVer:public guiTools ,public Ui::FormOduncVer {
    Q_OBJECT
    QModelIndex curindex;
    int uyeid;
    int kitapid;
    QString uyeid_str;
    QString kitapid_str;
public:
    guiTools uye;
    guiTools kitap;
    oduncver *aramaUyeler;
    oduncver *aramaKitaplar;
    formOduncVer() {
        setupUi(this);
        QDate localDate = QDate::currentDate();
        QDate localDate15sonra = localDate.addDays(15);
        dateVerme->setDate(localDate);
        dateAlma->setDate(localDate15sonra);

        aramaUyeler = new oduncver ();
        aramaKitaplar = new oduncver ();

        connect(ara_uyeler,SIGNAL(textChanged ( const QString &  )),this,SLOT(AraUyeler(const QString &)));
        connect(ara_kitaplar,SIGNAL(textChanged ( const QString &  )),this,SLOT(AraKitaplar(const QString &)));
        connect(pBver,SIGNAL(clicked()),this,SLOT(Kaydet()));
        connect(tVuyeler,SIGNAL(pressed( const QModelIndex & )),this,SLOT(tablodolas(const QModelIndex &)));
        connect(tVKitaplar,SIGNAL(pressed( const QModelIndex & )),this,SLOT(tablodolas(const QModelIndex &)));
        connect(tVuyeler,SIGNAL(activated( const QModelIndex & )),this,SLOT(tablodolas(const QModelIndex &)));
        connect(tVKitaplar,SIGNAL(activated( const QModelIndex & )),this,SLOT(tablodolas(const QModelIndex &)));
        connect ( tVuyeler->horizontalHeader(),SIGNAL ( sectionClicked ( int ) ),this,SLOT ( siralaUyeler(  int  )));
        connect ( tVKitaplar->horizontalHeader(),SIGNAL ( sectionClicked ( int ) ),this,SLOT ( siralaKitaplar ( int ) ));

        uye.wList.append(lEUye);
        uye.setSorgu("SELECT id,uye_no,ad,soyad FROM uyeler");
        uye.connectTable(tVuyeler);
        tVuyeler->hideColumn(0);
        tVuyeler->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
        kitap.wList.append(lEKitap);
        kitap.setSorgu("SELECT id,ad,isbn,barkod,adet FROM kitaplar");
        kitap.connectTable(tVKitaplar);
        tVKitaplar->hideColumn(0);
        tVKitaplar->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    }
public slots:

    void tablodolas(const QModelIndex & index) {
        uye.mapper->setCurrentModelIndex(index);
        kitap.mapper->setCurrentModelIndex(index);
        uyeid =uye.getData("id").toInt();
        kitapid=kitap.getData("id").toInt();
        uyeid_str =uye.getData("id").toString();
        kitapid_str=kitap.getData("id").toString();
        qDebug()<<kitapid_str;
    }
    void AraUyeler( const QString & text) {
        aramaUyeler->lookforMembers(1,text," DESC");
        aramaUyeler->Ara();
        uye.refreshTable ( aramaUyeler->getAramaSorgusu() );

    }
    void AraKitaplar(const QString & text ) {

        aramaKitaplar->lookforBooks(1,text," DESC");
        aramaKitaplar->Ara();
        kitap.refreshTable ( aramaKitaplar->getAramaSorgusu() );

    }

    void siralaUyeler ( int header ) {
        if (uye.modAzalan())
            aramaUyeler->lookforMembers(header,ara_uyeler->text(), " ASC");
        else
            aramaUyeler->lookforMembers(header,ara_uyeler->text(), " DESC");
        aramaUyeler->Ara();
        uye.refreshTable ( aramaUyeler->getAramaSorgusu() );

    }
    void siralaKitaplar ( int header ) {
        if (kitap.modAzalan())
            aramaKitaplar->lookforBooks(header,ara_kitaplar->text(), " ASC");
        else
            aramaKitaplar->lookforBooks(header,ara_kitaplar->text(), " DESC");
        aramaKitaplar->Ara();
        kitap.refreshTable ( aramaKitaplar->getAramaSorgusu() );

    }

    void Kaydet() {
        if (KitapUygunmu() and uyeUygunmu()) {

            oduncver *odunc = new oduncver(uyeid,kitapid,dateVerme->date(),dateAlma->date());

            if ( odunc->Kaydet() ) {
//                 modSaveError();
                QMessageBox::question(
                    this,
                    trUtf8("Uyarı"),
                    trUtf8("Kayıt Tamamlandı.")
                );

            } else {

                QMessageBox::question(
                    this,
                    trUtf8("Uyarı"),

                    trUtf8("Ödünç <b>Verilemedi</b>.Aynı Tarihte Aynı Kitabı "
                           "Vermeye Çalıştınız Yada Başka Sorun Oluştu.")
                );
            }

        }

    }

    int KitapUygunmu() {

       // QSqlQuery sorgu("SELECT count(*)  FROM  odunc_al_ver WHERE  kitap_id= "+ kitapid_str +" and verdi_vermedi=false");
        QSqlQuery sorgu;
        sorgu.prepare("SELECT count(*)  FROM  odunc_al_ver WHERE  kitap_id=:kitapid_str and verdi_vermedi=false");
        sorgu.bindValue(":kitapid_str",kitapid_str);
        sorgu.exec();
        sorgu.next();

        QSqlQuery sorgu1;
        sorgu1.prepare("SELECT adet  FROM  kitaplar WHERE  id=:kitapid_str");
        sorgu1.bindValue(":kitapid_str",kitapid_str);
        sorgu1.exec();
        sorgu1.next();

        if (sorgu.lastError().isValid());
        qDebug() << "hata" << sorgu.lastError();
        qDebug() << "hata2" << sorgu1.lastError();
        int verilen_kitap_sayisi=sorgu.value(0).toInt();
        int toplam_kitap_sayisi=sorgu1.value(0).toInt();
        QString k=sorgu.value(0).toString();
        QString tk=sorgu1.value(0).toString();
        qDebug()<<"sORGU 1 "<< k ;
        qDebug()<<"sORGU 2 "<< tk;
        if (toplam_kitap_sayisi<=verilen_kitap_sayisi) {
            qDebug("Kitap kalmamış");
            QMessageBox::question(
                this,
                trUtf8("Uyarı"),
                trUtf8("Kitap Adeti Yetersiz.Kitap Diğer Üyelerde Olabilir.")
            );
            return 0;
        } else return 1;

    }

    int uyeUygunmu() {

        QDomDocument ayarDosyasi;
        QFile tmp("/etc/kutya.ayar");
        tmp.open(QIODevice::ReadOnly| QIODevice::Text);
        ayarDosyasi.setContent(&tmp);
        QDomElement root = ayarDosyasi.firstChildElement("Ayarlar");
        QDomElement kategori = root.firstChildElement("KitapLimit");
        QDomElement deger = kategori.firstChildElement("Deger");

        int kitaplimit= deger.text().toInt();

        QSqlQuery sorgu;
        sorgu.prepare("SELECT count(*)  FROM  odunc_al_ver WHERE  uye_id=:uyeid_str and verdi_vermedi=false");
        sorgu.bindValue(":uyeid_str",uyeid_str);
        sorgu.exec();
        sorgu.next();

        if (sorgu.lastError().isValid());
        qDebug() << sorgu.lastError();
        int uyedeki_kitap_sayisi=sorgu.value(0).toInt();
        QString k=sorgu.value(0).toString();
        qDebug()<< k ;
        if (uyedeki_kitap_sayisi>=kitaplimit) {
            if (
                QMessageBox::question(
                    this,
                    trUtf8("Uyarı"),
                    trUtf8("Üyede  <b>%1 adet</b> getirilmemiş kitap gözüküyor."
                           "Üyenin getirmediği kitaplar için <u>Geri Al Formu</u>'na   bakabilirsiniz."
                           "Buna rağmen kitap vermek istiyor musunuz?").arg(k),
                    trUtf8("Evet"),
                    trUtf8("Hayır"),
                    QString(), 1, 0 | QMessageBox::Default | QMessageBox::Escape) == 0
            ) return 1;
            return 0;
        }
        return 1;
    }

};

