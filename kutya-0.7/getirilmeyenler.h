#ifndef GETIRILMEYENLER_H
#define GETIRILMEYENLER_H
#include "libdbBase.h"
class getirilmeyenler:public libdbBase {
public:
    getirilmeyenler();
    void lookfor(int,QString,QString);
};
#endif
