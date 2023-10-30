#include "uyeler.h"
#include <QLocale>
uyeler::uyeler() {

}
uyeler::uyeler(const QString & id) {
    setCurrentId(id);
//delete olayÄ±
    QSqlQuery tmp_sil;
    tmp_sil.prepare("DELETE FROM uyeler WHERE id =" + getCurrentId() );
    setSilSorgusu(tmp_sil);

}
uyeler::uyeler(const QString & id,QString uye_no, QString ad, QString soyad, int sinif, QDate uyelik_tarihi, QString uyelik_tipi, QString tel, QString ceptel, QString email, QString adres, QString ek_bilgi) {
    setCurrentId(id);
//gÃ¼ncelleme olayÄ±
    QSqlQuery tmp_guncelle;
    tmp_guncelle.prepare("UPDATE uyeler SET uye_no=:uye_no, ad=:ad, soyad=:soyad, sinif=:sinif, uyelik_tarihi=:uyelik_tarihi, uyelik_tipi=:uyelik_tipi, tel=:tel, ceptel=:ceptel, email=:email, adres=:adres ,ek_bilgi=:ek_bilgi WHERE  id = " + getCurrentId() );
    tmp_guncelle.bindValue(":uye_no", uye_no);
    tmp_guncelle.bindValue(":ad",ad);
    tmp_guncelle.bindValue(":soyad",soyad);
    tmp_guncelle.bindValue(":sinif",sinif);
    tmp_guncelle.bindValue(":uyelik_tarihi",uyelik_tarihi);
    tmp_guncelle.bindValue(":uyelik_tipi",uyelik_tipi);
    tmp_guncelle.bindValue(":tel",tel);
    tmp_guncelle.bindValue(":ceptel",ceptel);
    tmp_guncelle.bindValue(":email",email);
    tmp_guncelle.bindValue(":adres",adres);
    tmp_guncelle.bindValue(":ek_bilgi",ek_bilgi);
    setGuncelleSorgusu(tmp_guncelle);

}
uyeler::uyeler(QString uye_no, QString ad, QString soyad, int sinif, QDate uyelik_tarihi, QString uyelik_tipi, QString tel, QString ceptel, QString email, QString adres, QString ek_bilgi) {


    //insert olayÄ± burada
    QSqlQuery tmp_kaydet;
    tmp_kaydet.prepare("INSERT INTO uyeler ( uye_no, ad, soyad, sinif, uyelik_tarihi, uyelik_tipi, tel, ceptel, email, adres, ek_bilgi)"
                       "VALUES ( :uye_no, :ad, :soyad, :sinif, :uyelik_tarihi, :uyelik_tipi, :tel, :ceptel, :email, :adres, :ek_bilgi)");
    tmp_kaydet.bindValue(":uye_no", uye_no);
    tmp_kaydet.bindValue(":ad",ad);
    tmp_kaydet.bindValue(":soyad",soyad);
    tmp_kaydet.bindValue(":sinif",sinif);
    tmp_kaydet.bindValue(":uyelik_tarihi",uyelik_tarihi);
    tmp_kaydet.bindValue(":uyelik_tipi",uyelik_tipi);
    tmp_kaydet.bindValue(":tel",tel);
    tmp_kaydet.bindValue(":ceptel",ceptel);
    tmp_kaydet.bindValue(":email",email);
    tmp_kaydet.bindValue(":adres",adres);
    tmp_kaydet.bindValue(":ek_bilgi",ek_bilgi);
    setKaydetSorgusu(tmp_kaydet);
    //insert olayÄ± burda biter


}

void uyeler::lookfor(int i,QString text,QString mod) {
    QLocale turk(QLocale::Turkish,QLocale::Turkey);
    QString lowerText = text.toLower();
    QString upperText = text.toUpper();
    QString column = turk.toString ( i+1 );
    QSqlQuery tmp_arama;
    QString find_str;

    find_str.append("lower(uye_no) LIKE '%"+lowerText+"%'");
    find_str.append("OR upper(uye_no) LIKE '%"+upperText+"%'");

    find_str.append("OR lower(ad) LIKE '%"+lowerText+"%'");
    find_str.append("OR upper(ad) LIKE '%"+upperText+"%'");

    find_str.append("OR lower(soyad) LIKE '%"+lowerText+"%'");
    find_str.append("OR upper(soyad) LIKE '%"+upperText+"%'");

   // find_str.append("OR lower(sinif) LIKE '%"+lowerText+"%'");
    //find_str.append("OR upper(sinif) LIKE '%"+upperText+"%'");

    //find_str.append("OR lower(adres) LIKE '%"+lowerText+"%'");
    //find_str.append("OR upper(adres) LIKE '%"+upperText+"%'");

    find_str.append(" ORDER by "+ column + mod);
    tmp_arama.prepare("SELECT * FROM uyeler WHERE "+find_str);
    setAramaSorgusu(tmp_arama);

}
