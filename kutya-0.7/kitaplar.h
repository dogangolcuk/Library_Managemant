#include "libdbBase.h"
class kitaplar:public libdbBase {
// Q_OBJECT
public:
    kitaplar();
    kitaplar(QString ad,QString isbn,QString barkod,QDate yayin_tarihi,int adet,QString raf, int baski_sayisi,int giris_sekli,QDate giris_tarihi,QString ek, int yayinci,int kategori);//Kaydetme iÃ§in

    kitaplar(const QString & id);//Silme iÃ§in
    kitaplar(const QString & id,QString ad,QString isbn,QString barkod,QDate yayin_tarihi,int adet,QString raf, int baski_sayisi,int giris_sekli,QDate giris_tarihi,QString ek, int yayinci,int kategori);//GÃ¼ncelleme iÃ§in
//Arama iÃ§in
    void lookfor(int,QString,QString);
private:
// public slots:

};
