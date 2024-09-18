#ifndef OUTFITMANAGER_H
#define OUTFITMANAGER_H

#include <QObject>
#include "clothes.h"

class OutfitManager : public QObject
{
    Q_OBJECT

public:
    explicit OutfitManager(QObject *parent = nullptr);
    QString getOutfitImage(const double &temperature, const QString &style);

private:
    Clothes *clothes;
    QString classifyTemperature(double temperature);
};

#endif // OUTFITMANAGER_H
