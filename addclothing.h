#ifndef ADDCLOTHING_H
#define ADDCLOTHING_H

#include "qlabel.h"
#include "qsqldatabase.h"
#include <QDialog>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>

class AddClothing : public QDialog
{
    Q_OBJECT

public:
    explicit AddClothing(QWidget *parent = nullptr);
    ~AddClothing();

private slots:
    void addButtonClicked();
    void onCategoryChanged(const QString &category);
    void onWholeBodyCheckBoxStateChanged(int state);

private:
    QComboBox *categoryComboBox;
    QComboBox *styleComboBox;
    QComboBox *weatherComboBox;
    QLineEdit *fileLineEdit;
    QPushButton *addButton;
    QCheckBox *wholeBodyCheckBox;
    QLabel *infoLabel;
    QSqlDatabase db;
    QMap<QString, QString> clothesMap;
    QMap<QString, QString> weatherMap;
};

#endif // ADDCLOTHING_H
