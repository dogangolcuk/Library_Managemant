#include "getirilmeyenler.h"
#include <QLocale>
getirilmeyenler::getirilmeyenler() {

}

void getirilmeyenler::lookfor(int i,QString text,QString mod) {
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

    find_str.append("OR lower(kitap) LIKE '%"+lowerText+"%'");
    find_str.append("OR upper(kitap) LIKE '%"+upperText+"%'");

    find_str.append("OR almatarihi LIKE  '%"+text+"%'");
// 	find_str.append("OR upper(almatarihi) LIKE '%"+upperText+"%'");

    find_str.append("OR vermetarihi LIKE '%"+text+"%'");
// 	find_str.append("OR upper(vermetarihi) LIKE '%"+upperText+"%'");

    find_str.append(" ORDER by "+ column + mod);
    tmp_arama.prepare("SELECT * FROM getirilmeyenler WHERE "+find_str);
    setAramaSorgusu(tmp_arama);

}
