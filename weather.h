#ifndef WEATHER_H
#define WEATHER_H

#include <QString>
#include <QMap>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class Weather; }
QT_END_NAMESPACE

class Weather {
public:
    Weather();

    QPixmap toIcon(const QString &condition) const;

private:
    QMap<QString, QString> icons;
};

#endif // WEATHER_H
