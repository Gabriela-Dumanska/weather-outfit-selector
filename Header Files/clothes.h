#ifndef CLOTHES_H
#define CLOTHES_H

#include <QObject>
#include <QSqlDatabase>
#include <QList>
#include <QString>

class Clothes : public QObject
{
    Q_OBJECT

public:
    explicit Clothes(QObject *parent = nullptr);
    ~Clothes();

    struct ClothingItem {
        QString image_path;
        QString whole_body;
    };

    QList<ClothingItem> getClothingItems(const QString &category, const QString &weatherCondition, const QString &style);

private:
    QSqlDatabase db;
};

#endif // CLOTHES_H
