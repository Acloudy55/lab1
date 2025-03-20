#pragma once
#ifndef _FLOAT_TYPE_
#define _FLOAT_TYPE_
#include "../types.h"
// вспомогательный макрос для создания коэффициента из значения int без ссылок и указателей
#define new_float(value) ({ \
    float _temp = (value); \
    _new_float((void*)&_temp); \
})

// Функции для работы с хранением коэффициентов
coef *copy_float( const coef *src );
coef *_new_float( void* value );
void del_float( coef* arg );
char *to_string_float(coef *coefficient);

// Функции для выполнения арифметических операций
coef *sum_float( const coef *a, const coef *b);
coef *sub_float( const coef *a, const coef *b);
coef *mul_float( const coef *a, const coef *b);
coef *pow_float( const coef *base, const size_t exponent);
coef *get_one_float();
coef *get_zero_float();
size_t get_size_float();

// Функция для получения информации о структуре коэффициента
const type_info* get_float_type_info();

#endif