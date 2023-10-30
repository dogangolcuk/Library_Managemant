#include "kitaplar.h"
kitaplar::kitaplar() {

}
kitaplar::kitaplar(const QString & id) {
    setCurrentId(id);
//delete olayÄ±
    QSqlQuery tmp_sil;
    tmp_sil.prepare("DELETE FROM kitaplar WHERE id = " + getCurrentId() );
    setSilSorgusu(tmp_sil);

}
kitaplar::kitaplar(const QString & id,QString ad,QString isbn,QString barkod,QDate yayin_tarihi,int adet,QString raf, int baski_sayisi,int giris_sekli,QDate giris_tarihi,QString ek, int yayinci,int kategori) {
    setCurrentId(id);
//gÃ¼ncelleme olayÄ±
    QSqlQuery tmp_guncelle;
    tmp_guncelle.prepare("UPDATE kitaplar SET ad=:ad, isbn=:isbn, barkod=:barkod, yayin_tarihi=:yayin_tarihi, adet=:adet, raf=:raf, baski_sayisi=:baski_sayisi, giris_sekli=:giris_sekli,giris_tarihi=:giris_tarihi, ek=:ek, yayinci=:yayinci,  kategori=:kategori WHERE  id = " + getCurrentId() );
    tmp_guncelle.bindValue(":ad", ad);
    tmp_guncelle.bindValue(":isbn",isbn);
    tmp_guncelle.bindValue(":barkod",barkod);
    tmp_guncelle.bindValue(":yayin_tarihi",yayin_tarihi);
    tmp_guncelle.bindValue(":adet",adet);
    tmp_guncelle.bindValue(":raf",raf);
    tmp_guncelle.bindValue(":baski_sayisi",baski_sayisi);
    tmp_guncelle.bindValue(":giris_sekli",giris_sekli);
    tmp_guncelle.bindValue(":giris_tarihi",giris_tarihi);
    tmp_guncelle.bindValue(":ek",ek);
    tmp_guncelle.bindValue(":yayinci",yayinci);
    tmp_guncelle.bindValue(":kategori",kategori);
    setGuncelleSorgusu(tmp_guncelle);

}
kitaplar::kitaplar(QString ad,QString isbn,QString barkod,QDate yayin_tarihi,int adet,QString raf, int baski_sayisi,int giris_sekli,QDate giris_tarihi,QString ek, int yayinci,int kategori) {

    //insert olayÄ± burada
    QSqlQuery tmp_kaydet;
    tmp_kaydet.prepare("INSERT INTO kitaplar ( ad, isbn, barkod, yayin_tarihi, adet, raf, baski_sayisi, giris_sekli, giris_tarihi, ek, yayinci,kategori )"
                       "VALUES (  :ad, :isbn, :barkod, :yayin_tarihi, :adet, :raf, :baski_sayisi, :giris_sekli, :giris_tarihi, :ek, :yayinci, :kategori )");
    tmp_kaydet.bindValue(":ad", ad);
    tmp_kaydet.bindValue(":isbn",isbn);
    tmp_kaydet.bindValue(":barkod",barkod);
    tmp_kaydet.bindValue(":yayin_tarihi",yayin_tarihi);
    tmp_kaydet.bindValue(":adet",adet);
    tmp_kaydet.bindValue(":raf",raf);
    tmp_kaydet.bindValue(":baski_sayisi",baski_sayisi);
    tmp_kaydet.bindValue(":giris_sekli",giris_sekli);
    tmp_kaydet.bindValue(":giris_tarihi",giris_tarihi);
    tmp_kaydet.bindValue(":ek",ek);
    tmp_kaydet.bindValue(":yayinci",yayinci);
    tmp_kaydet.bindValue(":kategori",kategori);
    setKaydetSorgusu(tmp_kaydet);
    //insert olayÄ± burda biter


}
void kitaplar::lookfor(int i,QString text,QString mod) {
    QLocale turk(QLocale::Turkish,QLocale::Turkey);
    QString lowerText = text.toLower();
    QString upperText = text.toUpper();
    QString column = turk.toString ( i+1 );
    QSqlQuery tmp_arama;
    QString find_str;

    find_str.append("lower(ad) LIKE '%"+lowerText+"%'");
    find_str.append("OR upper(ad) LIKE '%"+upperText+"%'");


    //find_str.append("OR lower(isbn) LIKE '%"+lowerText+"%'");
    //find_str.append("OR upper(isbn) LIKE '%"+upperText+"%'");

    find_str.append("OR lower(barkod) LIKE '%"+lowerText+"%'");
    find_str.append("OR upper(barkod) LIKE '%"+upperText+"%'");

    //find_str.append("OR lower(yayin_tarihi) LIKE '%"+lowerText+"%'");
    //find_str.append("OR upper(yayin_tarihi) LIKE '%"+upperText+"%'");

    find_str.append("OR lower(raf) LIKE '%"+lowerText+"%'");
    find_str.append("OR upper(raf) LIKE '%"+upperText+"%'");


    find_str.append(" ORDER by "+ column + mod);

    tmp_arama.prepare("SELECT * FROM kitaplar WHERE "+find_str);
    //qDebug("SELECT * FROM kitaplar WHERE "+find_str);
    setAramaSorgusu(tmp_arama);

}
