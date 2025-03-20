#include "complex.h"
//
//
//
static char *buff = NULL;
//
//
//
static complex_data *allocate_complex_data(){
    complex_data *res = (complex_data*) malloc(sizeof(complex_data));
    if (!res)
    {
        log_error(ERR_MEMORY_ALLOCATION_FAILED);
        return NULL;
    }
    res->re = malloc(sizeof(coef));
    if (!(res->re))
    {
        log_error(ERR_MEMORY_ALLOCATION_FAILED);
        free(res);
        return NULL;
    }
    res->im = malloc(sizeof(coef));
    if (!(res->im))
    {
        log_error(ERR_MEMORY_ALLOCATION_FAILED);
        free(res->re);
        free(res);
        return NULL;
    }
    return res;
}
static void deallocate_complex_data(complex_data *data){
    if (data)
    {
        free(data->re);
        free(data->im);
        free(data);
    }
    else{
        log_error(ERR_NULL_POINTER);
    }
}
//
//
//
coef *copy_complex(const coef *src) {
    if (!src) {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
    if (!(src->data)) {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
    complex_data *src_data = (complex_data*) src->data;
    return _new_complex(src_data->re, src_data->im);
}

//Обертка для присвоения в таблицу внутри type
static coef *new_complex_wrapper(void *args) {
    complex_data *init = (complex_data*) args;
    return _new_complex(init->re, init->im);
}

coef *_new_complex(coef* real, coef* imaginary) {
    if (!real || !imaginary) {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
    if (real->type != imaginary->type) {
        log_error(ERR_TYPE_MISMATCH);
        return NULL;
    }
    coef *temp = (coef*) malloc(sizeof(coef));
    if (temp == NULL) {
        log_error(ERR_MEMORY_ALLOCATION_FAILED);
        return NULL;
    }
    temp->type = get_complex_type_info();
    temp->data = (void*) allocate_complex_data();
    if (temp->data == NULL) {
        log_error(ERR_MEMORY_ALLOCATION_FAILED);
        free(temp);
        return NULL;
    }
    complex_data *data = (complex_data*) temp->data;
    // Use copy_coef to do a deep copy of each part
    data->re = copy_coef(real);
    data->im = copy_coef(imaginary);
    return temp;
}


void del_complex(coef *c)
{
    if (!c) return;

    complex_data *data = (complex_data*)c->data;
    if (!data) {
        free(c);
        return;
    }

    // Удаляем только если коэффициенты были созданы внутри new_complex_coef
    if (data->is_allocated) {
        delete_coef(data->re);
        delete_coef(data->im);
    }

    free(data);
    free(c);
}


size_t get_size_complex()
{
    return (sizeof(complex_data));
};

char *to_string_complex(coef *coefficient) {
    if (!coefficient || !coefficient->data) {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
    complex_data* value = (complex_data*)coefficient->data;
    char *real_str = value->re->type->to_string(value->re);
    char *imag_str = value->im->type->to_string(value->im);
    if (!real_str || !imag_str) {
        free(real_str);
        free(imag_str);
        return NULL;
    }
    size_t buffer_size = strlen(real_str) + strlen(imag_str) + 10;
    char* temp = (char*)malloc(buffer_size);
    if (!temp) {
        log_error(ERR_MEMORY_ALLOCATION_FAILED);
        free(real_str);
        free(imag_str);
        return NULL;
    }
    temp[0] = '\0';
    strncat(temp, real_str, buffer_size - strlen(temp) - 1);
    if (value->im->data && *(float*)value->im->data >= 0) {
        strncat(temp, " + ", buffer_size - strlen(temp) - 1);
    }
    strncat(temp, imag_str, buffer_size - strlen(temp) - 1);
    strncat(temp, "i", buffer_size - strlen(temp) - 1);
    free(real_str);
    free(imag_str);
    return temp;
}
////////////////////////////////////////////////////////////////
///////////////// Арифметические операции //////////////////////
////////////////////////////////////////////////////////////////
coef *sum_complex(const coef *a, const coef *b)
{
    if (!a || !b)
    {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
    if (a->type != get_complex_type_info() || b->type != get_complex_type_info())
    {
        log_error(ERR_TYPE_MISMATCH);
        return NULL;
    }
    if (a->data != NULL && b->data != NULL){
        complex_data *val_1 = (complex_data*)(a->data);
        complex_data *val_2 = (complex_data*)(b->data);
        return _new_complex(val_1->re->type->sum(val_1->re, val_2->re), val_1->re->type->sum(val_1->im, val_2->im));
    }
    else
    {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
};

coef *sub_complex( const coef *a, const coef *b)
{
    if (a->data != NULL && b->data != NULL){

        complex_data *val_1 = (complex_data*)(a->data);
        complex_data *val_2 = (complex_data*)(b->data);
        return _new_complex(val_1->re->type->sub(val_1->re, val_2->re), val_1->re->type->sub(val_1->im, val_2->im));
    }
    else
    {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
};

coef *mul_complex( const coef *a, const coef *b)
{
    if (a->data != NULL && b->data != NULL){

        complex_data *val_1 = (complex_data*)a->data;
        complex_data *val_2 = (complex_data*)b->data;
        
        // Реальная часть: (re1 * re2) - (im1 * im2)
        coef *real_part = val_1->re->type->mul(val_1->re, val_2->re); // re1 * re2
        coef *im_part_re = val_1->im->type->mul(val_1->im, val_2->im); // im1 * im2
        coef *real_result = val_1->re->type->sub(real_part, im_part_re); // (re1 * re2) - (im1 * im2)

        // Мнимая часть: (re1 * im2) + (im1 * re2)
        coef *im_part = val_1->re->type->mul(val_1->re, val_2->im);  // re1 * im2
        coef *real_part_im = val_1->im->type->mul(val_1->im, val_2->re); // im1 * re2
        coef *im_result = val_1->re->type->sum(im_part, real_part_im); // (re1 * im2) + (im1 * re2)

        // Создаем новый комплексный коэффициент
        coef *result = _new_complex(real_result, im_result);

        // Удаляем вспомогательные коэффициенты
        delete_coef(real_part);
        delete_coef(im_part_re);
        delete_coef(im_part);
        delete_coef(real_part_im);

        return result;
    }
    else
    {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
};

coef *pow_complex(const coef *base, const size_t exponent)
{
    if (base == NULL || base->data == NULL) {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
    
    complex_data *c_data = (complex_data *) base->data;
    
    
    if (c_data->re == NULL || c_data->im == NULL) {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
    
    if (c_data->re->type != c_data->im->type) {
        log_error(ERR_TYPE_MISMATCH);
        return NULL;
    }
    
    const type_info *underlying_type = c_data->re->type;
    
    coef *result = _new_complex(underlying_type->one(), underlying_type->zero());
    if (result == NULL) {
        log_error(ERR_MEMORY_ALLOCATION_FAILED);
        return NULL;
    }
    
    if (exponent == 0) {
        return result;
    }
    if (exponent == 1) {
        delete_coef(result);
        return copy_complex(base);
    }
    
    coef *b = copy_complex(base);
    size_t exp = exponent;
    
    while(exp > 0) {
        if(exp % 2 == 1) {
            coef *temp = mul_complex(result, b);
            delete_coef(result);
            result = temp;
        }
        exp /= 2;
        if(exp > 0) {
            coef *temp = mul_complex(b, b);
            delete_coef(b);
            b = temp;
        }
    }
    
    delete_coef(b);
    return result;
}



// shouldn't be used
coef *get_one_complex()
{
    
    coef *res = _new_complex(get_one_float(), get_zero_float());

    return res;
}

coef *get_zero_complex()
{

    coef *res = _new_complex(get_zero_float(), get_zero_float());

    return res;
}


//
//
// Пользовательская функция для быстрой инициализации complex с типом float
coef *new_complex_coef(float re, float im)
{
    coef *real_coef = new_float(re);
    coef *imag_coef = new_float(im);
    if (!real_coef || !imag_coef) {
        delete_coef(real_coef);
        delete_coef(imag_coef);
        return NULL;
    }
    coef *result = _new_complex(real_coef, imag_coef);
    if (!result) {
        delete_coef(real_coef);
        delete_coef(imag_coef);
        return NULL;
    }
    ((complex_data*)result->data)->is_allocated = true;
    return result;
}




static type_info *complex_type_info = NULL;
const type_info* get_complex_type_info()
{
    if (complex_type_info == NULL){
        complex_type_info = malloc(sizeof(type_info));
        complex_type_info->size = sizeof(complex_data);
        complex_type_info->sum = &sum_complex;
        complex_type_info->sub = &sub_complex;
        complex_type_info->mul = &mul_complex;
        complex_type_info->power = &pow_complex;
        complex_type_info->copy = &copy_complex;
        complex_type_info->new = &new_complex_wrapper;
        complex_type_info->del = &del_complex;
        complex_type_info->get_size = &get_size_complex;
        complex_type_info->to_string = &to_string_complex;
        complex_type_info->zero = &get_zero_complex;
        complex_type_info->one = &get_one_complex;
    };
    return complex_type_info;
};

