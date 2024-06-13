#include "outfitmanager.h"
#include "qsize.h"
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
    QStringList outfitData;
    bool topCoversWholeBody = false;

    for (const QString &category : categories) {
        QList<Clothes::ClothingItem> items = clothes->getClothingItems(category, weatherCondition, style);
        if (!items.isEmpty()) {
            int randomIndex = QRandomGenerator::global()->bounded(items.size());
            QString imagePath = items[randomIndex].image_path;

            QSize itemSize;
            if (category == "Hats") {
                itemSize = QSize(200, 200);
            } else if (category == "Tops") {
                if (items[randomIndex].whole_body == "True") {
                    topCoversWholeBody = true;
                    itemSize = QSize(100, 200);
                } else {
                    itemSize = QSize(200, 200);
                }
            } else if (category == "Bottoms") {
                itemSize = QSize(100, 200);
            } else if (category == "Shoes") {
                itemSize = QSize(200, 200);
            }

            if (imagePath == "clothes_images/filler") {
                continue;
            } else {
                outfitData.append(QString("%1;%2x%3").arg(imagePath).arg(itemSize.width()).arg(itemSize.height()));
            }
        }
    }

    if (topCoversWholeBody) {
        QStringList filteredOutfitData;
        for (const QString &data : outfitData) {
            QStringList parts = data.split(';');
            QString imagePath = parts[0];
            if (!imagePath.contains("Dol") && !imagePath.contains("Dół")) {
                filteredOutfitData.append(data);
            }
        }
        outfitData = filteredOutfitData;
    }

    return outfitData.join("\n");
}
