#include "anaPencere.h"
anaPencere::anaPencere() {
    mdiArea = new QMdiArea;
    setCentralWidget(mdiArea);

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    oduncver();
}

void anaPencere::createActions() {
    kitaplarAct = new QAction(QIcon(":/ikonlar/contents.png"), trUtf8("&Kitaplar"), this);
    kitaplarAct->setStatusTip(trUtf8("Kitap Penceresi"));
    connect(kitaplarAct, SIGNAL(triggered()), this, SLOT(kitaplar()));

    yazarlarAct = new QAction(QIcon(":/ikonlar/edit.png"), trUtf8("&Yazarlar"), this);
    yazarlarAct->setStatusTip(trUtf8("Yazarlar Penceresi"));
    connect(yazarlarAct, SIGNAL(triggered()), this, SLOT(yazarlar()));

    uyelerAct = new QAction(QIcon(":/ikonlar/agt_family.png"), trUtf8("&Üyeler"), this);
    uyelerAct->setStatusTip(trUtf8("Üyeler Penceresi"));
    connect(uyelerAct, SIGNAL(triggered()), this, SLOT(uyeler()));

    oduncVerAct = new QAction(QIcon(":/ikonlar/share.png"), trUtf8("Ödünç &Ver"), this);
    oduncVerAct->setStatusTip(trUtf8("Kitap Ödünç Ver"));
    connect(oduncVerAct, SIGNAL(triggered()), this, SLOT(oduncver()));

    geriAlAct = new QAction(QIcon(":/ikonlar/reload.png"), trUtf8("&Geri Al"), this);
    geriAlAct->setStatusTip(trUtf8("Kitap Geri Al"));
    connect(geriAlAct, SIGNAL(triggered()), this, SLOT(gerial()));

    yayineviAct= new QAction(QIcon(":/ikonlar/yayinevi.png"), trUtf8("Yayınevi"), this);
    yayineviAct->setStatusTip(trUtf8("Yayınevi Penceresi"));
    connect(yayineviAct, SIGNAL(triggered()), this, SLOT(yayinevi()));

    sabitSinifAct= new QAction(QIcon(":/ikonlar/sinif.png"), trUtf8("Sınıf/Kurum"), this);
    sabitSinifAct->setStatusTip(trUtf8("Sınıf/Kurum Penceresi"));
    connect(sabitSinifAct, SIGNAL(triggered()), this, SLOT(sinif()));

    sabitKategoriAct=new QAction(QIcon(":/ikonlar/kitapkategori.png"), trUtf8("Kitap Kategori"), this);
    sabitKategoriAct->setStatusTip(trUtf8("Kitap Kategori Penceresi"));
    connect(sabitKategoriAct, SIGNAL(triggered()), this, SLOT(kategori()));


    sabitKitapgirissekli=new QAction(QIcon(":/ikonlar/kitapgirissekli.png"), trUtf8("Kitap Giriş Şekli"), this);
    sabitKitapgirissekli->setStatusTip(trUtf8("Kitap Giriş Şekli Penceresi"));
    connect(sabitKitapgirissekli, SIGNAL(triggered()), this, SLOT(kitapgirissekli()));

    raporUyelerAct= new QAction(QIcon(":/ikonlar/uyelist.png"), trUtf8("Raporlar"), this);
    raporUyelerAct->setStatusTip(trUtf8("Raporlar"));
    connect(raporUyelerAct, SIGNAL(triggered()), this, SLOT(raporUyeListesi()));

    exitAct = new QAction(trUtf8("Çıkış"), this);
    exitAct->setShortcut(trUtf8("Ctrl+Q"));
    exitAct->setStatusTip(trUtf8("Programdan Çık"));
    connect(exitAct, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));


    closeAct = new QAction(trUtf8("Kapat"), this);
    closeAct->setShortcut(trUtf8("Ctrl+F4"));
    closeAct->setStatusTip(trUtf8("Aktif Pencereyi Kapat"));
    connect(closeAct, SIGNAL(triggered()),mdiArea, SLOT(closeActiveSubWindow()));

    closeAllAct = new QAction(trUtf8("Hepsini Kapat"), this);
    closeAllAct->setStatusTip(trUtf8("Tüm Pencereleri Kapat"));
    connect(closeAllAct, SIGNAL(triggered()),mdiArea, SLOT(closeAllSubWindows()));

    tileAct = new QAction(trUtf8("&Diz"), this);
    tileAct->setStatusTip(trUtf8("Pencereleri Diz"));
    connect(tileAct, SIGNAL(triggered()), mdiArea, SLOT(tileSubWindows()));

    cascadeAct = new QAction(trUtf8("&Sırala"), this);
    cascadeAct->setStatusTip(trUtf8("Pencereleri Sırala"));
    connect(cascadeAct, SIGNAL(triggered()), mdiArea, SLOT(cascadeSubWindows()));

    nextAct = new QAction(trUtf8("Sonraki"), this);
    nextAct->setStatusTip(trUtf8("Bir Sonraki Pencere"));
    connect(nextAct, SIGNAL(triggered()),mdiArea, SLOT(activateNextSubWindow()));

    previousAct = new QAction(trUtf8("Önceki"), this);
    previousAct->setStatusTip(trUtf8("Bir Önceki Pencere"));
    connect(previousAct, SIGNAL(triggered()),mdiArea, SLOT(activatePreviousSubWindow()));

    separatorAct = new QAction(this);
    separatorAct->setSeparator(true);

    aboutAct = new QAction(QIcon(":/ikonlar/info.png"),trUtf8("&Hakkında"), this);
    aboutAct->setStatusTip(trUtf8("Program Hakkında"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

}
void anaPencere::createToolBars() {
    formBar = addToolBar(tr("Formlar"));
    formBar->addAction(yazarlarAct);
    formBar->addAction(kitaplarAct);
    formBar->addAction(uyelerAct);
    formBar->addSeparator();
    formBar->addAction(oduncVerAct);
    formBar->addAction(geriAlAct);

    raporBar = addToolBar(tr("Raporlar"));
    raporBar->addAction(raporUyelerAct);
}
void anaPencere::createMenus() {
    formMenu = menuBar()->addMenu(tr("&Formlar"));
    formMenu->addAction(yazarlarAct);
    formMenu->addAction(kitaplarAct);
    formMenu->addAction(uyelerAct);
    formMenu->addSeparator();
    formMenu->addAction(oduncVerAct);
    formMenu->addAction(geriAlAct);
    formMenu->addSeparator();

    formMenu->addAction(exitAct);
    formMenu->addSeparator();
    raporMenu = menuBar()->addMenu(trUtf8("&Raporlar"));
    raporMenu->addAction(raporUyelerAct);
    raporMenu->addSeparator();

    sabitMenu = menuBar()->addMenu(trUtf8("&Sabit Değerler"));
    sabitMenu->addAction(sabitSinifAct);
    sabitMenu->addAction(yayineviAct);
    sabitMenu->addAction(sabitKategoriAct);
    sabitMenu->addAction(sabitKitapgirissekli);

    windowMenu = menuBar()->addMenu(trUtf8("&Pencereler"));
    updateWindowMenu();
    connect(windowMenu, SIGNAL(aboutToShow()), this, SLOT(updateWindowMenu()));

    helpMenu = menuBar()->addMenu(trUtf8("&Yardım"));
    helpMenu->addAction(aboutAct);
}
void anaPencere::createStatusBar() {
    statusBar()->showMessage(trUtf8("Kütüphane Üye Takip YAzılımı"));
}
void anaPencere::updateWindowMenu() {
    windowMenu->clear();
    windowMenu->addAction(closeAct);
    windowMenu->addAction(closeAllAct);
    windowMenu->addSeparator();
    windowMenu->addAction(tileAct);
    windowMenu->addAction(cascadeAct);
    windowMenu->addSeparator();
    windowMenu->addAction(nextAct);
    windowMenu->addAction(previousAct);
    windowMenu->addAction(separatorAct);

}
void anaPencere::about() {
    formAbout *fa= new formAbout(this);
    fa->show();

}
void anaPencere::yazarlar() {
    pencereYazarlar *py = new pencereYazarlar();
    mdiArea->addSubWindow(py);
    py->show();

}
void anaPencere::kitaplar() {
    pencereKitaplar *pk = new pencereKitaplar();
    mdiArea->addSubWindow(pk);
    pk->show();
}

void anaPencere::oduncver() {
    formOduncVer *fo = new formOduncVer();
    mdiArea->addSubWindow(fo);
    fo->show();
}
void anaPencere::uyeler() {
    pencereUyeler *pu =new pencereUyeler();
    mdiArea->addSubWindow(pu);
    pu->show();
}
void anaPencere::yayinevi() {
    pencereYayinevi *py =new pencereYayinevi();
    mdiArea->addSubWindow(py);
    py->show();
}
void anaPencere::sinif() {
    pencereSinif *ps =new pencereSinif();
    mdiArea->addSubWindow(ps);
    ps->show();

}
void anaPencere::kategori() {
    pencereKategori *pk =new pencereKategori();
    mdiArea->addSubWindow(pk);
    pk->show();
}

void anaPencere::kitapgirissekli() {
    pencereKitapgirissekli *pg =new pencereKitapgirissekli();
    mdiArea->addSubWindow(pg);
    pg->show();
}
void anaPencere::gerial() {
    formGeriAl *fg=new formGeriAl();
    mdiArea->addSubWindow(fg);
    fg->show();

}
void anaPencere::raporUyeListesi() {
    raporUyeler *ru = new raporUyeler(0);
    mdiArea->addSubWindow(ru);
    ru->show();

}
