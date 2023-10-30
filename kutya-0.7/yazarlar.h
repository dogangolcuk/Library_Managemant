#include "libdbBase.h"
class yazarlar:public libdbBase {
    Q_OBJECT
public:
    yazarlar();
    yazarlar(QString ad, QString soyad, QString ek);//Kaydetme iÃ§in
    yazarlar(const QString & id);//Silme iÃ§in
    yazarlar(const QString & id,QString ad, QString soyad, QString ek);//GÃ¼ncelleme iÃ§in
    void lookfor(int,QString,QString);
private:
public slots:
};
