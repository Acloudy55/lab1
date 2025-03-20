#include <stdio.h>
#include "polynomial.h"
#include "test.h"
void test_polynomial_float()
{   
    float mas[] = {5.1f, 4.0f, 2.0f};
    float mas2[] = {4.3f, 5.0f, 21.4213f, 76.1f};
    polynomial *poly1 = new_polynomial(mas, get_float_type_info(), 3); 
    coef *argument = new_float(3.0f);
    printf("poly1 with arg 3.0 %s\n", to_string_coef(value_polynomial(poly1, argument)));
    polynomial *poly2 = new_polynomial(mas2, get_float_type_info(), 4); 
    polynomial *poly3 = copy_polynomial(poly2);
    printf("poly1: %s\n", to_string_polynomial(poly1));
    printf("poly2: %s\n", to_string_polynomial(poly2));
    printf("poly3: %s\n", to_string_polynomial(poly3));
    poly3 = add_polynomial(poly1, poly2);
    printf("poly1 + poly2: %s\n", to_string_polynomial(poly3));
    polynomial* poly4 = mul_polynomial(poly1, poly2);
    printf("poly1 * poly2: %s\n", to_string_polynomial(poly4));
    

    polynomial *poly5 = copy_polynomial(poly1);
    poly5 = pow_polynomial(poly5, 0);
    printf("poly1^3: %s\n", to_string_polynomial(poly5));
    poly1 = scalar_mul_polynomial(poly1, new_float(2.0f));
    printf("poly1 * 2: %s\n", to_string_polynomial(poly1));
    //
    //
    //
    
    

    float poly1_data[] = {5.0f, 3.0f, 5.0f};
    float poly2_data[] = {1.0f, 2.0f, 1.0f, 3.2f};
    polynomial *test_1 = new_polynomial(poly1_data, get_float_type_info(), 3);
    polynomial *test_2 = new_polynomial(poly2_data, get_float_type_info(), 4);
    printf("test1: %s\n", to_string_polynomial(test_1));
    printf("test2: %s\n", to_string_polynomial(test_2));
    polynomial *composed_polynomial = compose_polynomial(test_1, test_2);
    printf("composed polynomial: %s\n", to_string_polynomial(composed_polynomial));

    delete_polynomial(poly1);
    delete_polynomial(poly2);
    delete_polynomial(poly3);
    delete_polynomial(poly4);
    delete_polynomial(poly5);  
    delete_polynomial(composed_polynomial);
    delete_polynomial(test_1);
    delete_polynomial(test_2);
}
void test_polynomial_int()
{
    int mas[] = {5, 4, 2};
    int mas2[] = {4, 5, 21, 76};
    polynomial *poly1 = new_polynomial(mas, get_int_type_info(), 3); 
    polynomial *poly2 = new_polynomial(mas2, get_int_type_info(), 4);
    polynomial *poly3 = copy_polynomial(poly2);
    printf("poly1: %s\n", to_string_polynomial(poly1));
    printf("poly2: %s\n", to_string_polynomial(poly2));
    printf("poly3: %s\n", to_string_polynomial(poly3));
    poly3 = add_polynomial(poly1, poly2);
    printf("poly1 + poly2: %s\n", to_string_polynomial(poly3));
    polynomial* poly4 = mul_polynomial(poly1, poly2);
    printf("poly1 * poly2: %s\n", to_string_polynomial(poly4));
    

    polynomial *poly5 = copy_polynomial(poly1);
    poly5 = pow_polynomial(poly5, 2);
    printf("poly1^3: %s\n", to_string_polynomial(poly5));
    poly1 = scalar_mul_polynomial(poly1, new_int(2.0f));
    printf("poly1 * 2: %s\n", to_string_polynomial(poly1));
    //
    //
    //
    coef *argument = new_int(3);
    printf("argument value: %s\n", to_string_coef(value_polynomial(poly1, argument)));
    

    int poly1_data[] = {5, 3, 5};
    int poly2_data[] = {1, 2, 1};
    polynomial *test_1 = new_polynomial(poly1_data, get_int_type_info(), 3);
    polynomial *test_2 = new_polynomial(poly2_data, get_int_type_info(), 3);
    polynomial *composed_polynomial = compose_polynomial(test_1, test_2);
    printf("composed polynomial: %s\n", to_string_polynomial(composed_polynomial));
    delete_polynomial(poly1);
    delete_polynomial(poly2);
    delete_polynomial(poly3);
    delete_polynomial(poly4);
    delete_polynomial(poly5);  
    delete_polynomial(composed_polynomial);
    delete_polynomial(test_1);
    delete_polynomial(test_2);   
}

void test_polynomial_double()
{
    double mas[] = {5.56, 4.123, 2.432};
    double mas2[] = {4.84, 5.32, 21.874, 76.231};
    polynomial *poly1 = new_polynomial(mas, get_double_type_info(), 3); 
    polynomial *poly2 = new_polynomial(mas2, get_double_type_info(), 4);
    polynomial *poly3 = copy_polynomial(poly2);
    printf("poly1: %s\n", to_string_polynomial(poly1));
    printf("poly2: %s\n", to_string_polynomial(poly2));
    printf("poly3: %s\n", to_string_polynomial(poly3));
    poly3 = add_polynomial(poly1, poly2);
    printf("poly1 + poly2: %s\n", to_string_polynomial(poly3));
    polynomial* poly4 = mul_polynomial(poly1, poly2);
    printf("poly1 * poly2: %s\n", to_string_polynomial(poly4));
    

    polynomial *poly5 = copy_polynomial(poly1);
    poly5 = pow_polynomial(poly5, 2);
    printf("poly1^3: %s\n", to_string_polynomial(poly5));
    poly1 = scalar_mul_polynomial(poly1, new_double(2.0f));
    printf("poly1 * 2: %s\n", to_string_polynomial(poly1));
    //
    //
    //
    coef *argument = new_double(3.0);
    printf("value of argument is %s\n", to_string_coef(argument));
    printf("value of %s inside poly1 is %s\n", to_string_coef(argument), to_string_coef(value_polynomial(poly1, argument)));
    printf("value of argument is %s\n", to_string_coef(argument));

    double poly1_data[] = {5.312, 3.43, 5};
    double poly2_data[] = {1, 2.2, 1.11};
    polynomial *test_1 = new_polynomial(poly1_data, get_double_type_info(), 3);
    polynomial *test_2 = new_polynomial(poly2_data, get_double_type_info(), 3);
    polynomial *composed_polynomial = compose_polynomial(test_1, test_2);
    printf("composed polynomial: %s\n", to_string_polynomial(composed_polynomial));
    delete_polynomial(poly1);
    delete_polynomial(poly2);
    delete_polynomial(poly3);
    delete_polynomial(poly4);
    delete_polynomial(poly5);  
    delete_polynomial(composed_polynomial);
    delete_polynomial(test_1);
    delete_polynomial(test_2); 
}
void test_complex_coef()
{
    coef *c1 = new_complex_coef(3.f, 2.f);
    coef *c2 = new_complex_coef(1.f, -0.5f);
    printf("c1 = %s\n", to_string_coef(c1));
    printf("c2 = %s\n", to_string_coef(c2));
    coef *c_sum = sum_complex(c1, c2);
    printf("c1 + c2 = %s\n", to_string_coef(c_sum));
    coef *c_sub = sub_complex(c1, c2);
    printf("c1 - c2 = %s\n", to_string_coef(c_sub));
    coef *c_mul = mul_complex(c1, c2);
    printf("c1 * c2 = %s\n", to_string_coef(c_mul));
    coef *c_pow = pow_complex(c1, 3);
    printf("c1^3 = %s\n", to_string_coef(c_pow));
    c_pow = pow_complex(c1, 0);
    printf("c1^0 = %s\n", to_string_coef(c_pow));
    coef *c_one = get_one_complex();
    coef *c_zero = get_zero_complex();
    printf("One complex: %s\n", to_string_coef(c_one));
    printf("Zero complex: %s\n", to_string_coef(c_zero));

    delete_coef(c1);
    delete_coef(c2);
    delete_coef(c_sum);
    delete_coef(c_sub);
    delete_coef(c_mul);
    delete_coef(c_pow);
    delete_coef(c_one);
    delete_coef(c_zero);
}

void test_polynomial_complex_float()
{
    coef* polynomial_data_1[3];
    coef* polynomial_data_2[4];
    polynomial_data_1[0] = new_complex_coef(1.0, 2.0);  // 1 + 2i
    polynomial_data_1[1] = new_complex_coef(3.0f, -4.0f); // 3 - 4i
    polynomial_data_1[2] = new_complex_coef(-5.0f, 6.0f);
    polynomial_data_2[0] = new_complex_coef(1.0f, 5.0f);  // 1 + 5i
    polynomial_data_2[1] = new_complex_coef(2.0f, -3.0f); // 2 - 3i
    polynomial_data_2[2] = new_complex_coef(3.0f, 2.0f);  // 3 + 2i
    polynomial_data_2[3] = new_complex_coef(4.0f, 1.0f);  // 4 + 1i

    polynomial *poly1 = new_polynomial(polynomial_data_1, get_complex_type_info(), 3);
    coef *argument = new_complex_coef(3.0f, 2.1f);
    printf("3+2,1i * 1+2i = %s\n", to_string_coef(mul_coef(argument, polynomial_data_1[0])));
    printf("value of the poly1 with arg = (3.0f, 2.1f) %s\n", to_string_coef(value_polynomial(poly1, argument)));
    polynomial *poly2 = new_polynomial(polynomial_data_2, get_complex_type_info(), 4); 
    polynomial *poly3 = copy_polynomial(poly2);
    printf("poly1: %s\n", to_string_polynomial(poly1));
    printf("poly2: %s\n", to_string_polynomial(poly2));
    printf("poly3: %s\n", to_string_polynomial(poly3));
    poly3 = add_polynomial(poly1, poly2);
    printf("poly1 + poly2: %s\n", to_string_polynomial(poly3));
    polynomial* poly4 = mul_polynomial(poly1, poly2);
    printf("poly1 * poly2: %s\n", to_string_polynomial(poly4));
    

    polynomial *poly5 = copy_polynomial(poly1);
    poly5 = pow_polynomial(poly5, 2);
    printf("poly1^3: %s\n", to_string_polynomial(poly5));
    poly1 = scalar_mul_polynomial(poly1, new_complex_coef(2.0f, 0.0f));
    printf("poly1 * 2: %s\n", to_string_polynomial(poly1));
    //
    //
    //
    
    

    polynomial *composed_polynomial = compose_polynomial(poly1, poly2);
    printf("poly1: %s\n", to_string_polynomial(poly1));
    printf("poly2: %s\n", to_string_polynomial(poly2));
    printf("composed polynomial: %s\n", to_string_polynomial(composed_polynomial));
    delete_polynomial(poly1);
    delete_polynomial(poly2);
    delete_polynomial(poly3);
    delete_polynomial(poly4);
    delete_polynomial(poly5);  
    delete_polynomial(composed_polynomial);
    delete_coef(argument);
}
void test_polynomial_complex_int()
{
    //
    //  CREATION OF POLYNOM WITH INT COMPLEX COEFFICIENTS
    //
    coef* polynomial_data_1[3];
    coef* polynomial_data_2[4];
    int mas1[3] = {2, 0, 12};
    int mas2[3] = {63, 10, 4};

    int mas3[4] = {23, 32, 15, 32};
    int mas4[4] = {73, 23, 98, 76};
    int index = 0;
    for (; index < 3; index++) {
        
        int *temp1 = &mas1[index];
        int *temp2 = &mas2[index];
        polynomial_data_1[index] = _new_complex(new_coef(temp1, get_int_type_info()), new_coef(temp2, get_int_type_info()));
    }
    index = 0;
    for  (; index < 4; index++) {
        int *temp1 = &mas3[index];
        int *temp2 = &mas4[index];
        polynomial_data_2[index] = _new_complex(new_coef(temp1, get_int_type_info()), new_coef(temp2, get_int_type_info()));
        
    }
    
    polynomial *poly1 = new_polynomial(polynomial_data_1, get_complex_type_info(), 3);
    polynomial *poly2 = new_polynomial(polynomial_data_2, get_complex_type_info(), 4); 
    printf("poly1: %s\n", to_string_polynomial(poly1));
    printf("poly2: %s\n", to_string_polynomial(poly2));

    polynomial *poly3 = copy_polynomial(poly1);

    poly3 = add_polynomial(poly1, poly2);
    printf("poly1 + poly2: %s\n", to_string_polynomial(poly3));
    polynomial* poly4 = mul_polynomial(poly1, poly2);
    printf("poly1 * poly2: %s\n", to_string_polynomial(poly4));
    

    polynomial *poly5 = copy_polynomial(poly1);
    poly5 = pow_polynomial(poly5, 0);
    printf("poly1^3: %s\n", to_string_polynomial(poly5));
    printf("poly1: %s\n", to_string_polynomial(poly1));

    coef *argument = _new_complex(new_coef(&mas1[0], get_int_type_info()), new_coef(&mas1[1], get_int_type_info()));
    printf("arg is %s\n", to_string_coef(argument));

    poly1 = scalar_mul_polynomial(poly1, argument);

    printf("poly1 * 2: %s\n", to_string_polynomial(poly1));
    //
    //
    //
    
    printf("value of poly 1 with arg: %s\n", to_string_coef(value_polynomial(poly1, argument)));
    polynomial *composed_polynomial = compose_polynomial(poly1, poly2);
    printf("composed polynomial: %s\n", to_string_polynomial(composed_polynomial));
    delete_polynomial(poly1);
    delete_polynomial(poly2);
    delete_polynomial(poly3);
    delete_polynomial(poly4);
    delete_polynomial(poly5);  
    delete_polynomial(composed_polynomial);
    delete_coef(argument);

}
void test_to_string_coefs() {
    coef *a = new_float(5.f);
    coef *b = new_float(10.4532000f);
    printf("float a: %s\n", to_string_coef(a));
    printf("float b: %s\n", to_string_coef(b));
    coef *c = new_int(5);
    coef *d = new_int(10);
    printf("int c: %s\n", to_string_coef(c));
    printf("int d: %s\n", to_string_coef(d));
    coef *e = new_double(5.0);
    coef *f = new_double(15.87654300);
    printf("double e: %s\n", to_string_coef(e));
    printf("double f: %s\n", to_string_coef(f));

    coef *g = _new_complex(a, b);
    printf("complex_float g: %s\n", to_string_coef(g));
    coef *h = _new_complex(c, d);
    printf("complex_int h: %s\n", to_string_coef(h));
    coef *i = _new_complex(e, f);
    printf("complex_double i: %s\n", to_string_coef(i));
}



int main() {
    printf("-----------------------\n");
    test_to_string_coefs();
    // test_polynomial_float();
    // test_polynomial_complex_float();
    // test_polynomial_float();
    // test_complex_coef();
    // return launch_test_system();
    return 0;
}