#ifndef GUITOOLS_H
#define GUITOOLS_H
#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QtSql>
#include <QHeaderView>
#include <QtGui/QComboBox>
class guiTools:public QWidget {
    Q_OBJECT
public:
    guiTools();
    QDataWidgetMapper *mapper ;
    QPushButton *kaydet;
    QPushButton *degistir;
    QList<QWidget *> wList;
    QStringList headerdata;
    QSqlQueryModel *sorgu_model;
    QItemSelectionModel *selectionModel ;
private:
    bool yeni_kayit;
    bool guncelle;
    bool azalan;
    QString sorgu;

public slots:
    void widgetClear(const QList<QWidget *> & widgetList);
    void widgetMapData(QAbstractItemModel * model ,const QList<QWidget *> & widgetList);
    void widgetSetReadOnly(const QList<QWidget *> & widgetList , int durum);
    void modInitial();
    bool modSave();
    bool modChange();
    bool modAzalan();
    void modSaveError();
    void setSorgu(QString str);
    QString getSorgu();
    void connectTable(QTableView *table);
    void refreshTable(QSqlQuery  query);
    QVariant getData(int);
    QVariant getData(QString);
    int getFieldCount();//ana tablonun alanlarÃÂ±nÃÂ±n sayÃÂ±sÃÂ±nÃÂ± verir.
    int getFieldCount(QSqlQuery);
    QStringList getDataList(QString key,QString query);
    void setHeader();
    QStringList getFieldNames();
    void connectComboBoxDb(QComboBox * cb,QString sorgu);
};
#endif
