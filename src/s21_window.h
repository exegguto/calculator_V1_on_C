#ifndef S21_WINDOW_H
#define S21_WINDOW_H

#include <QClipboard>
#include <QKeyEvent>
#include <QMainWindow>
#include <QScreen>

#include "credit.h"
#include "graph.h"
#include "s21_smartcalc.h"

#define END 0
#define NUM 1
#define SGN 2
#define POI 3
#define BOP 4
#define BCL 5
#define BTX 6
#define OPR 7
#define EQL 8

QT_BEGIN_NAMESPACE
namespace Ui {
class s21_Window;
}
QT_END_NAMESPACE

class s21_Window : public QMainWindow {
  Q_OBJECT

 public:
  s21_Window(QWidget *parent = nullptr);
  ~s21_Window();

 private:
  Ui::s21_Window *ui;
  Credit *credit_form;
  graph *graph_form;
  struct deposit cr;
  struct popolnenie pp;
  double iks;

 private slots:
  void closeEvent(QCloseEvent *event);
  void digits_numbers();
  void digits_sign();
  void pi_e_clicked();
  void on_Button_c_clicked();
  void on_Button_del_clicked();
  void on_Button_point_clicked();
  void on_Button_iks_clicked();

  void on_comboBox_activated(int index);
  void on_pushButton_list_clicked();
  void on_pushButton_add_clicked();
  void on_Button_deposit_clicked();
  void on_Button_credit_clicked();
  void on_Button_bracketopening_clicked();
  void on_Button_bracketclosing_clicked();

  void on_doubleSpinBox_iks_valueChanged(double arg1);
  void on_result_show_textChanged();
  void on_checkBox_clicked(bool checked);
  void Window_Pos();

  QString first_num(QString butt);
  bool Validate(int clicked_button);

  void on_Button_xy_clicked();

  void on_Button_mod_clicked();

  void function_trig();

  void on_Button_equally_clicked();

  void on_doubleSpinBox_obl_x1_valueChanged(double arg1);

  void on_doubleSpinBox_obl_x2_valueChanged(double arg1);

  void on_doubleSpinBox_obl_y1_valueChanged(double arg1);

  void on_doubleSpinBox_obl_y2_valueChanged(double arg1);

 protected:
  virtual void keyPressEvent(QKeyEvent *event);

 signals:
  void sendData(struct credits *cr);
  void sendDebet(struct deposit *dp);
  void sendPrint(const char *str_in1, double *diapazon);
};
#endif  // S21_WINDOW_H
