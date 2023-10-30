#ifndef KATEGORI_H
#define KATEGORI_H
#include "libdbBase.h"
class kategori:public libdbBase {
    Q_OBJECT
public:
    kategori();
    kategori(QString ad, QString ek);//Kaydetme iÃ§in
    kategori(const QString & id);//Silme iÃ§in
    kategori(const QString & id, QString ad, QString ek);//GÃ¼ncelleme iÃ§in
private:
public slots:
    void lookfor(int i,QString text,QString mod);

};
#endif
