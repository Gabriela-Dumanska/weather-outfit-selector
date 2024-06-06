#include <QString>
#include <QMap>
#include <QPixmap>

class Weather {
public:
    Weather() {
        icons["Sunny"] = ":/icons/sunny.png";
        icons["Rain"] = ":/icons/rain.png";
    }

    QPixmap toIcon(const QString &condition) const {
        if (icons.contains(condition)) {
            return QPixmap(icons[condition]);
        } else {
            return QPixmap(":/icons/question.png");
        }
    }

private:
    QMap<QString, QString> icons;
};
