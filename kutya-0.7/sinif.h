#ifndef SINIF_H
#define SINIF_H
#include "libdbBase.h"
class sinif:public libdbBase {
    Q_OBJECT
public:
    sinif();
    sinif(QString ad, QString ek);//Kaydetme iÃ§in
    sinif(const QString & id);//Silme iÃ§in
    sinif(const QString & id, QString ad, QString ek);//GÃ¼ncelleme iÃ§in
private:
public slots:
    void lookfor(int i,QString text,QString mod);

};
#endif
