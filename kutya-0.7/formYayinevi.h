#include "ui_formYayinevi.h" 
#include "yayinevi.h"
#include<QSqlQueryModel>
#include<QItemSelectionModel>
#include<QDataWidgetMapper>
class pencereYayinevi:public QWidget ,public Ui::FormYayinevi
{
 Q_OBJECT
public:
 QSqlQueryModel *sorgu_model;
 QItemSelectionModel *selectionModel ;
 QDataWidgetMapper *mapper ;
 QList<QWidget *> wList;//Bunlara formdaki lineedit alanlarını ekliyorum.setreadonly için.
 bool yeni_kayit;
 bool guncelle;

pencereYayinevi(QWidget *parent):QWidget(parent)
{
    setupUi(this);
    wList.append(LeAd);
    yeni_kayit=true;
    guncelle=true;
  

     sorgu_model = new QSqlQueryModel;
     sorgu_model->setQuery("SELECT * FROM yayinevi");
     actionSil->setEnabled(true); 
     yayinevi_tablo->addAction(actionSil);

     yayinevi_tablo->setModel(sorgu_model);
     yayinevi_tablo->show();
     selectionModel = yayinevi_tablo->selectionModel();
  mapper = new QDataWidgetMapper;
  mapper->setModel(sorgu_model);
  mapper->addMapping(LeAd, 1);
  mapper->addMapping(TeEk, 2);

 connect(pBKaydet,SIGNAL(clicked()),this,SLOT(Kaydet()));
 connect(arama_kutusu,SIGNAL(textChanged ( const QString &  )),this,SLOT(Ara(const QString &)));
 connect(pBSil,SIGNAL(clicked()),this,SLOT(Sil()));
 connect(pBiptal,SIGNAL(clicked()),this,SLOT(mod_baslangic()));
 connect(pBDegistir,SIGNAL(clicked()),this,SLOT(Guncelle()));
 connect(yayinevi_tablo,SIGNAL(pressed ( const QModelIndex & )),this,SLOT(tablodolas(const QModelIndex &)));
 connect(yayinevi_tablo,SIGNAL(activated ( const QModelIndex & )),this,SLOT(tablodolas(const QModelIndex &)));

}
public slots:

void tablodolas(const QModelIndex & index)
{
mapper->setCurrentModelIndex(index);
//Bilgi alanların setReadOnly(true) olması.düğmelerin değiştir ve yeni kayır modunda olması gibi şeyler.
mod_baslangic();
}
void Guncelle()
{
   if(mod_guncelle()){
        QString tmp_id= sorgu_model->data(sorgu_model->index(selectionModel->currentIndex().row(), 0)).toString();
	yayinevi *y = new yayinevi(tmp_id,LeAd->text(),TeEk->toPlainText());
        y->Guncelle();
		sorgu_model->setQuery("SELECT * FROM yayinevi ");
		sorgu_model->query();
   }

}

void Kaydet()
{
  if(mod_kayit()){
yayinevi *y = new yayinevi(LeAd->text(),TeEk->toPlainText());
y->Kaydet();
sorgu_model->setQuery("SELECT * FROM yayinevi ORDER by id DESC");
sorgu_model->query();
}
}
void Ara(const QString & text )
{
QString f;
f.append( "lower(ad) LIKE '%");
f.append(text.toLower());
f.append("%'");
f.append( " OR ad LIKE '%");
f.append(text);
f.append("%' ");
qDebug() << f ;
sorgu_model->setQuery("SELECT * FROM yayinevi WHERE "+ f);
sorgu_model->query();

}

void Sil()
{

	QString tmp_id= sorgu_model->data(sorgu_model->index(selectionModel->currentIndex().row(), 0)).toString();
	yayinevi *y = new yayinevi(tmp_id);
	y->Sil();
		sorgu_model->setQuery("SELECT * FROM yayinevi ");
		sorgu_model->query();
}
void on_actionSil_triggered()
{
 Sil(); 
}
bool mod_kayit()
{
if(yeni_kayit){
	pBKaydet->setText(QString::fromUtf8("Kaydet"));
//Bilgi girilebilir. 
	widgetLineEditSetReadOnly(wList,0);
 	TeEk->setReadOnly(0);
//Bilgi girilebilir
 	widgetLineEditTemizle(wList);
 	TeEk->clear();
	yeni_kayit=false;
	pBDegistir->setEnabled (false);
return false;
}else{
	pBKaydet->setText(QString::fromUtf8("Yeni Kayıt"));
 	widgetLineEditSetReadOnly(wList,1);
	yeni_kayit=true;
	pBDegistir->setEnabled (true);
return true;
     }
}
bool mod_guncelle()
{
if(guncelle){
	pBDegistir->setText("Onayla");
	pBKaydet-> setEnabled (false);
//Bilgi girilebilir.
	widgetLineEditSetReadOnly(wList,0);
	TeEk->setReadOnly(false);
//Bilgi girilebilir.
	guncelle=false;
return false;
}else{
	pBDegistir->setText(QString::fromUtf8("Değiştir"));
	pBKaydet-> setEnabled (true);
//Bilgi girilecek yerler aktif değil.
	widgetLineEditSetReadOnly(wList,1);
	TeEk->setReadOnly(true);
//Bilgi girilecek yerler aktif değil.
	guncelle=true;
return true;

}


}
void mod_baslangic()
{
	pBKaydet-> setEnabled (true);
	pBDegistir->setEnabled (true);
	yeni_kayit=true;
	guncelle=true;
	pBDegistir->setText(QString::fromUtf8("Değiştir"));
	pBKaydet->setText(QString::fromUtf8("Yeni Kayıt"));
	widgetLineEditSetReadOnly(wList,1);
	 TeEk->setReadOnly(true);
}
void widgetLineEditSetReadOnly(QList<QWidget *> widgetList , int durum)
{
 for (int i = 0; i < widgetList.size(); ++i) {
         qobject_cast<QLineEdit *>(widgetList.at(i))->setReadOnly(durum);
 }
}
void widgetLineEditTemizle(QList<QWidget *> widgetList)
 {
  for (int i = 0; i < widgetList.size(); ++i) {
          qobject_cast<QLineEdit *>(widgetList.at(i))->clear();
  }
 }

};

