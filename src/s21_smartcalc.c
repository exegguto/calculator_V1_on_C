// Copyright 2022 exegguto

#include "s21_smartcalc.h"

double stack[STKDPTH];

void algoritm_d(char *outstr) {
  struct st *OPERS = NULL;  // стек
  int k = 0;      // номер символа во входной строке
  int point = 0;  // номер символа в выходной строке
  int skobka = 0;
  char str_mass[STKDPTH];  // массив для символов преобразованной строки
  strncpy(str_mass, "", STKDPTH - 1);
  while (outstr[k] != '\0' && outstr[k] != '=') {
    if (outstr[k] == '(') skobka++;
    if (outstr[k] == ')' && skobka > 0) {
      while (OPERS->c != '(')
        str_mass[point++] = DEL(&OPERS), str_mass[point++] = ' ';
      DEL(&OPERS);
      skobka--;
    }
    if (outstr[k] == 'x') str_mass[point++] = 'x', str_mass[point++] = ' ';
    if (outstr[k] >= '0' && outstr[k] <= '9') {
      while (strchr("0123456789.,", outstr[k]) != NULL && outstr[k] != '\0')
        str_mass[point++] = (outstr[k++] != ',') ? outstr[k - 1] : '.';
      k--;
      str_mass[point++] = ' ';
    }
    if (strchr("(+-/*asctlm^", outstr[k]) != NULL) {
      int flag = 1;
      char str = outstr[k];
      if (!strncmp(&outstr[k], "sin", 3) || !strncmp(&outstr[k], "cos", 3) ||
          !strncmp(&outstr[k], "tan", 3) || !strncmp(&outstr[k], "log", 3) ||
          !strncmp(&outstr[k], "mod", 3))
        k += 2, flag = 0;
      if (flag) {
        if (!strncmp(&outstr[k], "asin", 4)) str = 'S', k += 3;
        if (!strncmp(&outstr[k], "acos", 4)) str = 'C', k += 3;
        if (!strncmp(&outstr[k], "atan", 4)) str = 'T', k += 3;
        if (!strncmp(&outstr[k], "sqrt", 4)) str = 'q', k += 3;
        if (!strncmp(&outstr[k], "ln", 2)) str = 'L', k += 1;
      }

      while (OPERS != NULL && outstr[k] != '(' && PRIOR(OPERS->c) >= PRIOR(str))
        str_mass[point++] = DEL(&OPERS), str_mass[point++] = ' ';
      if ((outstr[k] == '(' && outstr[k + 1] == '-') ||
          (k == 0 && outstr[k] == '-')) {
        if (outstr[k] == '(') OPERS = push(OPERS, '('), k++;
        OPERS = push(OPERS, 'M');
      } else {
        OPERS = push(OPERS, str);
      }
    }
    k++;
  }
  while (OPERS != NULL)
    str_mass[point++] = DEL(&OPERS), str_mass[point++] = ' ';
  str_mass[point] = '\0';
  strncpy(outstr, str_mass, STKDPTH);
}

char DEL(struct st **HEAD) {
  struct st *PTR;
  char a;
  if (*HEAD == NULL) return '\0';
  PTR = *HEAD;
  a = PTR->c;
  *HEAD = PTR->next;
  free(PTR);
  return a;
}

struct st *push(struct st *HEAD, char a) {
  struct st *PTR;
  if ((PTR = malloc(sizeof(struct st))) == NULL) exit(-1);
  PTR->c = a;
  PTR->next = HEAD;
  return PTR;
}

int PRIOR(char a) {
  int i = 0;
  switch (a) {
    case 's':
    case 'S':
    case 'c':
    case 'C':
    case 't':
    case 'T':
    case 'q':
    case 'L':
    case 'l':
      i = 7;
      break;
    case '^':
      i = 6;
      break;
    case 'M':
      i = 5;
      break;
    case '*':
    case '/':
      i = 4;
      break;
    case 'm':
      i = 3;
      break;
    case '-':
    case '+':
      i = 2;
      break;
    case '(':
      i = 1;
      break;
  }
  return i;
}

int operand(const char *str, double *rez, double x) {
  char *endptr;    // ошибка перевода в число
  int error = 0;   // ошибки
  int scount = 0;  // счетчик элементов в стеке
  char s[STKDPTH];
  strcpy(s, str);
  char *str_temp = strtok(s, " ");  // элемент из нотации

  while (str_temp && !error) {
    if ((strchr("+*/m^", *str_temp) != NULL && scount < 2) ||
        (strchr("-asScCtTqLl", *str_temp) != NULL && scount < 1)) {
      error = SUF;
    } else {
      --scount;
      switch (*str_temp) {
        case '-':
          stack[scount - 1] -= stack[scount];
          break;
        case '+':
          stack[scount - 1] += stack[scount];
          break;
        case '*':
          stack[scount - 1] *= stack[scount];
          break;
        case '^':
          stack[scount - 1] = pow(stack[scount - 1], stack[scount]);
          break;
        case '/':
          if (stack[scount] != 0 && stack[scount - 1] != 0)
            stack[scount - 1] /= stack[scount];
          else if (stack[scount] == 0 && stack[scount - 1] == 0)
            error = ENAN;
          else if (stack[scount] == 0)
            error = EINF;
          else
            stack[scount - 1] = 0;
          break;
        case 'm':
          if (stack[scount] != 0 && stack[scount - 1] != 0)
            stack[scount - 1] = fmod(stack[scount - 1], stack[scount]);
          else if (stack[scount] == 0 && stack[scount - 1] == 0)
            error = ENAN;
          else if (stack[scount] == 0)
            error = EINF;
          else
            stack[scount - 1] = 0;
          break;
        case 'M':
          stack[scount] = -stack[scount];
          break;
        case 's':
          stack[scount] = sin(stack[scount]);
          break;
        case 'S':
          stack[scount] = asin(stack[scount]);
          break;
        case 'c':
          stack[scount] = cos(stack[scount]);
          break;
        case 'C':
          stack[scount] = acos(stack[scount]);
          break;
        case 't':
          stack[scount] = tan(stack[scount]);
          break;
        case 'T':
          stack[scount] = atan(stack[scount]);
          break;
        case 'q':
          if (stack[scount] < 0)
            error = ENAN;
          else
            stack[scount] = sqrt(stack[scount]);
          break;
        case 'L':
          if (stack[scount] < 0)
            error = ENAN;
          else
            stack[scount] = log10(stack[scount]);
          break;
        case 'l':
          if (stack[scount] < 0)
            error = ENAN;
          else
            stack[scount] = log(stack[scount]);
          break;
        default: {
          scount++;
          if (str_temp[0] == 'x') {
            stack[scount++] = x;
          } else {
            double tval;  // хранит операнд для загрузки в стек
            if (str_temp[0] == '_') str_temp[0] = '-';
            tval = strtod(str_temp, &endptr);
            if (*endptr != '\0') {
              error = UNK;
            } else {
              if (scount < STKDPTH)
                stack[scount++] = tval;
              else
                error = SOF;
            }
          }
          break;
        }
      }
      if (strchr("MasScCtTqLl", *str_temp) != NULL) scount++;
      str_temp = strtok(NULL, " ");
    }
  }
  *rez = stack[0];
  return error;
}

int yearv(int year) {
  return ((year % 4) == 0 && (((year % 100) != 0) || ((year % 400) == 0)));
}

void credit_calc(struct credits *cr) {
  if (cr->type == 1) {
    double proc = cr->percent / 12 / 100;
    cr->pay[0] = cr->sum * proc * pow(1 + proc, cr->time) /
                 (pow(1 + proc, cr->time) - 1) * 100;
    cr->pay[0] = round(cr->pay[0]) / 100;
    cr->all_pay = cr->pay[0] * cr->time;
    cr->overpayment = cr->all_pay - cr->sum;
    cr->day[1] = 0.0;
  } else {
    int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int day = 0, month = cr->month[0], year = cr->year[0];

    cr->debt = round(cr->sum / cr->time * 100) / 100;
    cr->balance[0] = cr->sum;
    month++;

    for (int i = 1; i <= cr->time; i++) {
      cr->year[i] = month == 13 ? ++year : year;
      if (month == 13) month = 1;
      int y = yearv(year);
      day = (y && month == 2) ? 29 : days[month];
      cr->day[i] = cr->day[0] > day ? day : cr->day[0];
      cr->day[i + 1] = 0.0;
      cr->month[i] = month++;

      double d = cr->month[i] == 1 ? days[12] : days[cr->month[i - 1]];
      if (y && cr->month[i] == 3) d++;
      double i1 = 366.0, i2 = 365.0;
      if (!y) {
        i1 = 365.0;
        if (yearv(year - 1)) i2 = 366.0;
      }
      d = cr->month[i] == 1 ? (d - cr->day[i - 1]) / i2 + cr->day[i] / i1
                            : (d - cr->day[i - 1] + cr->day[i]) / i1;

      cr->procent[i] = cr->balance[i - 1] * cr->percent * d;
      cr->procent[i] = round(cr->procent[i]) / 100;
      cr->pay[i] = cr->debt + cr->procent[i];
      cr->balance[i] = cr->balance[i - 1] - cr->debt;
      cr->all_pay += cr->pay[i];
      cr->overpayment += cr->procent[i];
    }
  }
  sprintf(cr->all_pay_c, "%.2f", cr->all_pay);
  sprintf(cr->overpayment_c, "%.2f", cr->overpayment);
}

void transfer(double *val, char *str) { sprintf(str, "%.2f", *val); }

void deposit_calc(struct deposit *dp) {
  int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int day = (int)dp->day[0], month = dp->month[0], year = dp->year[0];
  int month_end = dp->month[0] + dp->time % 12;
  int year_end = dp->year[0] + (int)(dp->time / 12);
  if (month_end > 12) month_end -= 12, year_end++;
  int all_days = days[month] - (int)dp->day[0];
  for (int i = year; i <= year_end; i++) {
    for (int j = (i == year) ? month + 1 : 1;
         j <= ((i == year_end) ? month_end : 12); j++) {
      all_days += (year_end == i && month_end == j) ? (int)dp->day[0] : days[j];
      if (j == 2 && yearv(i)) all_days++;
    }
  }
  int per = periud(day, month, year, dp->periud, day);
  dp->balance[0] = dp->sum;
  dp->all_procent = 0.0;
  double procent = 0.0, dohod = 0.0;
  int date = 1, new_nalog = 0;
  cash(dp, day, month, year, &date);
  for (int i = 1, step = 0; i <= all_days; i++) {
    day++;
    step++;
    if (month == 2 && yearv(year)) {
      if (day > (days[month] + 1)) day = 1, month++;
    } else {
      if (day > days[month]) {
        day = 1;
        if (++month > 12) month = 1, year++;
      }
    }

    if (month == 1 && day == 1) new_nalog = 1;
    double d = yearv(year) ? 366.0 : 365.0;
    procent += dp->balance[date - 1] * dp->percent / d;
    cash(dp, day, month, year, &date);

    if (step == per || (step != per && day == dp->day[0] &&
                        month == month_end && year == year_end)) {
      if (day == dp->day[0] && month == month_end && year == year_end) {
        new_nalog = 1;
        dohod += round(procent) / 100;
      }
      if (new_nalog && (dohod - 75000) > 0)
        dp->all_nalog += (dohod - 75000) * dp->nalog / 100, dohod = 0;

      step = 0;
      dp->day[date] = day;
      dp->day[date + 1] = 0.0;
      dp->month[date] = month;
      dp->year[date] = year;

      dp->procent[date] = round(procent) / 100;
      dohod += dp->procent[date];
      dp->all_procent += dp->procent[date];
      dp->balance[date] = dp->kapital
                              ? dp->balance[date - 1] + dp->procent[date]
                              : dp->balance[date - 1];
      procent = 0;
      per = periud(dp->day[date], dp->month[date], dp->year[date], dp->periud,
                   dp->day[0]);
      dp->all_cash = dp->balance[date];
      date++;
    }
  }
}

int periud(int day, int month, int year, int per, int day_one) {
  int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int ret = 1;
  int i = 0;
  switch (per) {
    case 0:
      ret = 1;
      break;
    case 1:
      ret = 7;
      break;
    case 2:
      ret = days[month] - day;
      if (month == 12) month = 1;
      ret += (day_one > days[month]) ? days[month] : day_one;
      if (month == 2 && yearv(year)) ret++;
      break;
    case 6:
      ret = 0;
      break;
    default:
      i = (per == 4) ? 6 : 3;
      if (per == 5) i = 12;
      ret = days[month++] - day;
      for (int j = 1; j <= i; j++, month++) {
        if (month == 13) month = 1, year++;
        ret += (day_one > days[month] || j < i) ? days[month] : day_one;
        if (month == 2 && yearv(year)) ret++;
      }
      break;
  }
  return ret;
}

void cash(struct deposit *dp, int day, int month, int year, int *date) {
  for (int i = 0; dp->add->day[i] > 0; i++) {
    if (day == dp->add->day[i] && month == dp->add->month[i] &&
        year == dp->add->year[i]) {
      dp->day[*date] = day;
      dp->month[*date] = month;
      dp->year[*date] = year;
      dp->balance[*date] = dp->balance[*date - 1] + dp->add->sum[i];
      (*date)++;
    }
  }
}
