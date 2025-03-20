#pragma once
#ifndef _INT_TYPE_
#define _INT_TYPE_
#include "../types.h"
// вспомогательный макрос для создания коэффициента из значения int без ссылок и указателей
#define new_int(value) ({ \
    int _temp = (value); \
    _new_int((void*)&_temp); \
})

// Функции для работы с хранением коэффициентов
coef *copy_int( const coef *src );
coef *_new_int( void* value );
void del_int( coef* arg );
char *to_string_int(coef *coefficient);

// Функции для выполнения арифметических операций
coef *sum_int( const coef *a, const coef *b);
coef *sub_int( const coef *a, const coef *b);
coef *mul_int( const coef *a, const coef *b);
coef *pow_int( const coef *base, const size_t exponent);
coef *get_one_int();
coef *get_zero_int();

size_t get_size_int();

// Функция для получения информации о структуре коэффициента
const type_info* get_int_type_info();

#endif