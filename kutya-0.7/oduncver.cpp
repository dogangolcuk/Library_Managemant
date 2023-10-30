#include "oduncver.h"
#include <QLocale>
oduncver::oduncver() {

}
oduncver::oduncver(int uyeid, int kitapid, QDate verme_tarihi,QDate alma_tarihi) {
    //insert olayÄ± burada
    QSqlQuery tmp_kaydet;
    tmp_kaydet.prepare("INSERT INTO odunc_al_ver ( uye_id, kitap_id, verme_tarihi, alma_tarihi)"
                       "VALUES (  :uyeid, :kitapid, :verme_tarihi, :alma_tarihi)");
    tmp_kaydet.bindValue(":uyeid", uyeid);
    tmp_kaydet.bindValue(":kitapid", kitapid);
    tmp_kaydet.bindValue(":verme_tarihi",verme_tarihi);
    tmp_kaydet.bindValue(":alma_tarihi",alma_tarihi);
    setKaydetSorgusu(tmp_kaydet);

}
void oduncver::lookforMembers(int i,QString text,QString mod) {
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

    find_str.append(" ORDER by "+ column + mod);
    tmp_arama.prepare("SELECT id,uye_no,ad,soyad FROM uyeler WHERE "+find_str);
    setAramaSorgusu(tmp_arama);

}
void oduncver::lookforBooks(int i,QString text,QString mod) {
    QLocale turk(QLocale::Turkish,QLocale::Turkey);
    QString lowerText = text.toLower();
    QString upperText = text.toUpper();
    QString column = turk.toString ( i+1 );
    QSqlQuery tmp_arama;
    QString find_str;

    find_str.append("lower(ad) LIKE '%"+lowerText+"%'");
    find_str.append("OR upper(ad) LIKE '%"+upperText+"%'");

    find_str.append("OR lower(isbn) LIKE '%"+lowerText+"%'");
    find_str.append("OR upper(isbn) LIKE '%"+upperText+"%'");

    find_str.append("OR lower(barkod) LIKE '%"+lowerText+"%'");
    find_str.append("OR upper(barkod) LIKE '%"+upperText+"%'");

    find_str.append(" ORDER by "+ column + mod);
    tmp_arama.prepare("SELECT id,ad,isbn,barkod,adet FROM kitaplar WHERE "+find_str);
    setAramaSorgusu(tmp_arama);

}
