#include "outfitmanager.h"
#include <QList>
#include <QRandomGenerator>

OutfitManager::OutfitManager(QObject *parent) : QObject(parent), clothes(new Clothes(this)) {}

QString OutfitManager::classifyTemperature(double temperature) {
    if (temperature < 5) {
        return "Mroźnie";
    } else if (temperature < 10) {
        return "Zimno";
    } else if (temperature < 18) {
        return "Chłodno";
    } else if (temperature < 24) {
        return "Pogodnie";
    } else if (temperature < 29) {
        return "Ciepło";
    } else {
        return "Gorąco";
    }
}

QString OutfitManager::getOutfitImage(const double &temperature, const QString &style) {
    QString weatherCondition = classifyTemperature(temperature);

    QStringList categories = {"Hats", "Tops", "Bottoms", "Shoes"};
    QStringList outfitImages;

    for (const QString &category : categories) {
        QList<Clothes::ClothingItem> items = clothes->getClothingItems(category, weatherCondition, style);
        if (!items.isEmpty()) {
            int randomIndex = QRandomGenerator::global()->bounded(items.size());
            outfitImages.append(items[randomIndex].image_path);
        }
    }

    return outfitImages.join("\n");
}
