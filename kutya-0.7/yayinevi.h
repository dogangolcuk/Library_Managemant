#ifndef YAYINEVI_H
#define YAYINEVI_H
#include "libdbBase.h"
class yayinevi:public libdbBase {
    Q_OBJECT
public:
    yayinevi();
    yayinevi(QString ad, QString ek);//Kaydetme iÃ§in
    yayinevi(const QString & id);//Silme iÃ§in
    yayinevi(const QString & id, QString ad, QString ek);//GÃ¼ncelleme iÃ§in
private:
public slots:
    void lookfor(int i,QString text,QString mod);

};
#endif
