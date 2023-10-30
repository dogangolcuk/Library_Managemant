#ifndef GERIAL_H
#define GERIAL_H
#include "libdbBase.h"
class gerial:public libdbBase {
public:
    gerial();
    void lookfor(int,QString,QString);
    gerial(int,QDate alma_tarihi);

};
#endif
