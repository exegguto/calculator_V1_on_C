#include <QApplication>

#include "s21_window.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21_Window w;
  w.show();
  return a.exec();
}
