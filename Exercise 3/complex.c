#include <stdio.h>
#include <math.h>
#include "complex.h"

void add_complex_numbers(complex *z, complex *w)
{
    complex temp;
    complex *p = &temp;
    temp.real = z->real + w->real;
    temp.img = z->img + w->img;
    print_complex(p);
}

void sub_complex_numbers(complex *z, complex *w)
{
    complex temp;
    complex *p = &temp;
    temp.real = z->real - w->real;
    temp.img = z->img - w->img;
    print_complex(p);
}

void multiply_complex_real(complex *z, double real_number)
{
    complex temp;
    complex *p = &temp;
    temp.real = real_number * z->real;
    temp.img = real_number * z->img;
    print_complex(p);
}

void multiply_complex_img(complex *z, double img_number)
{
    complex temp;
    complex *p = &temp;
    temp.real = -1 * img_number * z->img;
    temp.img = img_number * z->real;
    print_complex(p);
}

void multiply_complexes(complex *z, complex *w)
{
    complex temp;
    complex *p = &temp;
    temp.real = (z->real * w->real) - (z->img * w->img);
    temp.img = (z->real * w->img) + (z->img * w->real);
    print_complex(p);
}

void abs_of_complex(complex *z)
{
    double abs;
    abs = sqrt((z->real * z->real) + (z->img * z->img));
    printf("The abs value is: %.2f\n", abs);
}