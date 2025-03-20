# lab1
Polymorphic polynomials on C

## Описание
Этот проект представляет собой тестовую систему для работы с полиномами, написанную на языке C. Система позволяет создавать полиномы с коэффициентами различных типов (`INT`, `FLOAT`, `DOUBLE`, а также комплексные числа) и выполнять над ними разнообразные операции. Команды для работы с полиномами считываются из файла `input.txt`, который используется для тестов.

## Тестовая система
#### Основные возможности:
- **Создание полиномов**: Поддержка коэффициентов типов `INT`, `FLOAT`, `DOUBLE` и комплексных чисел.
- **Операции с полиномами**:
  - Сложение (`ADD_POLY [name1] [name2]`)
  - Вычитание (`SUB_POLY [name1] [name2]`)
  - Умножение (`MUL_POLY [name1] [name2]`)
  - Возведение в степень (`POW_POLY [name] [exponent]`)
  - Скалярное умножение (`SCAL_MUL_POLY [name] [scalar]`)
  - Композиция полиномов (`COMPOSE [result_name] [name1] [name2]`)
  - Вычисление значения полинома в точке (`VALUE [name] [argument]`)
- **Обработка ошибок**: Ошибки выводятся в `stderr` с помощью функции `log_error`.

## Библиотека `coef`
Библиотека `coef` предоставляет поддержку для работы с коэффициентами различных типов:

- **`INT`**: Целочисленные коэффициенты (например, `5`, `-3`).
- **`FLOAT`**: Вещественные коэффициенты с плавающей точкой одинарной точности (например, `1.5`, `-0.3`).
- **`DOUBLE`**: Вещественные коэффициенты с плавающей точкой двойной точности (например, `1.2345`, `0.0001`).
- **Комплексные числа**:
  - `COMPLEX INT`: Комплексные числа с целочисленными действительной и мнимой частями (например, `(1, 2)` означает `1 + 2i`).
  - `COMPLEX FLOAT`: Комплексные числа с действительной и мнимой частями типа `FLOAT` (например, `(1.5, 2.3)`).
  - `COMPLEX DOUBLE`: Комплексные числа с действительной и мнимой частями типа `DOUBLE` (например, `(1.2345, 0.0001)`).

Комплексные числа представлены в формате `(re, im)`, где `re` — действительная часть, а `im` — мнимая часть.

## Библиотека `polynomial`
Библиотека `polynomial` позволяет создавать полиномы и выполнять над ними операции. Она может использоваться как через команды в файле `input.txt`, так и напрямую в коде (не через консоль). Ниже описаны варианты использования библиотеки в коде.

### Создание полинома
Полиномы создаются с помощью функции `new_polynomial`, которая принимает массив коэффициентов, тип данных и степень полинома.

#### Пример создания полинома с целыми коэффициентами
```c
#include "polynomial.h"

int coefs[] = {1, 2, 3}; // Полином: 1 + 2x + 3x^2
polynomial *p = new_polynomial(coefs, get_int_type_info(), 3);
printf("Polynomial: %s\n", to_string_polynomial(p));
```
#### Пример создания полинома с целыми коэффициентами
```c
coef *complex_coefs[2];
complex_coefs[0] = new_complex_coef(1, 2); // 1 + 2i
complex_coefs[1] = new_complex_coef(3, 4); // 3 + 4i
polynomial *p_complex = new_polynomial(complex_coefs, get_complex_type_info(), 2);
printf("Complex Polynomial: %s\n", to_string_polynomial(p_complex));
```
### Операции над полиномами

Библиотека поддерживает следующие операции, которые можно вызывать напрямую в коде:

#### Сложение полиномов

```c
polynomial *sum = add_polynomial(p, p_complex); 
printf("Sum: %s\n", to_string_polynomial(sum));`
```

#### Вычитание полиномов

```c
polynomial *diff = sub_polynomial(p, p_complex); 
printf("Difference: %s\n", to_string_polynomial(diff));`
```
#### Умножение полиномов

```c

polynomial *product = mul_polynomial(p, p_complex); 
printf("Product: %s\n", to_string_polynomial(product));`
```

#### Возведение в степень
```c
polynomial *powered = pow_polynomial(p, 3); // p^3 
printf("Powered: %s\n", to_string_polynomial(powered));`
```
#### Скалярное умножение
```c
coef *scalar = new_int(2); 
polynomial *scaled = scal_mul_polynomial(p, scalar); printf("Scaled: %s\n", to_string_polynomial(scaled));`
```
#### Композиция полиномов
```c
polynomial *composed = compose_polynomial(p, p_complex); 
printf("Composed: %s\n", to_string_polynomial(composed));
```
#### Вычисление значения в точке
```c
coef *arg = new_int(2); 
coef *value = value_polynomial(p, arg); 
printf("Value at 2: %s\n", to_string_coef(value));`
```
### Примечание

Для корректной работы операций необходимо, чтобы типы коэффициентов полиномов совпадали. 
В противном случае будет вызвана ошибка, которая обработается через log_error.

## Использование файла input.txt

Файл input.txt используется для тестовых команд. Пользователи могут редактировать этот файл, добавляя команды для создания полиномов и выполнения операций. Программа считывает команды из этого файла при запуске и выполняет их последовательно.

### Пример содержимого input.txt

```txt
CREATE_POLY p1 INT 1,2,3 
CREATE_POLY p2 INT 4,5 
ADD_POLY p1 p2 
CREATE_POLY p3 COMPLEX (1,2),(3,2)
SCAL_MUL_POLY p3 (2.0,0.3) 
VALUE p1 2
```
## Установка и запуск

1. **Клонирование репозитория**:
 ```bash 
 git clone https://github.com/yourusername/yourrepository.git 
 cd yourrepository
 ```
2. **Компиляция** и **запуск**:
```bash
make && ./program.exe  
```
## Структура проекта

- main.c: Главный файл с тестовым кодом.
- polynomial.c: Логика работы с полиномами.
- coef.c: Функции для работы с коэффициентами.
- polynomial.h, coef.h: Заголовочные файлы.
- input.txt: Файл с тестовыми командами.