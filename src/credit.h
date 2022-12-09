#ifndef CREDIT_H
#define CREDIT_H

#include <QModelIndex>
#include <QStandardItemModel>
#include <QStringList>
#include <QStringListModel>

#include "s21_smartcalc.h"
#include "ui_credit.h"

namespace Ui {
class Credit;
}

class Credit : public QDialog {
  Q_OBJECT

 public:
  explicit Credit(QWidget *parent = nullptr);
  ~Credit();

 private:
  Ui::Credit *ui;
  QStandardItemModel *model;  // Создать значение модели
  struct popolnenie *pp;

 public slots:
  void recieveData(struct credits *cr);
  void recieveDebet(struct deposit *dp);
  void recieveList(struct deposit *dp);
 private slots:
  void on_close_credit_clicked();
  void on_del_deposit_clicked();
};

#endif  // CREDIT_H
