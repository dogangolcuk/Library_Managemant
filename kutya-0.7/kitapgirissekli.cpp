#include "kitapgirissekli.h"
kitapgirissekli::kitapgirissekli() {

}
kitapgirissekli::kitapgirissekli(const QString & id) {
    setCurrentId(id);
//delete olayÄ±
    QSqlQuery tmp_sil;
    tmp_sil.prepare("DELETE FROM kitapgirissekli WHERE id =" + getCurrentId() );
    setSilSorgusu(tmp_sil);

}
kitapgirissekli::kitapgirissekli(const QString & id,QString ad, QString ek) {
    setCurrentId(id);
//gÃ¼ncelleme olayÄ±
    QSqlQuery tmp_guncelle;
    tmp_guncelle.prepare("UPDATE kitapgirissekli SET ad=:ad ,ek=:ek WHERE  id = " + getCurrentId() );
    tmp_guncelle.bindValue(":ad", ad);
    tmp_guncelle.bindValue(":ek",ek);
    setGuncelleSorgusu(tmp_guncelle);

}
kitapgirissekli::kitapgirissekli(QString ad, QString ek) {

    //insert olayÄ± burada
    QSqlQuery tmp_kaydet;
    tmp_kaydet.prepare("INSERT INTO kitapgirissekli ( ad, ek)"
                       "VALUES (  :ad,:ek)");
    tmp_kaydet.bindValue(":ad", ad);
    tmp_kaydet.bindValue(":ek", ek);
    setKaydetSorgusu(tmp_kaydet);
}
void kitapgirissekli::lookfor(int i,QString text,QString mod) {
    QLocale turk(QLocale::Turkish,QLocale::Turkey);
    QString lowerText = text.toLower();
    QString upperText = text.toUpper();
    QString column = turk.toString ( i+1 );
    QSqlQuery tmp_arama;
    QString find_str;
    find_str.append("lower(ad) LIKE '%"+lowerText+"%'");
    find_str.append("OR upper(ad) LIKE '%"+upperText+"%'");
    find_str.append(" ORDER by "+ column + mod);
    tmp_arama.prepare("SELECT * FROM kitapgirissekli WHERE "+find_str);
    setAramaSorgusu(tmp_arama);

}
