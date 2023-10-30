#include <QApplication>
#include "anaPencere.h"
#include <QSettings>
#include <QTranslator>
#include <QProcess>
#include <QMessageBox>
int main(int argc, char *argv[]) {
    QApplication app(argc,argv);
    app.setWindowIcon(QIcon(":/ikonlar/cache.png"));
//    	QTranslator translator;
//    	translator.load("langPath/eng");
//     	app.installTranslator(&translator);


    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("kutuphane");
    db.setUserName("postgres");
//      db.setPassword("yetli");
    bool ok = db.open();
    if (ok)
        qDebug("Veritabanı bağlandı");
    else {
        qDebug("Bağlantıda hata ");
        QSqlError hata =db.lastError();
        if (hata.isValid() )
            if (
                QMessageBox::question (
                    0,
                    QObject::trUtf8 ( "Uyarı-Veritabanına Bağlantı Kurulamadı." ),
                    QObject::trUtf8 ( ""
                                      "Veritabanınız Mevcut ise PostgreSQL servisini "         "başlatmayı deneyin.\nİlk kurulum yapıyorsanız yeni"
                                      " veritabanı oluşturmanız gerekir.\n  "
                                      "Yeni bir veritabanı oluşturulsun mu?" ),
                    QObject::trUtf8 ( "Evet" ),
                    QObject::trUtf8 ( "Hayır" ),
                    QString(), 1, 0 | QMessageBox::Default | QMessageBox::Escape ) == 0
            ) {
                QProcess *myProcess = new QProcess();
                QString program = "kdesu";
                QStringList arguments;
                arguments << "python" << "/tmp/kutyadbkur.py";
                myProcess->start(program , arguments);
            }
        if (!db.open()) {
            QMessageBox::information ( 0, QString::fromUtf8 ( "Uyarı" ),
                                       QString::fromUtf8 ( "\nProgramı Yeniden Başlatınız." ),
                                       QMessageBox::Close );
            return false;

        }
    }
    anaPencere form ;
    form.show();
    return app.exec();

}

