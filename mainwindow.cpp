#include "mainwindow.h"
#include "addclothing.h"
#include "./ui_mainwindow.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , networkManager(new QNetworkAccessManager(this))
    , weather(new Weather(this))
    , outfitManager(new OutfitManager(this))
{
    ui->setupUi(this);

    connect(ui->pb_refresh, &QPushButton::clicked, this, &MainWindow::refreshed);
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onWeatherDataReceived);
    connect(ui->pb_addclothing, &QPushButton::clicked, this, &MainWindow::showAddClothing);


    cityMap["Warszawa"] = "Warsaw";
    cityMap["Kraków"] = "Cracow";
    cityMap["Tarnów"] = "Tarnow";
    cityMap["Reykjavik"] = "Reykjavik";
    cityMap["Jakarta"] = "Jakarta";

    QStringList cities = {"Kraków", "Warszawa", "Tarnów", "Reykjavik", "Jakarta"};
    ui->cityBox->addItems(cities);

    QStringList styles = {"Codzienny", "Elegancki", "Sportowy"};
    ui->styleBox->addItems(styles);


    refreshed();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete networkManager;
    delete weather;
    delete outfitManager;
}

void MainWindow::refreshed()
{
    const QString apiKey = "b0314acf443a45629a0175154240606";
    QString selectedCity = ui->cityBox->currentText();
    QString englishCity = cityMap.value(selectedCity);
    const QString urlString = QString("http://api.weatherapi.com/v1/current.json?key=%1&q=%2").arg(apiKey, englishCity);

    QUrl url(urlString);
    QNetworkRequest request(url);
    networkManager->get(request);
}

void MainWindow::onWeatherDataReceived(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        ui->weatherLabel->setText("Error fetching weather data");
        reply->deleteLater();
        return;
    }

    QLayoutItem *child;
    while ((child = ui->outfitLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    QJsonObject jsonObj = jsonDoc.object();

    QJsonObject current = jsonObj.value("current").toObject();
    double temperature = current.value("temp_c").toDouble();
    QString condition = current.value("condition").toObject().value("text").toString();
    QString weatherInfo = QString("%1 °C").arg(temperature);

    QPixmap weatherIcon = weather->weatherIcon(condition);
    ui->weatherLabel->setPixmap(weatherIcon);
    ui->weatherLabel2->setText(weatherInfo);

    QString selectedStyle = ui->styleBox->currentText();

    QStringList outfitImages = outfitManager->getOutfitImage(4, selectedStyle).split("\n");

    QList<QSize> itemSizes;
    if (outfitImages.size() == 4) {
        itemSizes = {QSize(200, 200), QSize(200, 200), QSize(100, 200), QSize(200, 200)};
    } else {
        itemSizes = {QSize(200, 200), QSize(100, 200), QSize(200, 200)};
    }

    for (int i = 0; i < outfitImages.size(); ++i) {
        QLabel *imageLabel = new QLabel();
        QPixmap pixmap("C:/Users/gabul/Documents/Programowanie/Cpp/SkyStyle/resources/" + outfitImages[i]);

        imageLabel->setFixedSize(itemSizes[i]);

        pixmap = pixmap.scaled(itemSizes[i], Qt::KeepAspectRatio);

        imageLabel->setScaledContents(true);

        imageLabel->setPixmap(pixmap);
        ui->outfitLayout->addWidget(imageLabel);
    }

    reply->deleteLater();
}

void MainWindow::showAddClothing()
{
    AddClothing dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        // Tutaj możesz dodać kod do przetwarzania danych z dialogu
    }
}
