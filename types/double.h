#pragma once
#ifndef _DOUBLE_TYPE_
#define _DOUBLE_TYPE_
#include "../types.h"
// вспомогательный макрос для создания коэффициента из значения int без ссылок и указателей
#define new_double(value) ({ \
    double _temp = (value); \
    _new_double((void*)&_temp); \
})

// Функции для работы с хранением коэффициентов
coef *copy_double( const coef *src );
coef *_new_double( void* value );
void del_double( coef* arg );
char *to_string_double(coef *coefficient);

// Функции для выполнения арифметических операций
coef *sum_double( const coef *a, const coef *b);
coef *sub_double( const coef *a, const coef *b);
coef *mul_double( const coef *a, const coef *b);
coef *pow_double( const coef *base, const size_t exponent);
coef *get_one_double();
coef *get_zero_double();
size_t get_size_double();

// Функция для получения информации о структуре коэффициента
const type_info* get_double_type_info();

#endif