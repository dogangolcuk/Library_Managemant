#include "libdbBase.h"
class uyeler:public libdbBase {
// Q_OBJECT
public:
    uyeler();
//Kaydetme iÃ§in
    uyeler(QString uye_no, QString ad, QString soyad, int sinif, QDate uyelik_tarihi, QString uyelik_tipi, QString tel, QString ceptel, QString email, QString adres, QString ek_bilgi);
//Silme iÃ§in
    uyeler(const QString & id);
//GÃ¼ncelleme iÃ§in
    uyeler(const QString & id,QString uye_no, QString ad, QString soyad, int sinif, QDate uyelik_tarihi, QString uyelik_tipi, QString tel, QString ceptel, QString email, QString adres, QString ek_bilgi);
//Arama iÃ§in
    void lookfor(int,QString,QString);
private:

// public slots:


};
