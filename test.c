#include "test.h"

// Максимальное количество многочленов
#define MAX_POLYS 100

// Структура для хранения многочленов по имени
typedef struct {
    char *name;
    polynomial *poly;
} poly_entry;

poly_entry polynomials[MAX_POLYS];
int poly_count = 0;

// Инициализация массива
void init_polys() 
{
    for (int i = 0; i < MAX_POLYS; i++) {
        polynomials[i].name = NULL;
        polynomials[i].poly = NULL;
    }
}

// Добавление многочлена в массив
void add_poly(char *name, polynomial *poly) 
{
    if (poly_count >= MAX_POLYS) {
        fprintf(stderr, "Максимальное количество многочленов достигнуто\n");
        return;
    }
    polynomials[poly_count].name = strdup(name);
    polynomials[poly_count].poly = poly;
    poly_count++;
}

// Поиск многочлена по имени
polynomial *find_poly(char *name) 
{
    for (int i = 0; i < poly_count; i++) {
        if (strcmp(polynomials[i].name, name) == 0) {
            return polynomials[i].poly;
        }
    }
    return NULL;
}

// Удаление всех многочленов
void delete_all_polys() 
{
    for (int i = 0; i < poly_count; i++) {
        free(polynomials[i].name);
        delete_polynomial(polynomials[i].poly);
    }
    poly_count = 0;
}

// Парсинг типа
const type_info* parse_type(char *type_str) 
{
    if (strcmp(type_str, "INT") == 0) return get_int_type_info();
    if (strcmp(type_str, "FLOAT") == 0) return get_float_type_info();
    if (strcmp(type_str, "DOUBLE") == 0) return get_double_type_info();
    if (strcmp(type_str, "COMPLEX") == 0) return get_complex_type_info();
    log_error(ERR_TYPE_MISMATCH);
    fprintf(stderr, "Ошибка: неизвестный тип %s\n", type_str);
    return NULL;
}

// Вспомогательная функция для удаления символов из строки
char* remove_chars(const char *str, const char *chars_to_remove) 
{
    char *result = strdup(str);
    if (!result) {
        log_error(ERR_MEMORY_ALLOCATION_FAILED);
        return NULL;
    }
    size_t len = strlen(result);
    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (strchr(chars_to_remove, result[i]) == NULL) {
            result[j++] = result[i];
        }
    }
    result[j] = '\0';
    return result;
}

// Парсинг комплексных значений (предполагаем double для re и im)
coef** parse_complex_values(char *values_str, size_t *size) 
{
    char *clean_str = remove_chars(values_str, "()");
    if (!clean_str) {
        log_error(ERR_MEMORY_ALLOCATION_FAILED);
        return NULL;
    }

    char *token;
    size_t count = 0;
    char *str_copy = strdup(clean_str);
    if (!str_copy) {
        free(clean_str);
        log_error(ERR_MEMORY_ALLOCATION_FAILED);
        return NULL;
    }

    token = strtok(str_copy, ",");
    while (token) {
        count++;
        token = strtok(NULL, ",");
    }
    free(str_copy);

    if (count % 2 != 0) {
        log_error(ERR_INVALID_INPUT);
        fprintf(stderr, "Ошибка: некорректное количество компонент для комплексных чисел\n");
        free(clean_str);
        return NULL;
    }

    *size = count / 2;
    coef **mas = (coef**)malloc(*size * sizeof(coef*));
    if (!mas) {
        log_error(ERR_MEMORY_ALLOCATION_FAILED);
        free(clean_str);
        return NULL;
    }

    str_copy = strdup(clean_str);
    if (!str_copy) {
        free(clean_str);
        free(mas);
        log_error(ERR_MEMORY_ALLOCATION_FAILED);
        return NULL;
    }

    token = strtok(str_copy, ",");
    for (size_t i = 0; i < *size; i++) {
        double re = atof(token);
        token = strtok(NULL, ",");
        if (!token) {
            free(str_copy);
            free(clean_str);
            for (size_t j = 0; j < i; j++) delete_coef(mas[j]);
            free(mas);
            log_error(ERR_INVALID_INPUT);
            return NULL;
        }
        double im = atof(token);
        coef* re_coef = new_double(re);
        coef* im_coef = new_double(im);
        if (!re_coef || !im_coef) {
            delete_coef(re_coef);
            delete_coef(im_coef);
            free(str_copy);
            free(clean_str);
            for (size_t j = 0; j < i; j++) delete_coef(mas[j]);
            free(mas);
            log_error(ERR_MEMORY_ALLOCATION_FAILED);
            return NULL;
        }
        mas[i] = _new_complex(re_coef, im_coef); // Предполагаем, что new_complex доступен
        if (!mas[i]) {
            delete_coef(re_coef);
            delete_coef(im_coef);
            free(str_copy);
            free(clean_str);
            for (size_t j = 0; j < i; j++) delete_coef(mas[j]);
            free(mas);
            log_error(ERR_MEMORY_ALLOCATION_FAILED);
            return NULL;
        }
        token = strtok(NULL, ",");
    }

    free(str_copy);
    free(clean_str);
    return mas;
}

// Парсинг значений для всех типов
void* parse_values(char *values_str, const type_info *type, size_t *size) 
{
    if (type == get_complex_type_info()) {
        return (void*)parse_complex_values(values_str, size);
    }

    char *token;
    size_t count = 0;
    char *values_copy = strdup(values_str);
    if (!values_copy) {
        log_error(ERR_MEMORY_ALLOCATION_FAILED);
        return NULL;
    }

    token = strtok(values_copy, ",");
    while (token) {
        count++;
        token = strtok(NULL, ",");
    }
    free(values_copy);
    *size = count;

    if (type == get_int_type_info()) {
        int *mas = (int*)malloc(count * sizeof(int));
        if (!mas) {
            log_error(ERR_MEMORY_ALLOCATION_FAILED);
            return NULL;
        }
        values_copy = strdup(values_str);
        if (!values_copy) {
            free(mas);
            log_error(ERR_MEMORY_ALLOCATION_FAILED);
            return NULL;
        }
        token = strtok(values_copy, ",");
        for (size_t i = 0; i < count; i++) {
            mas[i] = atoi(token);
            token = strtok(NULL, ",");
        }
        free(values_copy);
        return mas;
    } else if (type == get_float_type_info()) {
        float *mas = (float*)malloc(count * sizeof(float));
        if (!mas) {
            log_error(ERR_MEMORY_ALLOCATION_FAILED);
            return NULL;
        }
        values_copy = strdup(values_str);
        if (!values_copy) {
            free(mas);
            log_error(ERR_MEMORY_ALLOCATION_FAILED);
            return NULL;
        }
        token = strtok(values_copy, ",");
        for (size_t i = 0; i < count; i++) {
            mas[i] = (float)atof(token);
            token = strtok(NULL, ",");
        }
        free(values_copy);
        return mas;
    } else if (type == get_double_type_info()) {
        double *mas = (double*)malloc(count * sizeof(double));
        if (!mas) {
            log_error(ERR_MEMORY_ALLOCATION_FAILED);
            return NULL;
        }
        values_copy = strdup(values_str);
        if (!values_copy) {
            free(mas);
            log_error(ERR_MEMORY_ALLOCATION_FAILED);
            return NULL;
        }
        token = strtok(values_copy, ",");
        for (size_t i = 0; i < count; i++) {
            mas[i] = atof(token);
            token = strtok(NULL, ",");
        }
        free(values_copy);
        return mas;
    }

    log_error(ERR_TYPE_MISMATCH);
    fprintf(stderr, "Ошибка: неподдерживаемый тип для значений\n");
    return NULL;
}

// Парсинг скаляра
coef* parse_scalar(char *scalar_str, const type_info *type) 
{
    if (type == get_int_type_info()) {
        return new_int(atoi(scalar_str));
    } else if (type == get_float_type_info()) {
        return new_float(atof(scalar_str));
    } else if (type == get_double_type_info()) {
        return new_double(atof(scalar_str));
    } else if (type == get_complex_type_info()) {
        char *clean_str = remove_chars(scalar_str, "()");
        if (!clean_str) {
            log_error(ERR_MEMORY_ALLOCATION_FAILED);
            return NULL;
        }
        char *re_str = strtok(clean_str, ",");
        char *im_str = strtok(NULL, ",");
        if (re_str && im_str && !strtok(NULL, ",")) {
            double re = atof(re_str);
            double im = atof(im_str);
            coef* re_coef = new_double(re);
            coef* im_coef = new_double(im);
            if (!re_coef || !im_coef) {
                delete_coef(re_coef);
                delete_coef(im_coef);
                free(clean_str);
                log_error(ERR_MEMORY_ALLOCATION_FAILED);
                return NULL;
            }
            coef* result = _new_complex(re_coef, im_coef);
            free(clean_str);
            if (!result) {
                delete_coef(re_coef);
                delete_coef(im_coef);
                log_error(ERR_MEMORY_ALLOCATION_FAILED);
            }
            return result;
        }
        free(clean_str);
        log_error(ERR_INVALID_INPUT);
        fprintf(stderr, "Ошибка: некорректный формат комплексного скаляра\n");
        return NULL;
    }
    log_error(ERR_TYPE_MISMATCH);
    fprintf(stderr, "Ошибка: неподдерживаемый тип для скаляра\n");
    return NULL;
}

// Обработка команд
void process_command(char *line) 
{
    char *line_copy = strdup(line);
    if (!line_copy) {
        fprintf(stderr, "Ошибка: не удалось выделить память\n");
        return;
    }

    int token_count = 0;
    char *token = strtok(line_copy, " ");
    while (token) {
        token_count++;
        token = strtok(NULL, " ");
    }
    free(line_copy);

    token = strtok(line, " ");
    if (!token) return;

    if (strcmp(token, "CREATE_POLY") == 0) {
        if (token_count < 4) {
            fprintf(stderr, "Ошибка: недостаточно аргументов для CREATE_POLY\n");
            return;
        }
        char *name = strtok(NULL, " ");
        if (!name) {
            fprintf(stderr, "Ошибка: имя полинома не указано\n");
            return;
        }
        if (find_poly(name) != NULL) {
            fprintf(stderr, "Полином с именем %s уже существует\n", name);
            return;
        }
        char *type_str = strtok(NULL, " ");
        const type_info *type = parse_type(type_str);
        if (!type) return;
        char *values_str = strtok(NULL, "\n");
        if (!values_str) {
            fprintf(stderr, "Ошибка: значения не указаны\n");
            return;
        }
        size_t size;
        void *mas = parse_values(values_str, type, &size);
        if (!mas) return;
        polynomial *poly = new_polynomial(mas, type, size);
        if (poly) {
            add_poly(name, poly);
            char *poly_str = to_string_polynomial(poly);
            if (poly_str) {
                printf("Created %s: %s\n", name, poly_str);
                free(poly_str);
            } else {
                fprintf(stderr, "Ошибка: не удалось преобразовать полином в строку\n");
            }
        } else {
            fprintf(stderr, "Ошибка: не удалось создать полином %s\n", name);
        }
        free(mas);
    } else if (strcmp(token, "ADD_POLY") == 0) {
        if (token_count != 3) {
            fprintf(stderr, "Ошибка: неверное количество аргументов для ADD_POLY\n");
            return;
        }
        char *name1 = strtok(NULL, " ");
        char *name2 = strtok(NULL, " ");
        if (!name1 || !name2) {
            fprintf(stderr, "Ошибка: не указаны имена полиномов\n");
            return;
        }
        polynomial *p1 = find_poly(name1);
        polynomial *p2 = find_poly(name2);
        if (p1 && p2) {
            polynomial *result = add_polynomial(p1, p2);
            if (result) {
                char *result_str = to_string_polynomial(result);
                if (result_str) {
                    printf("ADD %s + %s = %s\n", name1, name2, result_str);
                    free(result_str);
                }
                delete_polynomial(result);
            } else {
                fprintf(stderr, "Ошибка при сложении полиномов %s и %s\n", name1, name2);
            }
        } else {
            log_error(ERR_NULL_POINTER);
            fprintf(stderr, "Ошибка: полином %s не найден\n", p1 ? name2 : name1);
        }
    } else if (strcmp(token, "SUB_POLY") == 0) {
        if (token_count != 3) {
            fprintf(stderr, "Ошибка: неверное количество аргументов для SUB_POLY\n");
            return;
        }
        char *name1 = strtok(NULL, " ");
        char *name2 = strtok(NULL, " ");
        if (!name1 || !name2) {
            fprintf(stderr, "Ошибка: не указаны имена полиномов\n");
            return;
        }
        polynomial *p1 = find_poly(name1);
        polynomial *p2 = find_poly(name2);
        if (p1 && p2) {
            polynomial *result = sub_polynomial(p1, p2);
            if (result) {
                char *result_str = to_string_polynomial(result);
                if (result_str) {
                    printf("SUB %s - %s = %s\n", name1, name2, result_str);
                    free(result_str);
                }
                delete_polynomial(result);
            } else {
                fprintf(stderr, "Ошибка при вычитании полиномов %s и %s\n", name1, name2);
            }
        } else {
            log_error(ERR_NULL_POINTER);
            fprintf(stderr, "Ошибка: полином %s не найден\n", p1 ? name2 : name1);
        }
    } else if (strcmp(token, "MUL_POLY") == 0) {
        if (token_count != 3) {
            fprintf(stderr, "Ошибка: неверное количество аргументов для MUL_POLY\n");
            return;
        }
        char *name1 = strtok(NULL, " ");
        char *name2 = strtok(NULL, " ");
        if (!name1 || !name2) {
            fprintf(stderr, "Ошибка: не указаны имена полиномов\n");
            return;
        }
        polynomial *p1 = find_poly(name1);
        polynomial *p2 = find_poly(name2);
        if (p1 && p2) {
            polynomial *result = mul_polynomial(p1, p2);
            if (result) {
                char *result_str = to_string_polynomial(result);
                if (result_str) {
                    printf("MUL %s * %s = %s\n", name1, name2, result_str);
                    free(result_str);
                }
                delete_polynomial(result);
            } else {
                fprintf(stderr, "Ошибка при умножении полиномов %s и %s\n", name1, name2);
            }
        } else {
            log_error(ERR_NULL_POINTER);
            fprintf(stderr, "Ошибка: полином %s не найден\n", p1 ? name2 : name1);
        }
    } else if (strcmp(token, "POW_POLY") == 0) {
        if (token_count != 3) {
            fprintf(stderr, "Ошибка: неверное количество аргументов для POW_POLY\n");
            return;
        }
        char *name = strtok(NULL, " ");
        char *exp_str = strtok(NULL, " ");
        if (!name || !exp_str) {
            fprintf(stderr, "Ошибка: не указаны имя полинома или степень\n");
            return;
        }
        size_t exp = atoi(exp_str);
        polynomial *p = find_poly(name);
        if (p) {
            polynomial *result = pow_polynomial(p, exp);
            if (result) {
                char *result_str = to_string_polynomial(result);
                if (result_str) {
                    printf("POW %s^%zu = %s\n", name, exp, result_str);
                    free(result_str);
                }
                delete_polynomial(result);
            } else {
                fprintf(stderr, "Ошибка при возведении полинома %s в степень %zu\n", name, exp);
            }
        } else {
            log_error(ERR_NULL_POINTER);
            fprintf(stderr, "Ошибка: полином %s не найден\n", name);
        }
    } else if (strcmp(token, "SCAL_MUL_POLY") == 0) {
        if (token_count != 3) {
            fprintf(stderr, "Ошибка: неверное количество аргументов для SCAL_MUL_POLY\n");
            return;
        }
        char *name = strtok(NULL, " ");
        char *scalar_str = strtok(NULL, " ");
        if (!name || !scalar_str) {
            fprintf(stderr, "Ошибка: не указаны имя полинома или скаляр\n");
            return;
        }
        polynomial *p = find_poly(name);
        if (p) {
            coef *scalar = parse_scalar(scalar_str, p->type);
            if (scalar) {
                polynomial *result = scalar_mul_polynomial(p, scalar);
                if (result) {
                    char *scalar_str_out = to_string_coef(scalar);
                    char *result_str = to_string_polynomial(result);
                    if (scalar_str_out && result_str) {
                        printf("SCAL_MUL %s * (%s) = %s\n", name, scalar_str_out, result_str);
                        free(scalar_str_out);
                        free(result_str);
                    }
                    delete_polynomial(result);
                } else {
                    fprintf(stderr, "Ошибка при скалярном умножении полинома %s\n", name);
                }
                delete_coef(scalar);
            } else {
                fprintf(stderr, "Ошибка при парсинге скаляра для полинома %s\n", name);
            }
        } else {
            log_error(ERR_NULL_POINTER);
            fprintf(stderr, "Ошибка: полином %s не найден\n", name);
        }
    } else if (strcmp(token, "COMPOSE") == 0) {
        if (token_count != 3) {
            fprintf(stderr, "Ошибка: неверное количество аргументов для COMPOSE\n");
            return;
        }
        char *out_name = strtok(NULL, " ");
        char *in_name = strtok(NULL, " ");
        if (!out_name || !in_name) {
            fprintf(stderr, "Ошибка: не указаны имена полиномов\n");
            return;
        }
        polynomial *out_poly = find_poly(out_name);
        polynomial *in_poly = find_poly(in_name);
        if (out_poly && in_poly) {
            polynomial *result = compose_polynomial(out_poly, in_poly);
            if (result) {
                char *result_str = to_string_polynomial(result);
                if (result_str) {
                    printf("COMPOSE %s(%s) = %s\n", out_name, in_name, result_str);
                    free(result_str);
                }
                delete_polynomial(result);
            } else {
                fprintf(stderr, "Ошибка при композиции полиномов %s и %s\n", out_name, in_name);
            }
        } else {
            log_error(ERR_NULL_POINTER);
            fprintf(stderr, "Ошибка: полином %s не найден\n", out_poly ? in_name : out_name);
        }
    } else if (strcmp(token, "VALUE") == 0) {
        if (token_count != 3) {
            fprintf(stderr, "Ошибка: неверное количество аргументов для VALUE\n");
            return;
        }
        char *name = strtok(NULL, " ");
        char *arg_str = strtok(NULL, " ");
        if (!name || !arg_str) {
            fprintf(stderr, "Ошибка: не указаны имя полинома или аргумент\n");
            return;
        }
        polynomial *p = find_poly(name);
        if (p) {
            coef *arg = parse_scalar(arg_str, p->type);
            if (arg) {
                coef *val = value_polynomial(p, arg);
                if (val) {
                    char *arg_str_out = to_string_coef(arg);
                    char *val_str = to_string_coef(val);
                    if (arg_str_out && val_str) {
                        printf("VALUE %s(%s) = %s\n", name, arg_str_out, val_str);
                        free(arg_str_out);
                        free(val_str);
                    }
                    delete_coef(val);
                } else {
                    fprintf(stderr, "Ошибка при вычислении значения полинома %s\n", name);
                }
                delete_coef(arg);
            } else {
                fprintf(stderr, "Ошибка при парсинге аргумента для полинома %s\n", name);
            }
        } else {
            log_error(ERR_NULL_POINTER);
            fprintf(stderr, "Ошибка: полином %s не найден\n", name);
        }
    } else {
        fprintf(stderr, "Ошибка: неизвестная команда %s\n", token);
    }
}

int launch_test_system() 
{
    init_polys();

    FILE *file = fopen("input.txt", "r");
    if (!file) {
        fprintf(stderr, "Cannot open input.txt\n");
        return 1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; // Удаляем символ новой строки
        process_command(line);
    }

    fclose(file);
    delete_all_polys();
    return 0;
}