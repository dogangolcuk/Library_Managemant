#include "libdbBase.h"
libdbBase::libdbBase() {

}
libdbBase::~libdbBase() {

}
bool libdbBase::dbislem(QSqlQuery sorgu) {
    QSqlDatabase::database().transaction();
    sorgu.exec();
    QSqlError hata = sorgu.lastError();
    if (hata.isValid()) {
        QMessageBox::critical(0, trUtf8(" Veritabanı Hatası"),
                              trUtf8("Bir hata oluştu! Hata ile ilgili bilgiyi aşağıdaki metinden alabilirsiniz.\n\n")
                              + hata.text());
        QSqlDatabase::database().rollback();
        return false;
    }
    QSqlDatabase::database().commit();
    return true;


}
void  libdbBase::setAramaSorgusu(QSqlQuery sorgu) {
    arama_sorgusu=sorgu;

}
void  libdbBase::setKaydetSorgusu(QSqlQuery sorgu) {
    kaydet_sorgusu=sorgu;

}
void  libdbBase::setGuncelleSorgusu(QSqlQuery sorgu) {
    guncelle_sorgusu=sorgu;

}
void  libdbBase::setSilSorgusu(QSqlQuery sorgu) {
    silme_sorgusu=sorgu;
}
QSqlQuery  libdbBase::getAramaSorgusu() {
    return arama_sorgusu;
}
QSqlQuery  libdbBase::getKaydetSorgusu() {
    return kaydet_sorgusu;
}
QSqlQuery  libdbBase::getGuncelleSorgusu() {
    return guncelle_sorgusu;
}
QSqlQuery  libdbBase::getSilSorgusu() {
    return silme_sorgusu;
}
bool libdbBase::Kaydet() {
    return dbislem(getKaydetSorgusu());
}
bool libdbBase::Guncelle() {
    return dbislem(getGuncelleSorgusu());
}
bool libdbBase::Ara() {
    return dbislem(getAramaSorgusu());
}
bool libdbBase::Sil() {
    if (
        QMessageBox::question(
            0,
            trUtf8("Uyarı"),
            trUtf8("Kaydı silmek istediğinizden emin misiniz?"),
            trUtf8("Evet"),
            trUtf8("Hayır"),
            QString(), 1, 0 | QMessageBox::Default | QMessageBox::Escape) == 0
    )
        return  dbislem(getSilSorgusu());
}

void libdbBase::setCurrentId(QString str) {
    currentId=str;

}
QString libdbBase::getCurrentId() {
    return currentId;
}
