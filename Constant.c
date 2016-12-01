

/*****************************************************************************/

/*Author: Daniel Gonzalez P#4926400 */
/*Assignment 2: Calculate Euler and Pi*/

/* program will calculate and prompt mathematical 
*  constant Euler and Pi with 10 and 6 significant digit accuracy 
*  compilation: gcc Constant.c -lm -o myprogram.out */

/* execute with ./myprogram.out */
/* To exit press [ctrl + Z] */

/*****************************************************************************/
/*
   I Daniel Gonzalez #4926400 hereby certify that this collective work is 
   my own and none of it is the work of any other person or entity. 
*/
/*****************************************************************************/


#include <stdio.h>
#include <math.h> 
/**
* Using from math.h:
*      double M_E(euler constant)for comparison purpose only
*      double M_PI(Pi constant) for comparison purpose only
*      double pow(double x, double y) used to calculate epsilon value
*/
#include <time.h> 
/**
 * Using from time.h:
 *     clock_t type for execution time calculation
 *     clock_t clock(void) for execution time calculation
 *     CLOCKS_PER_SEC constant to get the time in seconds
 *     
 */


/*****************************************************************************/


#define NOERROR 0                    /*For clean return  */
#define BASE10 10                    /*Used to calculate the digit accuracy*/
#define TERM_OF_ACURACY_E 10         /*Specified accuracy for euler*/
#define TERM_OF_ACURACY_PI 6         /*Specified accuracy for Pi*/
#define CONSTANT_NAME_E "e"          /*Name to use for constant e*/
#define CONSTANT_NAME_PI "Pi"        /*Name to use for constant Pi*/
#define MILLI_SEC_CONVERTION 1000.0  /*Value used for milliseconds conversion*/
#define OUTPUT_LINE_WIDTH 70         /*Output table line width*/
#define ACURACY_ARROW "\xef\xbf\xaa" /*Arrow to point at accuracy digit*/


/*****************************************************************************/
/*
 Function prototypes: 
 Function declarations are listed as below.
*/
 void calculateE(int);
 void calculatePi(int);
 void displayValues(double, double, char *, int, int, double);

/*****************************************************************************/


/* Main Process*/
 int main()
 {
  calculateE(TERM_OF_ACURACY_E);
  calculatePi(TERM_OF_ACURACY_PI);

  return NOERROR;
}


/*****************************************************************************/


/**
 *  This function calculates and prints a comparison of the 
 *  mathematical constant Euler with the specified accuracy.
 *  Formula used in the loop:
 *  e = ∑   1/n!  from n = 1( counter = 0 ) until Euler reaches 
 *  the specified accuracy
 * 
 * @param accuracy [the expected significant digit accuracy]
 */
 void calculateE(int accuracy){

  /* Declare and initialize variables  */   
  double epsilon= 0.0;
  long n = 1;
  int counter = 0;
  double term = 0.0;
  double over_sum = 0.0;
  double euler = 0.0;
  double execution_time = 0.0;
  clock_t start;
  clock_t end;


  /* for accuracy = 10, epsilon = 10^(-10 + 1) = 0.0000000001*/
  epsilon = pow(BASE10, -accuracy);
  start = clock();

  do{    
    euler = over_sum;
    n *= ((counter < 1)? 1 : counter) ;    
    term = 1.0/n;        
    over_sum += term;
    counter++;          

  }while (term > epsilon);

  counter--;    
  end = clock();

  execution_time = MILLI_SEC_CONVERTION 
  * (double)(end - start)
  / CLOCKS_PER_SEC;

  displayValues(  
    euler, 
    M_E,
    CONSTANT_NAME_E,
    accuracy, 
    counter, 
    execution_time );

}


/*****************************************************************************/


/**
 *  This function calculates and prints a comparison of the 
 *  mathematical constant Pi with the specified accuracy.
 *  Formula used in the loop:
 *  π = 4 * ∑   (-1)^n/ (2n + 1) from n = 0 until Pi reaches the specified 
 *  accuracy
 * 
 * @param accuracy [the expected significant digit accuracy]
 */
 void calculatePi(int accuracy){

  /* Declare and initialize variables  */  
  double epsilon= 0.0;
  long n = 0;
  double quater_pi = 0.0;
  double term = 0.0;    
  double pi = 1.0;
  double previous_pi = 0.0;
  double epsilon_term = 0.0;
  double execution_time = 0.0;
  clock_t start;
  clock_t end;


  /*for accuracy = 6, epsilon = 10^(-6) = 0.000001*/
  epsilon = pow(BASE10, -accuracy);
  start = clock();

  do{        
    previous_pi = pi;
    term = pow(-1,n)/(2 * n + 1);
    quater_pi += term;
    pi = 4 * quater_pi;
    epsilon_term = pi - previous_pi;        
    n++;
  }while (epsilon_term > epsilon || epsilon_term < -epsilon);    

  n--;
  pi = 4 * (quater_pi - term);
  end = clock();

  execution_time = MILLI_SEC_CONVERTION 
  * (double)(end - start)
  / CLOCKS_PER_SEC;

  displayValues(  pi,
    M_PI,
    CONSTANT_NAME_PI, 
    accuracy, 
    n, 
    execution_time 
    );

}


/**
 * [displays a comparison of values, the accuracy 
 *  of the calculation and the cycles it took to calculate.]  
 * @param calculated_value [calculated value to compare with constant]
 * @param comparison_const [constant used to compared calculated value]
 * @param constant_name    [name of constant calculated]
 * @param accuracy         [accuracy the calculated value most have]
 * @param terms            [terms it took to calculate value]
 * @param execution_time   [time spent in calculation]
 */
 void displayValues(
   double calculated_value, 
   double comparison_const,
   char * constant_name,
   int accuracy, 
   int terms,
   double execution_time){

  printf(
   "\n\n\n+%s+\n|%70s|\n",
   "-----------------------------------"
   "-----------------------------------",
   ""
   );
  printf(
   "|\t%s %s:  \t%.25f%12s|\n|\t%s:\t%.25f%12s|\n",
   "Calculated ",
   constant_name,
   calculated_value,
   "",
   "Library constant", 
   comparison_const,
   ""
   );
  printf(
   "|%35s%*s|%*s|\n",
   "",
   accuracy,
   ACURACY_ARROW,
   (OUTPUT_LINE_WIDTH - 34 - accuracy),
   ""
   );
  printf(
   "+%s+\n",
   "-----------------------------------"
   "-----------------------------------"
   );
  printf(
   " %s %d %s %d\n",
   "Terms to calculate with a digit accuracy of",
   accuracy,
   "is",
   terms         
   );
  printf(
   " %s %32.15f%s\n",
   "Execution time: ",
   execution_time,
   "ms"                        
   ); 
}




