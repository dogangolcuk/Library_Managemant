#include "gerial.h"
#include <QLocale>
gerial::gerial() {

}
gerial::gerial(int id,QDate alma_tarihi) {
//gÃ¼ncelleme olayÄ±
    QSqlQuery tmp_guncelle;
    tmp_guncelle.prepare("UPDATE odunc_al_ver SET verdi_vermedi=true, alma_tarihi= :date WHERE  id=:id"  );
    tmp_guncelle.bindValue(":date", alma_tarihi);
    tmp_guncelle.bindValue(":id",id);
    setGuncelleSorgusu(tmp_guncelle);

}
void gerial::lookfor(int i,QString text,QString mod) {
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
