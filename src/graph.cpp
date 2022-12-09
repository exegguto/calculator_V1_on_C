
#include "graph.h"

#include "s21_smartcalc.h"
#include "ui_graph.h"

graph::graph(QWidget *parent) : QDialog(parent), ui(new Ui::graph) {
  ui->setupUi(this);

  QScreen *screen = QGuiApplication::primaryScreen();
  QRect rect = screen->availableGeometry();
  QPoint center = rect.center();
  center.setX(center.x());
  center.setY(center.y() - (this->height() / 2));
  move(center);

  chart = new QChart();
  chartView = new QChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);
  axisX = new QValueAxis();
  axisX->setTitleText("X");
  axisX->setLabelFormat("%.1f");
  axisX->setTickCount(9);
  chart->addAxis(axisX, Qt::AlignBottom);

  axisY = new QValueAxis();
  axisY->setTitleText("Y");
  axisY->setLabelFormat("%.1f");
  axisY->setTickCount(9);
  chart->addAxis(axisY, Qt::AlignLeft);

  ui->verticalLayout->addWidget(chartView);
}

graph::~graph() { delete ui; }

void graph::Print(const char *str_in1, double *diapazon) {
  chartView->chart()->removeAllSeries();

  axisX->setRange(diapazon[0], diapazon[1]);
  axisY->setRange(diapazon[2], diapazon[3]);

  series1 = new QLineSeries();
  series1->append(0, -1000000);
  series1->append(0, 1000000);
  series1->setColor("Green");
  chart->addSeries(series1);

  series1->attachAxis(axisX);
  series1->attachAxis(axisY);

  series1 = new QLineSeries();
  series1->append(-1000000, 0);
  series1->append(1000000, 0);
  series1->setColor("Green");
  chart->addSeries(series1);
  series1->attachAxis(axisX);
  series1->attachAxis(axisY);

  series1 = new QLineSeries();
  double step = 0.01;
  double y, x = diapazon[0];

  double x_temp = x;
  int j = round(x / M_PI);

  for (int i = 0; x <= diapazon[1]; i++) {
    if (!operand(str_in1, &y, x) && !isnan(y) && !isinf(y)) {
      char str1[2] = "t";
      if ((strstr(str_in1, str1) != NULL) && x_temp < (M_PI / 2 + M_PI * j) &&
          x > (M_PI / 2 + M_PI * j)) {
        series1->setColor("Red");
        chart->addSeries(series1);
        series1->attachAxis(axisX);
        series1->attachAxis(axisY);

        series1 = new QLineSeries();
        series1->append(x, y);
        j++;
      } else {
        series1->append(x, y);
      }
      x_temp = x;
    }
    x += step;
  }
  series1->setColor("Red");
  chart->addSeries(series1);

  series1->attachAxis(axisX);
  series1->attachAxis(axisY);

  chart->legend()->hide();
  chartView->setChart(chart);
}

void graph::on_pushButton_clicked() {
  chartView->chart()->removeAllSeries();
  this->close();
}
