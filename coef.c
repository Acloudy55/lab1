#ifndef _TYPES_DEFINITION_
#define _TYPES_DEFINITION_
#include "coef.h"

coef *copy_coef(coef* src)
{
    coef *result = src->type->copy(src);
    return result;
};
//
//
//
//
//
//ADD ALL TYPES
coef *new_coef(void* value, const type_info* type)
{
    if (!value)
    {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
    coef *result = type->new(value);
    return result;
};
//
//
//
//
//
//
char *to_string_coef(coef* arg)
{
    if (arg)
    {
        return arg->type->to_string(arg);
    }
    else
    {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
};

void delete_coef(coef* arg)
{
    if (arg)
    {
        arg->type->del(arg);
    }
    else    
    {
        log_error(ERR_NULL_POINTER);
    }
};


coef *sum_coef(coef *left, coef *right)
{
    if (left && right)
    {
        if (left->type==right->type)
        {
            coef *result = left->type->sum(left, right);
            return result;
        }
        else
        {
            log_error(ERR_TYPE_MISMATCH);
            return NULL;
        }
    }
    else
    {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
};
coef *sub_coef(coef *left, coef *right)
{
    if (left && right)
    {
        if (left->type==right->type)
        {
            coef *result = left->type->sub(left, right);
            return result;
        }
        else{
            log_error(ERR_TYPE_MISMATCH);
        }
    }
    else
    {
        log_error(ERR_NULL_POINTER);
    }
    return NULL;
    //what should it return
};
coef *mul_coef(coef *left, coef *right)
{
    if (left && right)
    {
        if (left->type==right->type)
        {
            coef *result = left->type->mul(left, right);
            return result;
        }
        else{
            log_error(ERR_TYPE_MISMATCH);
        }
    }
    else
    {
        log_error(ERR_NULL_POINTER);
    }
    return NULL;
    //what should it return
};
coef *power_coef(const coef *base, size_t exponential)
{
    if (base!=NULL)
    {
        coef *result = base->type->power(base, exponential);
        return result;
    }
    else
    {
        log_error(ERR_NULL_POINTER);
    }
    return NULL;
    //what should it return
};

coef *zero_coef(const type_info *type)
{
    return type->zero();
}
coef *one_coef(const type_info *type)
{
    return type->one();
}

#endif
