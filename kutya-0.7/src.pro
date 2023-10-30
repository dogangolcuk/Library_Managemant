SOURCES += main.cpp \
anaPencere.cpp \
libdbBase.cpp \
kitaplar.cpp \
yazarlar.cpp \
uyeler.cpp \
yayinevi.cpp \
 guiTools.cpp \
 oduncver.cpp \
 gerial.cpp \
 getirilmeyenler.cpp \
 sinif.cpp \
 kategori.cpp \
 kitapgirissekli.cpp
TEMPLATE = app
CONFIG += warn_on \
	  thread \
          qt

QT += sql \
gui \
 xml \
 network\
  webkit
FORMS += formYazarlar.ui \
anaPencere.ui \
formKitaplar.ui \
widgetYayinciSec.ui \
YazarSec.ui \
formUyeler.ui \
formYayinevi.ui \
formGeriAl.ui \
formOduncVer.ui \
 raporUyeler.ui \
 formSinif.ui \
 formKategori.ui \
 formKitapgirissekli.ui \
 f_hakkinda.ui
HEADERS += anaPencere.h \
formYazarSec.h \
formOduncVer.h \
formGeriAl.h \
libdbBase.h \
kitaplar.h \
yazarlar.h \
pencereYazarlar.h \
uyeler.h \
pencereUyeler.h \
yayinevi.h \
pencereYayinevi.h \
 pencereKitaplar.h \
 raporUyeler.h \
 guiTools.h \
 oduncver.h \
 gerial.h \
 getirilmeyenler.h \
 sinif.h \
 pencereSinif.h \
 kategori.h \
 pencereKategori.h \
 kitapgirissekli.h \
 pencereKitapgirissekli.h \
 formAbout.h

DESTDIR = .

TRANSLATIONS += eng.ts

OBJECTS_DIR = obj

UI_DIR = ui

MOC_DIR = moc

RESOURCES += ikonlar/ikon.qrc

TARGET = kutya

