#include <QMdiArea>
#include <QMainWindow>
#include <QMdiSubWindow>
#include <QAction>
#include <QMenu>
#include <QSignalMapper>
#include "raporUyeler.h"
#include "pencereKitaplar.h"
#include "pencereYazarlar.h"
#include "pencereUyeler.h"
#include "pencereYayinevi.h"
#include "pencereSinif.h"
#include "pencereKategori.h"
#include "pencereKitapgirissekli.h"
#include "formGeriAl.h"
#include "formOduncVer.h"
#include "formAbout.h"
class anaPencere : public QMainWindow {
    Q_OBJECT
public:
    anaPencere();
private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    QMdiArea *mdiArea;
    QSignalMapper *windowMapper;

    QMenu *formMenu;
    QMenu *raporMenu;
    QMenu *sabitMenu;
    QMenu *windowMenu;
    QMenu *helpMenu;

    QToolBar *formBar;
    QToolBar *raporBar;
    QToolBar *sabitBar;

    QAction *kitaplarAct;
    QAction *yazarlarAct;
    QAction *uyelerAct;
    QAction *yayineviAct;
    QAction *sabitSinifAct;
    QAction *sabitKategoriAct;
    QAction *sabitKitapgirissekli;
    QAction *oduncVerAct;
    QAction *geriAlAct;
    QAction *raporUyelerAct;
    QAction *exitAct;
    QAction *closeAct;
    QAction *closeAllAct;
    QAction *tileAct;
    QAction *cascadeAct;
    QAction *nextAct;
    QAction *previousAct;
    QAction *separatorAct;
    QAction *aboutAct;
public slots:
    void updateWindowMenu();
    void about();
    void yazarlar();
    void kitaplar();
    void oduncver();
    void uyeler();
    void yayinevi();
    void sinif();
    void kategori();
    void kitapgirissekli();
    void gerial();
    void raporUyeListesi();
};
