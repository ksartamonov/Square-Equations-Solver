#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

const int infRoots = -1;
const double Accuracy = 1e-6;

int SquareEquationSolution (double a, double b, double c, double* ptr_x1, double* ptr_x2);
void SolvingCheckingFunc();
int IsZero(double x);
//------------------------------------------------------------------------------
int main()
{
  SolvingCheckingFunc ();

  printf ("Решение квадратного уравнения.\n");
  printf ("Введите коэфициенты квадратного уравнения a, b, c:\n");

  double coeff[3] = {0} ;
  for ( int nCoeff = 0 ; nCoeff < 3 ; nCoeff++ )
  {
    while ( scanf( "%lg", &coeff[nCoeff] ) != 1)
    {
      printf ("Ошибка! Все числа должны быть вещественными! Заново введите неверный коэффициент.\n");
      while (getchar() != '\n') {}
    }
  }
  double x1 = 0, x2 = 0;
  int RootsAmount = SquareEquationSolution (coeff[0], coeff[1], coeff[2], &x1, &x2);

  switch (RootsAmount)
  {
    case 0:         printf ("Решений нет\n");
                    break;

    case 1:         printf ("x = %lg\n", x1);
                    break;

    case 2:         printf ("x1 = %lg, x2 = %lg\n", x1, x2);
                    break;

    case infRoots:  printf ("Любое число\n");
                    break;

    default:        printf ("main(): Ошибка: количество корней = %d\n" , RootsAmount);
                    return 1;
  }

  return 0 ;
}

//------------------------------------------------------------------------------
//! Program solves a square equation ax^2 + bx +c = 0
//!
//! @param [in]   a  - coefficient
//! @param [in]   b  - coefficient
//! @param [in]   c  - coefficient
//! @param [out]  ptr_x1 - Pointer to the first root
//! @param [out]  ptr_x2 - Pointer to the second root
//!
//! @return Number of roots
//!
//! @note   In case of infinite number of roots, return infRoots
//------------------------------------------------------------------------------

int SquareEquationSolution (double a, double b, double c, double* ptr_x1, double* ptr_x2)
{

  assert (isfinite (a));
  assert (isfinite (b));
  assert (isfinite (c));

  assert (ptr_x1 != NULL);
  assert (ptr_x2 != NULL);
  assert (ptr_x1 != ptr_x2);

  if ( IsZero(a) )
  {
        if ( IsZero(b) )
        {
            if (  IsZero(c) )
              return infRoots;
            else          //  Если (с != 0 )
              return 0;
        }
        else { // Если ( b != 0 )
                *ptr_x1 = ( -c ) / b;
                return 1;
              }
  }
  else // Если ( a != 0 )
  {

    double Discriminant  = b * b - 4 * a * c;

    if ( Discriminant < 0 )
        return 0;

    if (  IsZero(Discriminant) )
    {
        *ptr_x1 = *ptr_x2 = (-b) / ( 2 * a );
        return 1;
    }

    if (Discriminant > 0 )
    {
        *ptr_x1 = ( -b + sqrt(Discriminant)) / ( 2 * a );
        *ptr_x2 = ( -b - sqrt(Discriminant)) / ( 2 * a );
        return 2;
    }

  }

}

//------------------------------------------------------------------------------
void SolvingCheckingFunc ( )
{
  printf("Запуск юнит-тестов: \n");
  double a_coef[3] = { 0, 1, 1e-5 };
  double b_coef[3] = { 0, 2, 9, };
  double c_coef[3] = { 0, 3, 2024999.9725 };
  int test_roots_amount[3] = {infRoots , 0, 2 };
  double test_x1 = 0 , test_x2 = 0 ;
  for (int i = 0 ; i < 3 ; i++ )
  {
    if ( SquareEquationSolution(a_coef[i] , b_coef[i], c_coef[i], &test_x1, &test_x2) == test_roots_amount[i])
          printf (" Тест № %d пройден (Входные данные: %f %f %f)\n", i+1, a_coef[i] , b_coef[i] , c_coef[i] ) ;

    else
     printf (" Тест № %d  НЕ пройден (Входные данные: %f %f %f)\n", i+1, a_coef[i] , b_coef[i] , c_coef[i] ) ;
  }
}
//------------------------------------------------------------------------------
int IsZero( double x)
{
  if (fabs(x) < Accuracy)
    return 1;

    return 0;
}
