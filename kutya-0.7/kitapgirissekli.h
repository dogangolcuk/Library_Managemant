#ifndef KITAPGIRISSEKLI_H
#define KITAPGIRISSEKLI_H
#include "libdbBase.h"
class kitapgirissekli:public libdbBase {
    Q_OBJECT
public:
    kitapgirissekli();
    kitapgirissekli(QString ad, QString ek);//Kaydetme iÃ§in
    kitapgirissekli(const QString & id);//Silme iÃ§in
    kitapgirissekli(const QString & id, QString ad, QString ek);//GÃ¼ncelleme iÃ§in
private:
public slots:
    void lookfor(int i,QString text,QString mod);

};
#endif
