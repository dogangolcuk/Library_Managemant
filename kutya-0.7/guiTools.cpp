#include "guiTools.h"
guiTools::guiTools() {
    yeni_kayit=true;
    guncelle=true;
    azalan=true;
// int EnSonSiralama;
// QString EnSonAramaMod;
}

void guiTools::widgetClear(const QList<QWidget *> & widgetList) {
    for (int i = 0; i < widgetList.size(); ++i) {
        QString wname =widgetList.at(i)->metaObject()->className();
// qDebug()<< wname;
        if ( wname == "QLineEdit")
            qobject_cast<QLineEdit *>(widgetList.at(i))->clear();
        if ( wname == "QTextEdit")
            qobject_cast<QTextEdit *>(widgetList.at(i))->clear();
        if ( wname == "QSpinBox")
            qobject_cast<QSpinBox *>(widgetList.at(i))->clear();

    }
}
void guiTools::widgetSetReadOnly(const QList<QWidget *> & widgetList , int durum) {

    for (int i = 0; i < widgetList.size(); ++i) {
        QString wname =widgetList.at(i)->metaObject()->className();
// 	qDebug()<< wname;

        if ( wname == "QLineEdit")
            qobject_cast<QLineEdit *>(widgetList.at(i))->setReadOnly(durum);
        if ( wname == "QTextEdit")
            qobject_cast<QTextEdit *>(widgetList.at(i))->setReadOnly(durum);
        if ( wname == "QSpinBox")
            qobject_cast<QSpinBox *>(widgetList.at(i))->setReadOnly(durum);
        if ( wname == "QComboBox")
            qobject_cast<QComboBox *>(widgetList.at(i))->setEnabled(!durum);
// 	if ( wname == "QToolButton")
//             qobject_cast<QToolButton *>(widgetList.at(i))->setEnabled(durum);
    }

}
void guiTools::widgetMapData(QAbstractItemModel * model,const QList<QWidget *> & widgetList) {
    mapper = new QDataWidgetMapper;
    mapper->setModel(model);
    for (int i = 0; i < widgetList.size(); ++i) {
        mapper->addMapping(widgetList.at(i), i+1);
    }

}
void guiTools::modInitial() {
    kaydet->setEnabled (true);
    degistir->setEnabled (true);
    yeni_kayit=true;
    guncelle=true;
    degistir->setText(trUtf8("Değiştir"));
    kaydet->setText(trUtf8("Yeni Kayıt"));
    widgetSetReadOnly(wList,1);

}
bool guiTools::modSave() {
    if (yeni_kayit) {
        kaydet->setText(trUtf8("Kaydet"));
        widgetSetReadOnly(wList,0);
        widgetClear(wList);
        yeni_kayit=false;
        degistir->setEnabled (false);
        return false;
    } else {
        kaydet->setText(trUtf8("Yeni Kayıt"));
        widgetSetReadOnly(wList,1);
        yeni_kayit=true;
        degistir->setEnabled (true);
        return true;
    }

}
bool guiTools::modChange() {
    if (guncelle) {
        degistir->setText(trUtf8("Onayla"));
        kaydet-> setEnabled (false);
//Bilgi girilebilir.
        widgetSetReadOnly(wList,0);
        guncelle=false;
        return false;
    } else {
        degistir->setText(trUtf8("Değiştir"));
        kaydet-> setEnabled (true);
//Bilgi girilecek yerler aktif deÃÂÃÂil.
        widgetSetReadOnly(wList,1);
//Bilgi girilecek yerler aktif deÃÂÃÂil.
        guncelle=true;
        return true;

    }
}
void guiTools::modSaveError() {
    kaydet->setText(trUtf8("Kaydet"));
    widgetSetReadOnly(wList,0);
//  		widgetClear(wList);
    yeni_kayit=false;
    degistir->setEnabled (false);
}
bool guiTools::modAzalan() {
    if (azalan) {
        azalan=false;
        return false;
    } else {
        azalan=true;
        return true;
    }
}

void guiTools::setSorgu(QString str) {
    sorgu=str;

}
QString guiTools::getSorgu() {
    return sorgu;

}
void guiTools::connectTable(QTableView  *table) {

    sorgu_model = new QSqlQueryModel;
    sorgu_model->setQuery(getSorgu());
    table->setModel(sorgu_model);
    table->show();
    selectionModel = table->selectionModel();
    widgetMapData(sorgu_model,wList);



}

QVariant guiTools::getData(int row) {

    QVariant data = sorgu_model->data ( sorgu_model->index ( selectionModel->currentIndex().row(), row ) );
    return data;

}
QVariant guiTools::getData(QString fieldname) {
    QSqlQuery q(getSorgu());
    QSqlRecord rec = q.record();
    int nameCol = rec.indexOf(fieldname); // index of the field "name"
    QVariant data = sorgu_model->data ( sorgu_model->index ( selectionModel->currentIndex().row(), nameCol ) );
    return data;

}
int guiTools::getFieldCount() {
    QSqlQuery q(getSorgu());
    QSqlRecord rec = q.record();
// qDebug() << "Number of columns: " << rec.count();
    return rec.count();
// int nameCol = rec.indexOf("name"); // index of the field "name"
//  while (q.next())
//      qDebug() << q.value(nameCol).toString(); // output all names

}
QStringList guiTools::getFieldNames() {
    QStringList FieldNames;
    QSqlQuery q(getSorgu());
    QSqlRecord rec = q.record();
    for (int i=0; i<rec.count(); i++)
        FieldNames.append(rec.fieldName(i));

    return FieldNames;
}
int guiTools::getFieldCount(QSqlQuery sorgu) {
    QSqlQuery q(sorgu);
    QSqlRecord rec = q.record();
//   qDebug() << "Number of columns: " << rec.count();
    return rec.count();

}
void guiTools::refreshTable(QSqlQuery  query) {
    sorgu_model->setQuery(query);
//     sorgu_model->query();

}
//Buradaki "key" ana tablodaki alan ismidir.
void guiTools::setHeader() {
    int fieldcount =getFieldCount();
    for (int i = 0; i < fieldcount; ++i) {
        sorgu_model->setHeaderData(i, Qt::Horizontal, headerdata.at(i));

    }


}
QStringList guiTools::getDataList(QString key,QString query) {
    QSqlQuery *sorgu = new QSqlQuery;
    QString key_id = getData(key).toString();
// qDebug()<<"key="<<key_id;
    sorgu->prepare(query);
    sorgu->bindValue(":key_id", key_id);
    sorgu->exec();
    QStringList list;
    QString tmp_str;
    int fieldcount =getFieldCount(*sorgu);
    while (sorgu->next()) {
        for (int i = 0; i < fieldcount; ++i) {
            QString tmp=sorgu->value(i).toString();
            tmp_str.append(tmp+" ");

        }
        list.append(tmp_str);
        tmp_str.clear();
    }
    return list;
}
void guiTools::connectComboBoxDb(QComboBox * cb,QString sorgu) {
    QSqlQueryModel *modelForeignKey = new QSqlQueryModel;
    modelForeignKey->setQuery(sorgu);
    cb->setModel(modelForeignKey);
}
