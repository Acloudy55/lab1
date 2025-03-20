#include "polynomial.h"

static char *buff = NULL;

// вспомогательные локальные функции для взятия несуществующей единицы и нуля для комплексного числа по типу его реальной части
static coef *zero(const coef* arg)
{
    coef* result = NULL;
    if (arg->type == get_complex_type_info()) {
        const type_info *underlying_type = ((complex_data*)arg->data)->re->type;
        result = _new_complex(underlying_type->zero(), underlying_type->zero());
    }
    else 
    {
        result = arg->type->zero();
    }
    if (!result) 
    {
        log_error(ERR_MEMORY_ALLOCATION_FAILED);
        return NULL;
    }
    return result;

}
static coef *one(coef* arg){
    coef* result = NULL;
    if (arg->type == get_complex_type_info()) {
        const type_info *underlying_type = ((complex_data*)arg->data)->re->type;
        result = _new_complex(underlying_type->one(), underlying_type->zero());   
    }
    else 
    {
        result = arg->type->one();
    }
    if (!result) 
    {
        log_error(ERR_MEMORY_ALLOCATION_FAILED);
        return NULL;
    }
    return result;
}




// вспомогательная локальная функция для инициализации пустого полинома
static polynomial *data_alloc_polynomial(size_t size, const type_info *type)
{
    polynomial *poly = (polynomial*)malloc(sizeof(polynomial));
    if (!poly) {
        log_error(ERR_MEMORY_ALLOCATION_FAILED);
        return NULL;
    }
    poly->coefficients = (coef**)calloc(size, sizeof(coef *));
    if (!poly->coefficients) {
        log_error(ERR_MEMORY_ALLOCATION_FAILED);
        free(poly);
        return NULL;
    }
    poly->type = type;
    poly->length = size;
    return poly;
}

// Создание полинома для всех типов (коэффициенты копируются -> в delete удаляем)
polynomial *new_polynomial(void *mas, const type_info *type, size_t size)
{
    if (mas == NULL || size == 0) {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
    
    polynomial *poly = data_alloc_polynomial(size, type);
    if (!poly) {
        return NULL;
    }
    
    size_t deg;
    if (type == get_float_type_info()) {
        float *data = (float*) mas;
        for (deg = 0; deg < size; deg++) {
            poly->coefficients[deg] = new_float(data[deg]);
            if (!poly->coefficients[deg]) {
                log_error(ERR_MEMORY_ALLOCATION_FAILED);
                return NULL;
            }
        }
    }
    else if (type == get_int_type_info()) {
        int *data = (int*) mas;
        for (deg = 0; deg < size; deg++) {
            poly->coefficients[deg] = new_int(data[deg]);
            if (!poly->coefficients[deg]) {
                log_error(ERR_MEMORY_ALLOCATION_FAILED);
                return NULL;
            }
        }
    }
    else if (type == get_double_type_info()) {
        double *data = (double*) mas;
        for (deg = 0; deg < size; deg++) {
            poly->coefficients[deg] = new_double(data[deg]);
            if (!poly->coefficients[deg]) {
                log_error(ERR_MEMORY_ALLOCATION_FAILED);
                return NULL;
            }
        }
    }
    else if (type == get_complex_type_info()) {
        coef **data = (coef**) mas;
        for (deg = 0; deg < size; deg++) {
            poly->coefficients[deg] = copy_coef(data[deg]);
            if (!poly->coefficients[deg]) {
                log_error(ERR_MEMORY_ALLOCATION_FAILED);
                return NULL;
            }
        }
    }
    else {
        log_error(ERR_TYPE_MISMATCH);
        return NULL;
    }
    
    return poly;
}

// Удаление полинома и коэффициентов внутри него
void delete_polynomial(polynomial* poly)
{   
    if (poly == NULL) {
        log_error(ERR_NULL_POINTER);
        return;
    }
    for (size_t deg = 0; deg < poly->length; deg++) {
        delete_coef(poly->coefficients[deg]);
    }
    free(poly->coefficients);
    free(poly);
}


// Преобразование полинома в строку
char *to_string_polynomial(polynomial* poly)
{
    if (poly == NULL) {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
    // Буффер для хранения всего многочлена (на каждый одночлен выделяется 32 байта)
    size_t buffer_size = poly->length * 32; 
    if (buff == NULL) {
        buff = (char*) malloc(buffer_size);
    } else {
        buff = (char*) realloc(buff, buffer_size);
        buff[0] = '\0';
    }

    if (!buff) {
        log_error(ERR_MEMORY_ALLOCATION_FAILED);
        return NULL;
    }

    // Добавление одночленов в буфер
    for (size_t deg = 0; deg < poly->length; deg++) {
        char term[32];
        char coef_str[50];  // Буффер для коэффициентов
        
        if (poly->type == get_complex_type_info()) {
            snprintf(coef_str, sizeof(coef_str), "(%s)", poly->type->to_string(poly->coefficients[deg])); 
        }
        else {
            snprintf(coef_str, sizeof(coef_str), "%s", poly->type->to_string(poly->coefficients[deg]));
        }
        
        // Соединяем число с знаком
        if (deg > 0) {
            snprintf(term, sizeof(term), "%s%s%s", " + ", coef_str, "x^");
        } else {
            snprintf(term, sizeof(term), "%s", coef_str);
        }
        
        // Добавляем степень в конец строки
        if (deg > 0) {
            char degree_str[5];
            snprintf(degree_str, sizeof(degree_str), "%zu", deg);
            strncat(term, degree_str, sizeof(term) - strlen(term) - 1);
        }
    
        // Добаввляем одночлен в буфер
        strncat(buff, term, buffer_size - strlen(buff) - 1);
    }

    char* result = strdup(buff);
    free(buff);
    buff = NULL;
    return result;
}

polynomial *copy_polynomial(polynomial* src)
{
    if (src != NULL)
    {
        polynomial *copy = data_alloc_polynomial(src->length, src->type);

        for (size_t i = 0; i < src->length; i++)
        {
            copy->coefficients[i] = copy_coef(src->coefficients[i]);
        }

        return copy;
    }
    else
    {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
};



polynomial* add_polynomial(polynomial* left, polynomial* right)
{
    if (left==NULL || right==NULL)
    {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }

    if  (left->type != right->type)
    {
        log_error(ERR_TYPE_MISMATCH);
        return NULL;
    }
    //  size of new poly
    size_t size = fmax(left->length, right->length);

    polynomial *poly = data_alloc_polynomial(size, left->type);

    for (size_t deg = 0; deg < poly->length; deg++)
    {
        if (deg < left->length && deg < right->length)
        {
            poly->coefficients[deg] = sum_coef(left->coefficients[deg], right->coefficients[deg]);
        }
        else if (deg < left->length)
        {
            poly->coefficients[deg] = copy_coef(left->coefficients[deg]);
        }
        else if (deg < right->length) 
        {
            poly->coefficients[deg] = copy_coef(right->coefficients[deg]);
        };
    }
    return poly;
};

polynomial* sub_polynomial(polynomial* left, polynomial* right)
{
    if (left==NULL || right==NULL)
    {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }

    if  (left->type != right->type)
    {
        log_error(ERR_TYPE_MISMATCH);
        return NULL;
    }
    //  size of new poly
    size_t size = fmax(left->length, right->length);

    polynomial *poly = data_alloc_polynomial(size, left->type);

    for (size_t deg = 0; deg < size; deg++)
    {
        if (deg < left->length && deg < right->length)
        {
            poly->coefficients[deg] = sub_coef(left->coefficients[deg], right->coefficients[deg]);
        }
        else if (deg < left->length)
        {
            poly->coefficients[deg] = copy_coef(left->coefficients[deg]);
        }
        else if (deg < right->length) 
        {
            poly->coefficients[deg] = copy_coef(right->coefficients[deg]);
        };
    }
    return poly;
};

polynomial* mul_polynomial(polynomial* left, polynomial* right)
{
    if (left==NULL || right==NULL)
    {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
    if  (left->type != right->type)
    {
        log_error(ERR_TYPE_MISMATCH);
        return NULL;
    }
    size_t size = (left->length + right->length)-1;

    polynomial *poly = data_alloc_polynomial(size, left->type);

    for (size_t i = 0; i < size; i++) {
        poly->coefficients[i] = zero(left->coefficients[0]);
    }
    for (size_t deg_left = 0; deg_left < left->length; deg_left++)
    {
        for (size_t deg_right = 0; deg_right < right->length; deg_right++)
        {
            coef *value = mul_coef(left->coefficients[deg_left], right->coefficients[deg_right]);
            poly->coefficients[deg_left + deg_right] = sum_coef(poly->coefficients[deg_left+deg_right], value);
        }
    }

    return poly;
}; 
polynomial* pow_polynomial(polynomial* base, size_t exponential)
{
    if (exponential == 0)
    {
        polynomial *poly = data_alloc_polynomial(1, base->type);
        poly->coefficients[0] = one(base->coefficients[0]);
        return poly;
    }
    polynomial *result = copy_polynomial(base);
    while (exponential > 1)
    {
        if (exponential % 2 == 0)
        {
            polynomial *temp = mul_polynomial(result, result);
            delete_polynomial(result);
            result = temp;
            exponential /= 2;
        }
        else
        {
            polynomial *temp = mul_polynomial(result, base);
            delete_polynomial(result);
            result = temp;
            exponential--;
        }
    }
    return result;

};

polynomial* scalar_mul_polynomial(polynomial* poly, coef *scalar)
{
    if (poly == NULL || scalar == NULL)
    {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
    if (poly->coefficients == NULL || scalar->data == NULL){
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
    if (poly->type != scalar->type)
    {
        log_error(ERR_TYPE_MISMATCH);
        return NULL;
    }
    if (poly->type == get_complex_type_info())
    {
        if(((complex_data*)poly->coefficients[0]->data)->re->type != ((complex_data*)scalar->data)->re->type)
        {
            log_error(ERR_TYPE_MISMATCH);
            return NULL;
        }
    }
    polynomial* result = data_alloc_polynomial(poly->length, poly->type);
    for (size_t deg = 0; deg < poly->length; deg++)
    {
        result->coefficients[deg] = mul_coef(poly->coefficients[deg], scalar);
    }
    return result;
};

coef* value_polynomial(polynomial* poly, const coef* argument) {
    
    if (!poly || !argument || !poly->coefficients) {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }

    // Проверка совпадения типов
    if (poly->type != argument->type) {
        log_error(ERR_TYPE_MISMATCH);
        return NULL;
    }

    if (poly->type == get_complex_type_info())
    {
        if(((complex_data*)poly->coefficients[0]->data)->re->type != ((complex_data*)argument->data)->re->type)
        {
            log_error(ERR_TYPE_MISMATCH);
            return NULL;
        }
    }
    // Создаем нулевой коэффициент для результата
    coef* result = zero(argument);
    // Вычисляем значение полинома
    for (size_t deg = 0; deg < poly->length; deg++) {
        // Проверка коэффициента полинома
        if (!poly->coefficients[deg]) {
            log_error(ERR_NULL_POINTER);
            delete_coef(result);
            return NULL;
        }

        // Вычисляем argument^deg
        coef* powered_arg = power_coef(argument, deg);
        if (!powered_arg) {
            delete_coef(result);
            return NULL;
        }

        // Умножаем коэффициент на argument^deg
        coef* term = mul_coef(poly->coefficients[deg], powered_arg);
        delete_coef(powered_arg);

        if (!term) {
            delete_coef(result);
            return NULL;
        }

        coef* new_result = sum_coef(result, term);
        delete_coef(result); 
        delete_coef(term);

        if (!new_result) {
            return NULL;
        }

        result = new_result;
    }

    return result;
}

polynomial* compose_polynomial(polynomial* poly, polynomial* argument)
{
    
    if (poly == NULL || argument == NULL)
    {
        log_error(ERR_NULL_POINTER);
        return NULL;
    }
    if (poly->type != argument->type)
    {
        log_error(ERR_TYPE_MISMATCH);
        return NULL;
    }
    
    size_t size = poly->length + argument->length - 1;
    polynomial *result = data_alloc_polynomial(size, poly->type);

    for (size_t i = 0; i < size; i++)
    {
        result->coefficients[i] = zero(poly->coefficients[0]);
    }
    
    for (size_t deg = 0; deg < poly->length; deg++)
    {
        polynomial *term;
        result = add_polynomial(result, scalar_mul_polynomial(pow_polynomial(argument, deg), poly->coefficients[deg]));
    }
    return result;
};