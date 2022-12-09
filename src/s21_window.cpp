#include "s21_window.h"

#include "graph.h"
#include "ui_s21_window.h"

bool sign = false;
int butt_end = END;  // 1 - цифры, 2-знаки, 3-точка, 4-(, 5-), 6-х, 7-sin

s21_Window::s21_Window(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::s21_Window) {
  ui->setupUi(this);

  connect(ui->Button_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->Button_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));

  connect(ui->Button_plus, SIGNAL(clicked()), this, SLOT(digits_sign()));
  connect(ui->Button_minus, SIGNAL(clicked()), this, SLOT(digits_sign()));
  connect(ui->Button_separation, SIGNAL(clicked()), this, SLOT(digits_sign()));
  connect(ui->Button_x, SIGNAL(clicked()), this, SLOT(digits_sign()));

  connect(ui->Button_e, SIGNAL(clicked()), this, SLOT(pi_e_clicked()));
  connect(ui->Button_pi, SIGNAL(clicked()), this, SLOT(pi_e_clicked()));

  connect(ui->Button_cos, SIGNAL(clicked()), this, SLOT(function_trig()));
  connect(ui->Button_sin, SIGNAL(clicked()), this, SLOT(function_trig()));
  connect(ui->Button_acos, SIGNAL(clicked()), this, SLOT(function_trig()));
  connect(ui->Button_asin, SIGNAL(clicked()), this, SLOT(function_trig()));
  connect(ui->Button_atan, SIGNAL(clicked()), this, SLOT(function_trig()));
  connect(ui->Button_tan, SIGNAL(clicked()), this, SLOT(function_trig()));
  connect(ui->Button_log, SIGNAL(clicked()), this, SLOT(function_trig()));
  connect(ui->Button_sqrt, SIGNAL(clicked()), this, SLOT(function_trig()));
  connect(ui->Button_ln, SIGNAL(clicked()), this, SLOT(function_trig()));

  ui->Date->setDate(QDate::currentDate());
  ui->Date_2->setDate(QDate::currentDate());
  ui->Date_3->setDate(QDate::currentDate());

  credit_form = new Credit();
  graph_form = new graph();

  cr.periud = 2;
  cr.add = &pp;
  cr.add->day[0] = 0;
}

s21_Window::~s21_Window() { delete ui; }

void s21_Window::closeEvent(QCloseEvent *event) {
  if (event) {
    if (credit_form->isVisible()) credit_form->close();
    if (graph_form->isVisible()) graph_form->close();
  }
}

void s21_Window::on_doubleSpinBox_iks_valueChanged(double arg1) { iks = arg1; }

void s21_Window::on_Button_c_clicked() {
  Validate(END);
  ui->result_show->setPlainText("0");
}

void s21_Window::digits_numbers() {
  if (Validate(NUM)) {
    QPushButton *button = (QPushButton *)sender();
    ui->result_show->setPlainText(first_num(button->text()));
  }
}

void s21_Window::pi_e_clicked() {
  QString new_label;
  QPushButton *button = (QPushButton *)sender();
  if (button->text() == "Pi")
    new_label = "3.1415926";
  else if (button->text() == "e")
    new_label = "2.7182818";

  if (butt_end == SGN || butt_end == BOP || butt_end == OPR)
    ui->result_show->setPlainText(ui->result_show->toPlainText() + new_label);
  else
    ui->result_show->setPlainText(new_label);
  sign = false;
  butt_end = NUM;
}

void s21_Window::digits_sign() {
  if (Validate(SGN)) {
    QPushButton *button = (QPushButton *)sender();
    if (ui->result_show->toPlainText() == "0" ||
        ui->result_show->toPlainText() == "(") {
      if (button->text() == "+" || button->text() == "-")
        ui->result_show->setPlainText(button->text());
    } else {
      ui->result_show->setPlainText(ui->result_show->toPlainText() +
                                    button->text());
    }
  }
}

void s21_Window::on_Button_xy_clicked() {
  if (Validate(SGN))
    ui->result_show->setPlainText(ui->result_show->toPlainText() + "^");
}

void s21_Window::on_Button_mod_clicked() {
  if (Validate(SGN))
    ui->result_show->setPlainText(ui->result_show->toPlainText() + " mod ");
}

void s21_Window::on_Button_point_clicked() {
  if (Validate(POI))
    ui->result_show->setPlainText(ui->result_show->toPlainText() + ".");
}

void s21_Window::on_Button_bracketopening_clicked() {
  if (Validate(BOP)) ui->result_show->setPlainText(first_num("("));
}

void s21_Window::on_Button_bracketclosing_clicked() {
  if (Validate(BCL)) ui->result_show->setPlainText(first_num(")"));
}

void s21_Window::on_Button_iks_clicked() {
  if (Validate(BTX)) ui->result_show->setPlainText(first_num("x"));
}

void s21_Window::function_trig() {
  if (Validate(OPR)) {
    QString new_label;
    QPushButton *button = (QPushButton *)sender();
    if (button->text() == "cos")
      new_label = "cos(";
    else if (button->text() == "sin")
      new_label = "sin(";
    else if (button->text() == "sin")
      new_label = "sin(";
    else if (button->text() == "tan")
      new_label = "tan(";
    else if (button->text() == "acos")
      new_label = "acos(";
    else if (button->text() == "asin")
      new_label = "asin(";
    else if (button->text() == "atan")
      new_label = "atan(";
    else if (button->text() == "log")
      new_label = "log(";
    else if (button->text() == "ln")
      new_label = "ln(";
    else if (button->text() == "sqrt")
      new_label = "sqrt(";

    ui->result_show->setPlainText(first_num(new_label));
  }
}

void s21_Window::on_Button_equally_clicked() {
  char str_in1[STKDPTH];
  strcpy(str_in1, ui->result_show->toPlainText().toLocal8Bit().data());
  if (sign)
    on_Button_del_clicked(),
        strcpy(str_in1, ui->result_show->toPlainText().toLocal8Bit().data());
  double rez = 0.0;
  algoritm_d(str_in1);
  int is_error = 0;
  QString history = ui->result_show->toPlainText();
  bool checkBox = ui->checkBox->isChecked();
  QString str_out = "0";
  if (checkBox) {
    is_error = operand(str_in1, &rez, 1);
    if (!is_error) {
      Window_Pos();
      double diapazon[4] = {
          ui->doubleSpinBox_obl_x1->value(), ui->doubleSpinBox_obl_x2->value(),
          ui->doubleSpinBox_obl_y1->value(), ui->doubleSpinBox_obl_y2->value()};
      connect(this, SIGNAL(sendPrint(const char *, double *)), graph_form,
              SLOT(Print(const char *, double *)), Qt::DirectConnection);
      graph_form->show();
      emit sendPrint(str_in1, diapazon);
    }
    butt_end = END;
    history = "График " + history;
  } else {
    is_error = operand(str_in1, &rez, iks);
    str_out = QString::number(rez, 'f', 7);
    rez = QVariant{str_out}.toDouble();
    str_out = QVariant{rez}.toString();
    butt_end = EQL;
    sign = false;
  }

  switch (is_error) {
    case -1:
      str_out = "Переполнение стека";
      break;
    case -2:
      str_out = "В стеке недостаточно операндов";
      break;
    case -3:
      str_out = "Неопознанное значение";
      break;
    case -4:
      str_out = "NaN";
      break;
    case -5:
      str_out = "inf";
      break;
  }
  ui->result_show->setPlainText(str_out);
  if (!checkBox) history += " = " + str_out;
  ui->result_history->appendPlainText(history);
}

void s21_Window::on_Button_del_clicked() {
  QString new_label = ui->result_show->toPlainText().mid(
      ui->result_show->toPlainText().length(), 1);
  int len = 1;
  if (new_label == '+' || new_label == '-' || new_label == '*' ||
      new_label == '/' || new_label == '^')
    sign = false;

  for (int i = 3; i < 6; i++) {
    new_label = ui->result_show->toPlainText().mid(
        ui->result_show->toPlainText().length() - i, i);
    if (new_label == "ln(")
      len = 3;
    else if (new_label == "cos(" || new_label == "sin(" ||
             new_label == "tan(" || new_label == "log(")
      len = 4;
    else if (new_label == "acos(" || new_label == "asin(" ||
             new_label == "atan(" || new_label == " mod " ||
             new_label == "sqrt(")
      len = 5;
  }

  new_label = ui->result_show->toPlainText().mid(
      ui->result_show->toPlainText().length() - 1, 1);
  if (new_label >= '0' && new_label <= '9')
    butt_end = NUM;
  else if (new_label == '+' || new_label == '-' || new_label == '*' ||
           new_label == '/' || new_label == '^' || new_label == ' ')
    butt_end = SGN, sign = true;
  else if (new_label == '.')
    butt_end = POI;
  else if (new_label == '(') {
    new_label = ui->result_show->toPlainText().mid(
        ui->result_show->toPlainText().length() - 2, 1);
    if (new_label >= 'a' && new_label <= 'z')
      butt_end = OPR;
    else
      butt_end = BOP;
  } else if (new_label == ')')
    butt_end = BCL;
  else if (new_label == 'x')
    butt_end = BTX;

  new_label = ui->result_show->toPlainText().remove(
      ui->result_show->toPlainText().length() - len, len);
  if (new_label == "") new_label = "0", butt_end = END;
  ui->result_show->setPlainText(new_label);
}

void s21_Window::on_comboBox_activated(int index) { cr.periud = index; }

void s21_Window::on_pushButton_list_clicked() {
  connect(this, SIGNAL(sendDebet(deposit *)), credit_form,
          SLOT(recieveList(deposit *)));
  Window_Pos();
  credit_form->show();
  emit sendDebet(&cr);
}

void s21_Window::on_pushButton_add_clicked() {
  int i = 0;
  for (; cr.add->day[i] > 0; i++)
    ;

  cr.add->day[i] = ui->Date_3->date().day();
  cr.add->day[i + 1] = 0;
  cr.add->month[i] = ui->Date_3->date().month();
  cr.add->year[i] = ui->Date_3->date().year();
  cr.add->sum[i] = ui->Sum_3->value();
  if (ui->comboBox_add->currentIndex() == 1) cr.add->sum[i] *= -1;
}

void s21_Window::on_Button_deposit_clicked() {
  cr.sum = ui->Sum_2->value();
  cr.time = ui->Time_2->value();
  cr.day[0] = ui->Date_2->date().day();
  cr.month[0] = ui->Date_2->date().month();
  cr.year[0] = ui->Date_2->date().year();
  cr.percent = ui->percent_2->value();
  cr.kapital = (ui->checkBox_kapital->isChecked()) ? 1 : 0;
  cr.nalog = ui->nalog->value();
  cr.all_nalog = 0;

  cr.all_cash = 0;
  cr.all_procent = 0;
  deposit_calc(&cr);

  connect(this, SIGNAL(sendDebet(deposit *)), credit_form,
          SLOT(recieveDebet(deposit *)));
  Window_Pos();
  credit_form->show();
  emit sendDebet(&cr);
}

void s21_Window::on_Button_credit_clicked() {
  struct credits cr;
  cr.sum = ui->Sum->value();
  cr.time = ui->Time->value();
  cr.percent = ui->percent->value();
  if (ui->radioButton_2->isChecked())
    cr.type = 1;
  else
    cr.type = 0;
  cr.all_pay = 0;
  cr.overpayment = 0;
  cr.day[0] = ui->Date->date().day();
  cr.month[0] = ui->Date->date().month();
  cr.year[0] = ui->Date->date().year();
  cr.pay[0] = 0;
  cr.debt = 0;
  cr.procent[0] = 0;
  cr.balance[0] = 0;
  credit_calc(&cr);

  char str[250];
  transfer(&(cr.overpayment), str);
  ui->overpayment->setText(str);

  transfer(&(cr.all_pay), str);
  ui->all_pay->setText(str);

  if (cr.type == 0) {
    transfer(&(cr.pay[1]), str);
    ui->pay_l->setText(str);
    connect(this, SIGNAL(sendData(credits *)), credit_form,
            SLOT(recieveData(credits *)));

    Window_Pos();
    credit_form->show();
    emit sendData(&cr);
  } else {
    transfer(&(cr.pay[0]), str);
    ui->pay_l->setText(str);
  }
}

void s21_Window::on_result_show_textChanged() {
  if (ui->result_show->toPlainText().length() > 255) on_Button_del_clicked();
  if (!ui->result_show->toPlainText().contains('x')) {
    iks = 1.0;
    ui->label_iks->setEnabled(false);
    ui->doubleSpinBox_iks->setEnabled(false);
    if (ui->checkBox->isChecked()) {
      on_checkBox_clicked(0);
      ui->checkBox->setChecked(0);
    }
  } else {
    if (!ui->checkBox->isChecked()) {
      iks = ui->doubleSpinBox_iks->value();
      ui->label_iks->setEnabled(true);
      ui->doubleSpinBox_iks->setEnabled(true);
    }
  }
}

void s21_Window::on_checkBox_clicked(bool checked) {
  if (checked) {
    ui->label_iks->setEnabled(false);
    ui->doubleSpinBox_iks->setEnabled(false);
    ui->label_x->setEnabled(true);
    ui->doubleSpinBox_obl_x1->setEnabled(true);
    ui->doubleSpinBox_obl_x2->setEnabled(true);
    ui->label_y->setEnabled(true);
    ui->doubleSpinBox_obl_y1->setEnabled(true);
    ui->doubleSpinBox_obl_y2->setEnabled(true);
  } else {
    if (!ui->result_show->toPlainText().contains('x')) {
      ui->label_iks->setEnabled(false);
      ui->doubleSpinBox_iks->setEnabled(false);
    } else {
      ui->label_iks->setEnabled(true);
      ui->doubleSpinBox_iks->setEnabled(true);
    }
    ui->label_x->setEnabled(false);
    ui->doubleSpinBox_obl_x1->setEnabled(false);
    ui->doubleSpinBox_obl_x2->setEnabled(false);
    ui->label_y->setEnabled(false);
    ui->doubleSpinBox_obl_y1->setEnabled(false);
    ui->doubleSpinBox_obl_y2->setEnabled(false);
  }
}

void s21_Window::Window_Pos() {
  QScreen *screen = QGuiApplication::primaryScreen();
  QRect rect = screen->availableGeometry();
  QPoint center = rect.center();
  center.setX(center.x() - (this->width() + 5));
  center.setY(center.y() - (this->height() / 2));
  move(center);
}

QString s21_Window::first_num(QString butt) {
  return (ui->result_show->toPlainText() == "0")
             ? butt
             : ui->result_show->toPlainText() + butt;
}

void s21_Window::keyPressEvent(QKeyEvent *event) {
  int key = event->key();
  QString str = event->text();
  if (key >= Qt::Key_0 && key <= Qt::Key_9) {
    this->findChild<QPushButton *>("Button_" + str)->click();
  } else if (key == Qt::Key_Backspace) {
    ui->Button_del->click();
  } else if (key == Qt::Key_Delete) {
    ui->Button_c->click();
  } else if (key == Qt::Key_Plus) {
    ui->Button_plus->click();
  } else if (key == Qt::Key_Minus) {
    ui->Button_minus->click();
  } else if (key == Qt::Key_Asterisk) {
    ui->Button_x->click();
  } else if (key == Qt::Key_ParenLeft) {
    ui->Button_bracketopening->click();
  } else if (key == Qt::Key_ParenRight) {
    ui->Button_bracketclosing->click();
  } else if (key == Qt::Key_Slash) {
    ui->Button_separation->click();
  } else if (key == Qt::Key_Period || key == Qt::Key_Comma) {
    ui->Button_point->click();
  } else if (key == Qt::Key_V && event->modifiers() & Qt::ControlModifier) {
    ui->result_show->setPlainText(QGuiApplication::clipboard()->text());
    ui->Button_equally->click();
  } else if (key == Qt::Key_Enter || key == Qt::Key_Return) {
    ui->Button_equally->click();
  } else if (key == Qt::Key_Escape) {
  }
}

// 1 - цифры, 2-знаки, 3-точка, 4-(, 5-), 6-х, 7-sin
bool s21_Window::Validate(int clicked_button) {
  bool rez = false;
  if (butt_end == END) ui->result_show->setPlainText("0");
  switch (clicked_button) {
    case END:
      rez = true;
      sign = false;
      break;
    case NUM:
      if (butt_end != BTX && butt_end != BCL && butt_end != EQL) {
        rez = true;
        sign = false;
      }
      break;
    case SGN:
      if (butt_end != POI) {
        rez = true;
        sign = true;
      }
      break;
    case POI:
      if (butt_end == END || butt_end == NUM) rez = true;
      break;
    case BOP:
      if (butt_end == END || butt_end == SGN || butt_end == BOP) {
        rez = true;
        sign = false;
      }
      break;
    case BCL:
      if (butt_end == NUM || butt_end == BTX || butt_end == BCL) rez = true;
      break;
    case BTX:
      if (butt_end == END || butt_end == SGN || butt_end == BOP ||
          butt_end == OPR) {
        rez = true;
        sign = false;
      }
      break;
    case OPR:
      if (butt_end == END || butt_end == SGN || butt_end == BOP ||
          butt_end == OPR) {
        rez = true;
        sign = false;
      }
      break;
  }

  if (rez) butt_end = clicked_button;
  return rez;
}

void s21_Window::on_doubleSpinBox_obl_x1_valueChanged(double arg1) {
  if (arg1 >= ui->doubleSpinBox_obl_x2->value())
    ui->doubleSpinBox_obl_x1->setValue(ui->doubleSpinBox_obl_x2->value() - 1);
}

void s21_Window::on_doubleSpinBox_obl_x2_valueChanged(double arg1) {
  if (arg1 <= ui->doubleSpinBox_obl_x1->value())
    ui->doubleSpinBox_obl_x2->setValue(ui->doubleSpinBox_obl_x1->value() + 1);
}

void s21_Window::on_doubleSpinBox_obl_y1_valueChanged(double arg1) {
  if (arg1 >= ui->doubleSpinBox_obl_y2->value())
    ui->doubleSpinBox_obl_y1->setValue(ui->doubleSpinBox_obl_y2->value() - 1);
}

void s21_Window::on_doubleSpinBox_obl_y2_valueChanged(double arg1) {
  if (arg1 <= ui->doubleSpinBox_obl_y1->value())
    ui->doubleSpinBox_obl_y2->setValue(ui->doubleSpinBox_obl_y1->value() + 1);
}
