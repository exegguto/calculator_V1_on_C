#include "credit.h"

#include <QScreen>

#include "ui_credit.h"

Credit::Credit(QWidget *parent) : QDialog(parent), ui(new Ui::Credit) {
  ui->setupUi(this);

  QScreen *screen = QGuiApplication::primaryScreen();
  QRect rect = screen->availableGeometry();
  QPoint center = rect.center();
  center.setX(center.x());
  center.setY(center.y() - (this->height() / 2));
  move(center);
}

Credit::~Credit() { delete ui; }

void Credit::recieveData(struct credits *cr) {
  ui->tableView->setShowGrid(true);
  ui->tableView->setGridStyle(Qt::SolidLine);
  model = new QStandardItemModel(this);
  QStringList labels = {"Дата", "Сумма платежа", "Основной долг", "Проценты",
                        "Остаток долга"};
  model->setHorizontalHeaderLabels(labels);
  QStandardItem *item = 0;
  char str[250];

  for (int i = 1; cr->day[i] != 0.0 && cr->type == 0; i++) {
    item = new QStandardItem(QString::number(cr->day[i]) + "." +
                             QString::number(cr->month[i]) + "." +
                             QString::number(cr->year[i]));
    item->setEditable(QAbstractItemView::NoEditTriggers);
    model->setItem(i - 1, 0, item);
    transfer(&(cr->pay[i]), str);
    item = new QStandardItem(str);
    item->setEditable(QAbstractItemView::NoEditTriggers);
    model->setItem(i - 1, 1, item);
    transfer(&(cr->debt), str);
    item = new QStandardItem(str);
    item->setEditable(QAbstractItemView::NoEditTriggers);
    model->setItem(i - 1, 2, item);
    transfer(&(cr->procent[i]), str);
    item = new QStandardItem(str);
    item->setEditable(QAbstractItemView::NoEditTriggers);
    model->setItem(i - 1, 3, item);
    transfer(&(cr->balance[i]), str);
    item = new QStandardItem(str);
    item->setEditable(QAbstractItemView::NoEditTriggers);
    model->setItem(i - 1, 4, item);
  }

  ui->overpayment->setVisible(false);
  ui->all_pay->setVisible(false);
  ui->pay_l->setVisible(false);
  ui->pay_l2->setVisible(false);
  ui->label->setVisible(false);
  ui->label_3->setVisible(false);
  ui->del_deposit->setVisible(false);

  ui->tableView->setStyleSheet(
      "QTableView { border: none;"
      "selection-background-color: #8EDE21;"
      "color: black}");
  ui->tableView->setModel(model);
  ui->tableView->resizeColumnsToContents();
  ui->tableView->show();
}

void Credit::recieveDebet(struct deposit *cr) {
  ui->tableView->setShowGrid(true);
  ui->tableView->setGridStyle(Qt::SolidLine);
  model = new QStandardItemModel(this);
  QStringList labels = {"Дата", "Проценты", "Остаток"};
  model->setHorizontalHeaderLabels(labels);

  QStandardItem *item = 0;
  char str[250];
  for (int i = 1; cr->day[i] != 0.0; i++) {
    item = new QStandardItem(QString::number(cr->day[i]) + "." +
                             QString::number(cr->month[i]) + "." +
                             QString::number(cr->year[i]));
    item->setEditable(QAbstractItemView::NoEditTriggers);
    model->setItem(i - 1, 0, item);

    transfer(&(cr->procent[i]), str);
    item = new QStandardItem(str);
    item->setEditable(QAbstractItemView::NoEditTriggers);
    model->setItem(i - 1, 1, item);

    transfer(&(cr->balance[i]), str);
    item = new QStandardItem(str);
    item->setEditable(QAbstractItemView::NoEditTriggers);
    model->setItem(i - 1, 2, item);
    transfer(&(cr->balance[i]), str);
  }
  ui->pay_l->setText(str);
  ui->pay_l->setVisible(true);
  ui->del_deposit->setVisible(false);

  transfer(&(cr->all_procent), str);
  ui->overpayment->setText(str);
  ui->overpayment->setVisible(true);
  ui->label_3->setText("Ежемесячный платеж");
  ui->label_3->setVisible(true);

  ui->label_3->setText("Сумма налога");
  transfer(&(cr->all_nalog), str);
  ui->all_pay->setText(str);
  ui->all_pay->setVisible(true);

  ui->pay_l2->setText("Cумма на вкладе");
  ui->pay_l2->setVisible(true);
  ui->label->setVisible(true);
  ui->del_deposit->setVisible(false);
  ui->tableView->setStyleSheet(
      "QTableView { border: none;"
      "selection-background-color: #8EDE21;"
      "color: black}");
  ui->tableView->setModel(model);

  ui->tableView->resizeColumnsToContents();
  ui->tableView->show();
}

void Credit::recieveList(struct deposit *cr) {
  ui->tableView->setShowGrid(true);
  ui->tableView->setGridStyle(Qt::SolidLine);
  model = new QStandardItemModel(this);
  QStringList labels;

  QStandardItem *item = 0;
  char str[250];
  if (cr->add->day[0] != 0.0) {
    labels << "Дата"
           << "Пополнение/Снятие";
    for (int i = 0; cr->add->day[i] > 0.0; i++) {
      item = new QStandardItem(QString::number(cr->add->day[i]) + "." +
                               QString::number(cr->add->month[i]) + "." +
                               QString::number(cr->add->year[i]));
      item->setEditable(QAbstractItemView::NoEditTriggers);
      model->setItem(i, 0, item);

      transfer(&(cr->add->sum[i]), str);
      item = new QStandardItem(str);
      item->setEditable(QAbstractItemView::NoEditTriggers);
      model->setItem(i, 1, item);
    }
    ui->del_deposit->setVisible(true);
  } else {
    labels << "Здесь пока нет записей";
  }
  ui->pay_l->setVisible(false);
  ui->pay_l2->setVisible(false);
  ui->all_pay->setVisible(false);
  ui->label->setVisible(false);
  ui->label_3->setVisible(false);
  ui->overpayment->setVisible(false);
  pp = cr->add;

  model->setHorizontalHeaderLabels(labels);
  ui->tableView->setStyleSheet(
      "QTableView { border: none;"
      "selection-background-color: #8EDE21;"
      "color: black}");
  ui->tableView->setModel(model);
  ui->tableView->resizeColumnsToContents();
  ui->tableView->show();
}

void Credit::on_close_credit_clicked() {
  model->removeRows(0, model->rowCount());
  this->close();
}

void Credit::on_del_deposit_clicked() {
  pp->day[0] = 0;
  model->removeRows(0, model->rowCount());
  this->close();
}
