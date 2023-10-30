#ifndef ODUNCVER_H
#define ODUNCVER_H
#include "libdbBase.h"
class oduncver:public libdbBase {
// Q_OBJECT
public:
    oduncver();
//kaydetme iÃ§in
    oduncver(int uyeid, int kitapid, QDate verme_tarihi,QDate alma_tarihi);
    void lookforMembers(int,QString,QString);
    void lookforBooks(int,QString,QString);
private:

// public slots:


};
#endif
