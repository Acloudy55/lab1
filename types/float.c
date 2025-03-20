#include "float.h"
//
//
//
static char *buff = NULL;

coef *copy_float( const coef *src )
{
    if (src)
    {
        coef *res = _new_float(src->data);
        return res;
    }
    else
    {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
};

coef *_new_float(void* value)
{
    coef *temp = (coef*) malloc(sizeof(coef));
    if (!temp)
    {
        log_error(ERR_MEMORY_ALLOCATION_FAILED);
        return NULL;
    }
    temp->type = get_float_type_info();
    temp->data = malloc(sizeof(float));

    if (!(temp->data))
    {
        log_error(ERR_MEMORY_ALLOCATION_FAILED);
        free(temp);
        return NULL;
    }
    if (value)
    {
        memcpy(temp->data, value, sizeof(float));
    }
    else
    {
        *(float*)temp->data = 0.0f;
    }
    return temp;
};


void del_float(coef* arg)
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

size_t get_size_float()
{
    return (sizeof(float));
};

char *to_string_float(coef *coefficient)
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
        float* value = (float*)(coefficient->data);
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
coef *sum_float( const coef *a, const coef *b)
{
    if (!a || !b)
    {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
    if (!(a->data) || !(b->data))
    {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
    if (a->data != NULL && b->data != NULL){
        float val_1 = *(float*)(a->data);
        float val_2 = *(float*)(b->data);
        return new_float(val_1 + val_2);
    }
    else
    {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
};

coef *sub_float( const coef *a, const coef *b)
{
    if (a->data && b->data){

        float val_1 = *(float*)a->data;
        float val_2 = *(float*)b->data;
        return new_float(val_1 - val_2);
    }
    else
    {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
};

coef *mul_float( const coef *a, const coef *b)
{
    if (a->data && b->data){

        float val_1 = *(float*)a->data;
        float val_2 = *(float*)b->data;
        return new_float(val_1 * val_2);
    }
    else
    {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
};
coef *pow_float(const coef *base, const size_t exponent) {
    if (!base) {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
    if (!(base->data)) {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
    float val = *(float*)base->data;
    float result = powf(val, (float)exponent);
    return _new_float(&result); 
}
//
//
//
coef *get_one_float()
{
    return new_float(1.0f);
};
coef *get_zero_float()
{
    return new_float(0.0f);
};
//
//
//
static type_info *float_type_info = NULL;
const type_info* get_float_type_info()
{
    if (!float_type_info){
        float_type_info = malloc(sizeof(type_info));
        float_type_info->size = sizeof(float);
        float_type_info->sum = &sum_float;
        float_type_info->sub = &sub_float;
        float_type_info->mul = &mul_float;
        float_type_info->power = &pow_float;
        float_type_info->copy = &copy_float;
        float_type_info->new = &_new_float;
        float_type_info->del = &del_float;
        float_type_info->get_size = &get_size_float;
        float_type_info->to_string = &to_string_float;
        float_type_info->zero = &get_zero_float;
        float_type_info->one = &get_one_float;
    };
    return float_type_info;
};