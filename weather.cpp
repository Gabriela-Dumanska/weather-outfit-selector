#include "weather.h"
#include <QPixmap>
#include <QtDebug>

Weather::Weather(QObject *parent) : QObject(parent)
{

}

QPixmap Weather::weatherIcon(const QString &conditionCode)
{
    if (iconPaths.contains(conditionCode)) {
        return loadPixmapFromDisk(iconPaths.value(conditionCode));
    } else {
        qDebug() << "Unknown weather condition code:" << conditionCode;
        return loadPixmapFromDisk(iconPaths.value("Default"));
    }
}

QPixmap Weather::loadPixmapFromDisk(const QString &filePath)
{
    int size = 200;
    QPixmap pixmap(filePath);
    if (pixmap.isNull()) {
        qDebug() << "Failed to load image from" << filePath;
    }
    return pixmap.scaled(size, size, Qt::KeepAspectRatio);
}
