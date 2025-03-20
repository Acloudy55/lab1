#pragma once
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "error.h"


typedef struct coef coef;

typedef coef *(*binary_operator)(const coef *a, const coef *b);
typedef coef *(*power_operator)(const coef *a, const size_t b); //size_t as unsigned int
typedef coef *(*unary_operator)(const coef *src);
typedef coef *(*allocator)(void* value);
typedef coef *(*multi_allocator)(void* value);
typedef size_t (*size_getter)();
typedef void (*del_t)(coef *arg);
typedef char *(*to_string_t)(coef*);
typedef coef *(*constant)();

// Структура, определяющая работу coef определенного типа
typedef struct type_info {
    size_t size;
    binary_operator sum;
    binary_operator sub;
    binary_operator mul;
    power_operator power;
    unary_operator copy;
    allocator new;
    del_t del;
    size_getter get_size;
    to_string_t to_string;
    constant one;
    constant zero;
} type_info;

// Пользовательский тип данных coef, 
// который в последствии используется 
// для удобной работы с коэффициентами в полиномах

typedef struct coef {
    void* data; // указатель на значение int, float, double, complex
    const type_info *type;
} coef;