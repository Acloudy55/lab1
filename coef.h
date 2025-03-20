#pragma once
#ifndef _COEF_DEFINITION_
#define _COEF_DEFINITION_
#include "types.h"
#include "types/float.h"
#include "types/int.h"
#include "types/double.h"
#include "types/complex.h"
coef *sum_coef(coef *left, coef *right);
coef *sub_coef(coef *left, coef *right);
coef *mul_coef(coef *left, coef *right);
coef *power_coef(const coef *base, size_t exponential);
coef *copy_coef(coef *src);
coef *new_coef(void* value, const type_info* type);
char *to_string_coef(coef *arg);
void delete_coef(coef *arg);
coef *zero_coef(const type_info *type);
coef *one_coef(const type_info *type);
#endif