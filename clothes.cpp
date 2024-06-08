#include "clothes.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QtDebug>
#include <QCoreApplication>

Clothes::Clothes(QObject *parent) : QObject(parent) {
    QString dbPath = "C:/Users/gabul/Documents/Programowanie/Cpp/SkyStyle/resources/Clothes";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);
    if (!db.open()) {
        qDebug() << "Error: Could not open database.";
    } else {
        qDebug() << "Database opened successfully.";
    }
}

Clothes::~Clothes() {
    db.close();
}

QList<Clothes::ClothingItem> Clothes::getClothingItems(const QString &category, const QString &weatherCondition, const QString &style) {
    QList<ClothingItem> items;
    QString queryStr = QString("SELECT weather_conditions, style, image_path FROM %1 WHERE weather_conditions LIKE :weather AND style LIKE :style").arg(category);
    QSqlQuery query;
    query.prepare(queryStr);
    query.bindValue(":weather", "%" + weatherCondition + "%");
    query.bindValue(":style", "%" + style + "%");

    if (query.exec()) {
        while (query.next()) {
            ClothingItem item;
            item.image_path = query.value("image_path").toString();
            if (category == "Tops") {
                item.whole_body = query.value("whole_body").toString();
            }
            items.append(item);
        }
    } else {
        qDebug() << "Error: " << query.lastError().text();
    }

    return items;
}
