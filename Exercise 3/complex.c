/**
 * In this module will be declared all the complex number operations that are required in the exercise:
 * adding, subtracting, multiplying (with real, img, or another complex number) and abs.
 * Reading a complex number is declared here is as well because it is another command of the program.
 */

#include <stdio.h>
#include <math.h>
#include "complex.h"

/* reading values to a complex number */
void read_complex(complex *number, double real_value, double img_value)
{
    number->real = real_value;
    number->img = img_value;
}

/* adding the values of two complex numbers and printing the result to the screen */
void add_complex_numbers(complex *z, complex *w)
{
    complex temp;
    complex *p = &temp;
    temp.real = z->real + w->real;
    temp.img = z->img + w->img;
    print_complex(p);
}

/* subtracting the values of two complex numbers and printing the result to the screen */
void sub_complex_numbers(complex *z, complex *w)
{
    complex temp;
    complex *p = &temp;
    temp.real = z->real - w->real;
    temp.img = z->img - w->img;
    print_complex(p);
}

/* multiplying a complex number with a real number and printing the result to the screen */
void multiply_complex_real(complex *z, double real_number)
{
    complex temp;
    complex *p = &temp;
    temp.real = real_number * z->real;
    temp.img = real_number * z->img;
    print_complex(p);
}

/* multiplying a complex number with an imaginary number and printing the result to the screen */
void multiply_complex_img(complex *z, double img_number)
{
    complex temp;
    complex *p = &temp;
    temp.real = -1 * img_number * z->img;
    temp.img = img_number * z->real;
    print_complex(p);
}

/* multiplying a complex number with another complex number and printing the result to the screen */
void multiply_complexes(complex *z, complex *w)
{
    complex temp;
    complex *p = &temp;
    temp.real = (z->real * w->real) - (z->img * w->img);
    temp.img = (z->real * w->img) + (z->img * w->real);
    print_complex(p);
}

/* calculate the abs of a complex number and print the result to the screen (print a number) */
void abs_of_complex(complex *z)
{
    double abs;
    abs = sqrt((z->real * z->real) + (z->img * z->img));
    printf("The abs value is: %.2f\n", abs);
}