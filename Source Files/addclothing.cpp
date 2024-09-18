#include "addclothing.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QUuid>

AddClothing::AddClothing(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Dodaj nowy ciuch");

    categoryComboBox = new QComboBox;
    categoryComboBox->addItem("Czapka");
    categoryComboBox->addItem("Góra");
    categoryComboBox->addItem("Dół");
    categoryComboBox->addItem("Buty");

    clothesMap["Czapka"] = "Hats";
    clothesMap["Góra"] = "Tops";
    clothesMap["Dół"] = "Bottoms";
    clothesMap["Buty"] = "Shoes";

    connect(categoryComboBox, &QComboBox::currentTextChanged, this, &AddClothing::onCategoryChanged);

    styleComboBox = new QComboBox;
    styleComboBox->addItem("Sportowy");
    styleComboBox->addItem("Elegancki");
    styleComboBox->addItem("Codzienny");

    weatherComboBox = new QComboBox;
    weatherComboBox->addItem("Mroźno");
    weatherComboBox->addItem("Zimno");
    weatherComboBox->addItem("Chłodno");
    weatherComboBox->addItem("Pogodnie");
    weatherComboBox->addItem("Ciepło");
    weatherComboBox->addItem("Gorąco");

    weatherMap["Mroźno"] = "Mrozno";
    weatherMap["Zimno"] = "Zimno";
    weatherMap["Chłodno"] = "Chlodno";
    weatherMap["Pogodnie"] = "Pogodnie";
    weatherMap["Ciepło"] = "Cieplo";
    weatherMap["Gorąco"] = "Goraco";

    fileLineEdit = new QLineEdit;
    fileLineEdit->setReadOnly(true);

    infoLabel = new QLabel("Zalecamy proporcje 1:1 oraz zdjęcie bez tła.");

    QPushButton *browseButton = new QPushButton("Przeglądaj");
    connect(browseButton, &QPushButton::clicked, [this]() {
        QString filePath = QFileDialog::getOpenFileName(this, "Wybierz plik PNG", "", "Pliki PNG (*.png)");
        if (!filePath.isEmpty()) {
            fileLineEdit->setText(filePath);
        }
    });

    wholeBodyCheckBox = new QCheckBox("Na całe ciało");
    wholeBodyCheckBox->setVisible(false);
    connect(wholeBodyCheckBox, &QCheckBox::stateChanged, this, &AddClothing::onWholeBodyCheckBoxStateChanged);


    addButton = new QPushButton("Dodaj");
    connect(addButton, &QPushButton::clicked, this, &AddClothing::addButtonClicked);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(new QLabel("Kategoria:"));
    layout->addWidget(categoryComboBox);
    layout->addWidget(wholeBodyCheckBox);
    layout->addWidget(new QLabel("Styl:"));
    layout->addWidget(styleComboBox);
    layout->addWidget(new QLabel("Pogoda:"));
    layout->addWidget(weatherComboBox);
    layout->addWidget(new QLabel("Wybierz plik PNG:"));
    QHBoxLayout *fileLayout = new QHBoxLayout;
    fileLayout->addWidget(fileLineEdit);
    fileLayout->addWidget(browseButton);
    layout->addLayout(fileLayout);
    layout->addWidget(infoLabel);
    layout->addWidget(addButton);

    setLayout(layout);
}

AddClothing::~AddClothing() {}

void AddClothing::addButtonClicked()
{
    QString category = categoryComboBox->currentText();
    QString style = styleComboBox ->currentText();
    QString weather = weatherComboBox->currentText();
    QString filePath = fileLineEdit->text();
    bool isWholeBody = wholeBodyCheckBox->isChecked();

    if (filePath.isEmpty()) {
        QMessageBox::critical(this, "Błąd", "Proszę wybrać plik PNG.");
        return;
    }

    QString resourcesDirPath = "C:/Users/gabul/Documents/Programowanie/Cpp/SkyStyle/resources/clothes_images";
    QDir resourcesDir(resourcesDirPath);
    if (!resourcesDir.exists()) {
        QDir().mkpath(resourcesDirPath);
    }

    QString newFileName = QString("%1-%2-%3.png").arg(weatherMap.value(weather), style, category);
    QString newFilePath = resourcesDirPath + "/" + newFileName;

    if (!QFile::copy(filePath, newFilePath)) {
        QMessageBox::critical(this, "Błąd", "Nie udało się skopiować pliku.");
        return;
    }

    QString dbPath = "C:/Users/gabul/Documents/Programowanie/Cpp/SkyStyle/resources/Clothes";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);
    if (!db.open()) {
        qDebug() << "Error: Could not open database.";
    } else {
        qDebug() << "Database opened successfully.";
    }
    QSqlQuery query;

    if (category == "Góra") {
        QString queryStr = QString("INSERT INTO %1 (weather_conditions, style, image_path, whole_body) "
                                   "VALUES (:weather, :style, :image_path, :whole_body)").arg(clothesMap.value(category));
        query.prepare(queryStr);
        query.bindValue(":style", style);
        query.bindValue(":weather", weather);
        query.bindValue(":image_path", "clothes_images/" + newFileName);
        query.bindValue(":whole_body", isWholeBody);
    } else {
        QString queryStr = QString("INSERT INTO %1 (weather_conditions, style, image_path) "
                                   "VALUES (:weather, :style, :image_path)").arg(clothesMap.value(category));
        query.prepare(queryStr);
        query.bindValue(":style", style);
        query.bindValue(":weather", weather);
        query.bindValue(":image_path", "clothes_images/" + newFileName);
    }

    if (!query.exec()) {
        QMessageBox::critical(this, "Błąd", "Nie udało się dodać elementu do bazy danych: " + query.lastError().text());
        return;
    }

    accept();
}

void AddClothing::onCategoryChanged(const QString &category)
{
    if (category == "Góra") {
        wholeBodyCheckBox->setVisible(true);
        infoLabel->setText("Zalecamy proporcje 1:1 oraz zdjęcie bez tła.");
    } else {
        wholeBodyCheckBox->setVisible(false);
    }

    if (category == "Dół") {
        infoLabel->setText("Zalecamy proporcje 1:2 oraz zdjęcie bez tła.");
    } else {
        infoLabel->setText("Zalecamy proporcje 1:1 oraz zdjęcie bez tła.");
    }

}

void AddClothing::onWholeBodyCheckBoxStateChanged(int state)
{
    if (state == Qt::Checked) {
        infoLabel->setText("Zalecamy proporcje 1:2 oraz zdjęcie bez tła.");
    } else {
        infoLabel->setText("Zalecamy proporcje 1:1 oraz zdjęcie bez tła.");
    }
}
