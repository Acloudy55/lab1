#pragma once
#include <stdlib.h>
#include "error.h"
#include "coef.h"

// coef** указатель на первый элемент статического массива для хранения коэффициентов полинома
// length - длина многочлена (количество одночленов)
// type - информация о хранящихся внутри коэффициентах (тип одинаковый у всех)
typedef struct polynomial{
    coef** coefficients;
    size_t length;
    const type_info* type;
} polynomial;

// создание нового полинома через указатель на статический массив int, double, float и т.д.
polynomial *new_polynomial(void* mas, const type_info *type, size_t size);
// копирование полинома (инициализация нового, deepcopy старого)
polynomial* copy_polynomial(polynomial* src);

// создание полинома суммы/разности/произведения двух полиномов
polynomial* add_polynomial(polynomial* left, polynomial* right);
polynomial* sub_polynomial(polynomial* left, polynomial* right);
polynomial* mul_polynomial(polynomial* left, polynomial* right); 

// возведение полинома в степень, умножение на скаляр, 
// получение значения полинома при заданном аргументе
// композиция полиномов
polynomial* pow_polynomial(polynomial* poly, size_t exponential);
polynomial* scalar_mul_polynomial(polynomial* poly, coef *scalar);
coef* value_polynomial(polynomial*, const coef *argument);
polynomial* compose_polynomial(polynomial* poly, polynomial* argument);

// удаление полинома и преобразование в строку (статический буфер)
char* to_string_polynomial(polynomial* poly);
void delete_polynomial(polynomial* poly);


