#pragma once
#ifndef _COMPLEX_TYPE_
#define _COMPLEX_TYPE_
#include "../coef.h"

// Все функции для работы с комплексными числами реализованы полиморфно
// за исключением new_complex_coef - упрощение создания
// get_one_complex - тип внутри complex_data не получить без передачи конкретных коэффициентов
// get_zero_complex - также без конкретных коэффициентов

// Структура для хранения данных комплексного числа
typedef struct complex_data {
    coef* re; // указатель на значение float, double
    coef* im; // указатель на значение float, double
    bool is_allocated;
} complex_data;

// Функции для работы с хранением коэффициентов
coef *copy_complex( const coef *src );
coef *_new_complex( coef *real, coef *imaginary);
void del_complex( coef *arg );
char *to_string_complex(coef *coefficient);

// Функции для выполнения арифметических операций
coef *sum_complex( const coef *a, const coef *b);
coef *sub_complex( const coef *a, const coef *b);
coef *mul_complex( const coef *a, const coef *b);
coef *pow_complex( const coef *base, const size_t exponent);
// используется только при степени полинома 0, 
// значит обращается в единицу на реальной оси re = 1, im = 0
coef *get_one_complex(); 
coef *get_zero_complex(); // re = 0, im = 0

size_t get_size_complex();

// Вспомогательная функция для создания коэффициента из значения float или double
coef *new_complex_coef(float re, float im);

// Функция для получения информации о структуре коэффициента
const type_info *get_complex_type_info();

#endif