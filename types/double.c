#include "double.h"
//
//
//
static char *buff = NULL;

coef *copy_double( const coef *src )
{
    if (src){
        coef *res = _new_double(src->data);
        return res;
    }
    else
    {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
};

coef *_new_double(void* value)
{
    coef *temp = (coef*) malloc(sizeof(coef));
    if (!temp)
    {
        log_error(ERR_MEMORY_ALLOCATION_FAILED);
        return NULL;
    }
    temp->type = get_double_type_info();
    temp->data = malloc(sizeof(double));
    if (!(temp->data))
    {
        log_error(ERR_MEMORY_ALLOCATION_FAILED);
        free(temp);
        return NULL;
    }
    if (value != NULL)
    {
        memcpy(temp->data, value, sizeof(double));
    }
    else
    {
        *(double*)temp->data = 0.0;
    }
    return temp;
};



void del_double(coef* arg)
{
    if (!arg) 
    {
        log_error(ERR_NULL_POINTER);
        return;
    }
    if (arg->data)
    {
        free(arg->data);
    }
    free(arg);
};

size_t get_size_double()
{
    return (sizeof(double));
};

char *to_string_double(coef *coefficient)
{
    if (!coefficient)
    {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
    if (coefficient->data)
    {
        size_t buffer_size = 30; 
        char *buff = (char*)malloc(buffer_size);
        if (!buff) {
            log_error(ERR_MEMORY_ALLOCATION_FAILED);
            return NULL;
        }
        memset(buff, 0, buffer_size);
        double* value = (double*)(coefficient->data);
        snprintf(buff, buffer_size, "%g", *value);
        return buff;
    }
    else
    {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
};
////////////////////////////////////////////////////////////////
///////////////// Арифметические операции //////////////////////
////////////////////////////////////////////////////////////////
coef *sum_double( const coef *a, const coef *b)
{
    if (!a || !b)
    {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
    if (a->data && b->data){
        double val_1 = *(double*)(a->data);
        double val_2 = *(double*)(b->data);
        return new_double(val_1 + val_2);
    }
    else
    {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
};

coef *sub_double( const coef *a, const coef *b)
{
    if (a->data  && b->data ){

        double val_1 = *(double*)a->data;
        double val_2 = *(double*)b->data;
        return new_double(val_1 - val_2);
    }
    else
    {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
};

coef *mul_double( const coef *a, const coef *b)
{
    if (a->data && b->data ){

        double val_1 = *(double*)a->data;
        double val_2 = *(double*)b->data;
        return new_double(val_1 * val_2);
    }
    else
    {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
};
coef *pow_double(const coef *base, const size_t exponent) {
    if (!base ) {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
    if (!(base->data)) {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
    double val = *(double*)base->data;
    double result = pow(val, (double)exponent); // CHECK THIS
    return _new_double(&result); 
}
//
//
//
coef *get_one_double()
{
    return new_double(1.0);
};
coef *get_zero_double()
{
    return new_double(0.0);
};
//
//
//
static type_info *double_type_info = NULL;
const type_info* get_double_type_info()
{
    if (double_type_info == NULL){
        double_type_info = malloc(sizeof(type_info));
        double_type_info->size = sizeof(double);
        double_type_info->sum = &sum_double;
        double_type_info->sub = &sub_double;
        double_type_info->mul = &mul_double;
        double_type_info->power = &pow_double;
        double_type_info->copy = &copy_double;
        double_type_info->new = &_new_double;
        double_type_info->del = &del_double;
        double_type_info->get_size = &get_size_double;
        double_type_info->to_string = &to_string_double;
        double_type_info->zero = &get_zero_double;
        double_type_info->one = &get_one_double;
    };
    return double_type_info;
};