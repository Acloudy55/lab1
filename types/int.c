#include "int.h"
//
//
// Общий буффер
static char *buff = NULL;
//
//
//
coef *copy_int( const coef *src )
{
    if (src){
        coef *res = _new_int(src->data);
        return res;
    }
    else
    {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
};
//
//
//
coef *_new_int(void* value)
{
    if (!value)
    {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
    coef *temp = (coef*) malloc(sizeof(coef));
    if (!temp)
    {
        log_error(ERR_MEMORY_ALLOCATION_FAILED);
        del_int(temp);
        return NULL;
    }
    temp->type = get_int_type_info();
    temp->data = malloc(sizeof(int));
    if (!(temp->data))
    {
        log_error(ERR_MEMORY_ALLOCATION_FAILED);
        del_int(temp);
        return NULL;
    }
    if (value != NULL)
    {
        memcpy(temp->data, value, sizeof(int));
    }
    else
    {
        *(int*)temp->data = 0;
    }
    return temp;
};
//
//
//

void del_int(coef* arg)
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
//
//
//
size_t get_size_int()
{
    return (sizeof(int));
};
//
//
// Буффер статический
char *to_string_int(coef *coefficient)
{
    if (!coefficient)
    {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
    if (coefficient->data)
    {
        size_t buffer_size = 16; 
        char *buff = (char*)malloc(buffer_size);
        if (!buff) {
            log_error(ERR_MEMORY_ALLOCATION_FAILED);
            return NULL;
        }
        memset(buff, 0, buffer_size);
        int* value = (int*)(coefficient->data);
        snprintf(buff, buffer_size, "%d", *value);
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
coef *sum_int( const coef *a, const coef *b)
{
    if (!a || !b)
    {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
    if (a->data && b->data){
        int val_1 = *(int*)(a->data);
        int val_2 = *(int*)(b->data);
        return new_int(val_1 + val_2);
    }
    else
    {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
};

coef *sub_int( const coef *a, const coef *b)
{
    if (a->data && b->data){

        int val_1 = *(int*)a->data;
        int val_2 = *(int*)b->data;
        return new_int(val_1 - val_2);
    }
    else
    {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
};

coef *mul_int( const coef *a, const coef *b)
{
    if (a->data && b->data){

        int val_1 = *(int*)a->data;
        int val_2 = *(int*)b->data;
        return new_int(val_1 * val_2);
    }
    else
    {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
};
coef *pow_int(const coef *base, const size_t exponent) {
    if (!base || !base->data) {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
    int val = *(int*)base->data;
    int result = pow(val, (int)exponent); // CHECK THIS
    return _new_int(&result); 
}
//
//
//
//
//
// Вспомогательные функции для создания коэффициентов с определенным значением
coef *get_one_int()
{
    return new_int(1);
};
coef *get_zero_int()
{
    return new_int(0);
};
//
//
//
//
//
static type_info *int_type_info = NULL;
const type_info* get_int_type_info()
{
    if (int_type_info == NULL){
        int_type_info = malloc(sizeof(type_info));
        int_type_info->size = sizeof(int);
        int_type_info->sum = &sum_int;
        int_type_info->sub = &sub_int;
        int_type_info->mul = &mul_int;
        int_type_info->power = &pow_int;
        int_type_info->copy = &copy_int;
        int_type_info->new = &_new_int;
        int_type_info->del = &del_int;
        int_type_info->get_size = &get_size_int;
        int_type_info->to_string = &to_string_int;
        int_type_info->zero = &get_zero_int;
        int_type_info->one = &get_one_int;
    };
    return int_type_info;
};