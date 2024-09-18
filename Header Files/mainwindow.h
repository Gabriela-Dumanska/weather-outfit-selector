#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include "weather.h"
#include "outfitmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void refreshed();
    void onWeatherDataReceived(QNetworkReply *reply);
    void showAddClothing();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *networkManager;
    Weather *weather;
    OutfitManager *outfitManager;
    QMap<QString, QString> cityMap;
};

#endif // MAINWINDOW_H
