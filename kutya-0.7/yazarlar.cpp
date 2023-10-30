#include "yazarlar.h"
yazarlar::yazarlar() {

}
yazarlar::yazarlar(const QString & id) {
    setCurrentId(id);
//delete olayÄ±
    QSqlQuery tmp_sil;
    tmp_sil.prepare("DELETE FROM yazarlar WHERE id =" + getCurrentId() );
    setSilSorgusu(tmp_sil);

}
yazarlar::yazarlar(const QString & id,QString ad, QString soyad, QString ek) {
    setCurrentId(id);
//gÃ¼ncelleme olayÄ±
    QSqlQuery tmp_guncelle;
    tmp_guncelle.prepare("UPDATE yazarlar SET ad=:ad ,soyad=:soyad,ek=:ek WHERE  id = " + getCurrentId() );
    tmp_guncelle.bindValue(":ad", ad);
    tmp_guncelle.bindValue(":soyad",soyad);
    tmp_guncelle.bindValue(":ek",ek);
    setGuncelleSorgusu(tmp_guncelle);

}
yazarlar::yazarlar(QString ad, QString soyad, QString ek) {
    //insert olayÄ± burada
    QSqlQuery tmp_kaydet;
    tmp_kaydet.prepare("INSERT INTO yazarlar ( ad, soyad, ek)"
                       "VALUES (  :ad, :soyad, :ek)");
    tmp_kaydet.bindValue(":ad", ad);
    tmp_kaydet.bindValue(":soyad",soyad);
    tmp_kaydet.bindValue(":ek",ek);
    setKaydetSorgusu(tmp_kaydet);
}
void yazarlar::lookfor(int i,QString text,QString mod) {
    QLocale turk(QLocale::Turkish,QLocale::Turkey);
    QString lowerText = text.toLower();
    QString upperText = text.toUpper();
    QString column = turk.toString ( i+1 );
    QSqlQuery tmp_arama;
    QString find_str;


    find_str.append("lower(ad) LIKE '%"+lowerText+"%'");
    find_str.append("OR upper(ad) LIKE '%"+upperText+"%'");
    find_str.append("OR lower(soyad) LIKE '%"+lowerText+"%'");
    find_str.append("OR upper(soyad) LIKE '%"+upperText+"%'");
    find_str.append(" ORDER by "+ column + mod);
    tmp_arama.prepare("SELECT * FROM yazarlar WHERE "+find_str);
    setAramaSorgusu(tmp_arama);

}
