#include <ui_raporUyeler.h>
#include "guiTools.h"
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>
#include <QHeaderView>
#include <QDate>
#include <QLocale>
// #include "tdpreviewdialog.h"
#include <QWebView>
class raporUyeler:public QWidget ,public Ui::RaporUyeler {
    Q_OBJECT

public:
    QString ht;
    guiTools raporlar;
    QWebView *web;
    QTreeWidgetItem *_item;
    int _column;
    raporUyeler(QWidget *parent):QWidget(parent) {
        setupUi(this);
        raporlar.setSorgu("SELECT uye_no,ad,soyad,sinif,uyelik_tipi,tel,email FROM uyeler");
        raporlar.connectTable(tablo);
        tablo->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
// tablo->hideColumn(0);
        web = new QWebView(0);

        connect(arama_kutusu,SIGNAL(textChanged ( const QString &  )),this,SLOT(Ara(const QString &)));
        connect(pBYazdir,SIGNAL(clicked()),this,SLOT(print()));
        connect(raporTreeWidget,SIGNAL(itemClicked ( QTreeWidgetItem *,int) ),this,SLOT(report(QTreeWidgetItem*,int)));

    }
public slots:

    void tablodolas(const QModelIndex & index) {



    }
    void report(QTreeWidgetItem * item,int column) {
        _item=item;
        _column=column;
        if (item->text(column)==trUtf8("Üyeler Listesi")) {
//             raporlar.setSorgu("SELECT uye_no,u.ad,soyad,s.ad AS sinif,uyelik_tipi,tel,email FROM uyeler u,sinif s WHERE sinif=s.id");
	    raporlar.setSorgu("SELECT * FROM raporuyelistesi");
            raporlar.refreshTable(raporlar.getSorgu());
        } else if (item->text(column)==trUtf8("En Çok Okuyan Üyeler Listesi")) {
            raporlar.setSorgu(" SELECT * FROM encokokuyan");
            raporlar.refreshTable(raporlar.getSorgu());

        } else if (item->text(column)==trUtf8("Kitap Listesi")) {
//             raporlar.setSorgu("SELECT isbn,barkod,kitaplar.ad,adet,raf,kt.ad AS kategori,yayin_tarihi FROM kitaplar,kitapkategori kt WHERE kitaplar.kategori=kt.id");
	    raporlar.setSorgu("SELECT * FROM raporkitaplistesi");
            raporlar.refreshTable(raporlar.getSorgu());

        } else if (item->text(column)==trUtf8("En Çok Okunan Kitap Listesi")) {
            raporlar.setSorgu("SELECT * FROM encokokunan");
            raporlar.refreshTable(raporlar.getSorgu());

        } else if (item->text(column)==trUtf8("Getirilmeyen Kitaplar")) {
            raporlar.setSorgu("SELECT * FROM getirilmeyenler");
            raporlar.refreshTable(raporlar.getSorgu());

        } else if (item->text(column)==trUtf8("Getirilmeyen Günü Geçmiş Kitaplar")) {
// 	QDate localDate = QDate::currentDate();
//  	QString date = localDate.toString(Qt::ISODate);
            raporlar.setSorgu("SELECT * FROM gunugecmiskitaplar");
            raporlar.refreshTable(raporlar.getSorgu());


        }
        label_title->setText(item->text(column));

        slotReportHtml();

    }

    void slotReportHtml() {
// cikti_hazirla();
        /*
        int rowCount = raporlar.sorgu_model->query().size();
        int lines=30;
        int pages;
        double div = rowCount / lines;
        	int modulo = rowCount % lines;
        	if (modulo == 0 ) {
        		pages = QVariant(div).toInt();
        	} else
        	{
        		div = div+1.0;
        		pages = QVariant(div).toInt();
        	}
        */
        ht.clear();
        ht.append("<center><tr><thead><table cellspacing='7' cellpadding='7' border='0' >");
        ht.append("<tr><b><h2>"+_item->text(_column)+"</h2></b></tr>");//baÃÂlÃÂ±k
        ht.append("<hr>");
// for(int i=0;i<pages;i++)
// {
        ht.append("<tr>");
        for (int i=0; i<raporlar.getFieldCount(); i++) {
            QString header=raporlar.sorgu_model->headerData(i,Qt::Horizontal,Qt::DisplayRole).toString();
            ht.append("<td><b>"+header.toUpper()+"</b></td>");
        }
        ht.append("</tr>");

// 	for (int j=0;j<lines;j++)
// {


        while (raporlar.sorgu_model->query().next()) {
            ht.append("<tr>");
// 			raporlar.sorgu_model->query().next();
            for (int i=0; i<raporlar.getFieldCount(); i++) {
                QString tableData=raporlar.sorgu_model->query().value(i).toString();
                ht.append("<td>"+tableData+"</td>");
            }
            ht.append("</tr>");
        }
// }
// ht.append("Sayfa"+QVariant(i).toString()+"/"+QVariant(pages).toString());
        ht.append("</table></thead></tr></center>");
// }

        web->setHtml(ht);





    }

    void Ara(const QString & text ) {
        QString f;
        QStringList fields;
        fields=raporlar.getFieldNames();
        f.append(fields.at(0)+" LIKE '%"+text+"%'");
        f.append(" OR ");
        f.append(" lower("+fields.at(0)+") LIKE '%"+text.toLower()+"%' ");

        for (int i=1;i<raporlar.getFieldCount();i++) {

            f.append(" OR "+fields.at(i)+" LIKE '%"+text+"%'");
            f.append(" OR ");
            f.append(" lower("+fields.at(i)+") LIKE '%"+text.toLower()+"%' ");
        }

        raporlar.sorgu_model->setQuery(raporlar.getSorgu()+" WHERE "+ f);
// 	raporlar.sorgu_model->query();

	qDebug()<<raporlar.getSorgu()<<" WHERE "<< f;
        slotReportHtml();
    }
    void print() {

        web->setHtml(ht);
        QPrintPreviewDialog *dialog = new QPrintPreviewDialog(this);
        connect(dialog, SIGNAL(paintRequested(QPrinter *)),
                web, SLOT(print(QPrinter *)));
        dialog->exec();

    }

};
