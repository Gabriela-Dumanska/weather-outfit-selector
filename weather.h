#ifndef WEATHER_H
#define WEATHER_H

#include <QObject>
#include <QPixmap>
#include <QMap>

class Weather : public QObject
{
    Q_OBJECT
public:
    explicit Weather(QObject *parent = nullptr);
    QPixmap weatherIcon(const QString &conditionCode);

private:
    QPixmap loadPixmapFromDisk(const QString &filePath);

    QMap<QString, QString> iconPaths = {
        {"Sunny", "C:/Users/gabul/Documents/Programowanie/Cpp/SkyStyle/resources/icons/sunny.png"},
        {"Clear", "C:/Users/gabul/Documents/Programowanie/Cpp/SkyStyle/resources/icons/sunny.png"},
        {"Partly cloudy", "C:/Users/gabul/Documents/Programowanie/Cpp/SkyStyle/resources/icons/partialy_cloudy.png"},
        {"Cloudy", "C:/Users/gabul/Documents/Programowanie/Cpp/SkyStyle/resources/icons/cloudy.png"},
        {"Overcast", "C:/Users/gabul/Documents/Programowanie/Cpp/SkyStyle/resources/icons/cloudy.png"},
        {"Mist", "C:/Users/gabul/Documents/Programowanie/Cpp/SkyStyle/resources/icons/cloudy.png"},
        {"Default", "C:/Users/gabul/Documents/Programowanie/Cpp/SkyStyle/resources/icons/rain.png"}
    };
};

#endif // WEATHER_H
