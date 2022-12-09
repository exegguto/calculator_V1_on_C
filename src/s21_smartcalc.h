// Copyright 2022 exegguto

#ifndef _S21_SMARTCALC_H_
#define _S21_SMARTCALC_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#define STKDPTH 300 /* Глубина стека */
#define ESP 1e-7

/* Значения, возвращаемые функцией parse */
#define VAL 0   /* В стек занесено новое значение */
#define ADD 1   /* Сложение */
#define SUB 2   /* Вычитание */
#define MUL 3   /* Умножение */
#define DIV 4   /* Деление */
#define SIN 5   /* sin */
#define COS 6   /* cos */
#define TAN 7   /* tan */
#define CTG 8   /* ctg */
#define SQRT 9  /* sqrt */
#define LN 10   /* ln */
#define ASIN 11 /* asin */
#define ACOS 12 /* acos */
#define ATAN 13 /* atan */
#define LOG 14  /* log */
#define MOD 15  /* mod */
#define POW 16  /* pow ^ */
#define SOF -1  /* Переполнение стека */
#define SUF -2  /* В стеке недостаточно операндов */
#define UNK -3  /* Неопознанное значение */
#define ENAN -4
#define EINF -5
/* Описание стpуктуpы(элемента стека) */
struct st {
  char c;
  struct st *next;
};

/* Пpототипы функций */

/**
 * записывает на стек (на веpшину котоpого указывает HEAD)
 * символ a . Возвpащает указатель на новую веpшину стека
 * @param PTR - новая веpшина стека
 * @param HEAD - стек
 * @param a - символ
 */
struct st *push(struct st *, char);

/**
 * Удаляет символ с веpшины стека.
 * Возвpащает удаляемый символ.
 * Изменяет указатель на веpшину стека
 * @param PTR - адpес веpшины стека
 * @param HEAD - стек
 * @param a - символ с веpшины стека
 * @return Возвpащает удаляемый символ
 */
char DEL(struct st **);

/**
 * Алгоритм Дейкстры
 * @param outstr - строка для разбора
 * @param x указатель на строку содержащюю параметр Х
 */
void algoritm_d(char *);

/**
 * пpиоpитет аpифм. опеpации
 * @param a - символ
 * @return возвpащает пpиоpитет аpифм. опеpации
 */
int PRIOR(char);

/**
 * @brief Обработка ошибок и Польская нотация
 *
 * @param str строка с элементами
 * @param x указатель на строку содержащюю параметр Х
 * @return  стек с элементами
 */
int operand(const char *str, double *rez, double x);

/**
 * @brief Обработчик элементов из строки
 *
 * @param s строка для обработки
 * @param scount счетчик элементов в стеке
 * @param x
 * @return int код операции либо ошибки
 */
int parse(char *, int *, double);

#define MAX 700

struct credits {
  double sum;      // общая сумма кредита
  int time;        // срок
  double percent;  // процентная ставка
  int type;  // тип (аннуитетный, дифференцированный)
  double all_pay;       // общая выплата
  double overpayment;   // переплата по кредиту
  double day[MAX];      // день
  int month[MAX];       // месяц
  int year[MAX];        // год
  double pay[MAX];      // ежемесячный платеж
  double debt;          // основной долг
  double procent[MAX];  // проценты
  double balance[MAX];  // Остаток долга

  char all_pay_c[250];      // общая выплата
  char overpayment_c[250];  // переплата по кредиту
};

/**
 * @brief Расчет високосного года
 *
 * @param year год для анализа
 * @return int 0 - не високосный, 1 - високосный
 */
int yearv(int year);

/**
 * @brief Кредитный калькулятор
 *
 * @param cr Структура с входными и выходными данными
 */
void credit_calc(struct credits *);

struct deposit {
  double sum;              // общая сумма кредита
  int time;                // срок в месяцах
  double day[MAX];         // день
  int month[MAX];          // месяц
  int year[MAX];           // год
  double percent;          // процентная ставка
  double nalog;            // налоговая ставка
  int periud;              // периодичность выплат
                           // 0 - каждый день
                           // 1 -раз в неделю
                           // 2 - раз в месяц
                           // 3 - раз в квартал
                           // 4 - раз в пол года
                           // 5 - раз в год
                           // 6 - в конце срока
  int kapital;             // капитализация процентов
  struct popolnenie *add;  // список пополнений и снятий

  double procent[MAX];  // проценты
  double all_nalog;     // сумма налога
  double all_cash;      // сумма на вкладе к концу срока
  double all_procent;   // сумма процентов

  double balance[MAX];  // текущий баланс счета
};

struct popolnenie {
  double sum[MAX];  // общая сумма кредита
  double day[MAX];  // день
  int month[MAX];   // месяц
  int year[MAX];    // год
};

/**
 * @brief калькулятор доходности вкладов
 *
 * @param dp Структура с входными и выходными данными
 */
void deposit_calc(struct deposit *);

/**
 * @brief расчет количества дней в периоде
 *
 * @return int
 */
int periud(int, int, int, int, int);

/**
 * @brief проверка даты на пополнение или снятие в этот день
 *
 * @param dp
 * @param day
 * @param month
 * @param year
 * @param date
 */
void cash(struct deposit *dp, int day, int month, int year, int *date);

/**
 * @brief перевод из дабл в строку с двумя знаками после запятой
 *
 * @param val исходное число
 * @param str выходная строка
 */
void transfer(double *val, char *str);

#ifdef __cplusplus
}
#endif

#endif  // _S21_SMARTCALC_H_"
