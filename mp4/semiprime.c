#include <stdlib.h>
#include <stdio.h>
//aryans5
//Aryan Shah
//9/28/2022
// Lab Partners: devdp2, loganeh2

/*Error 1: the test case in is_prime didn't account for
0 or negative values.

Error 2: the return inside the the nested if inside the for loop in is_prime
is incorrect, it should return 0 instead of 1, and the last return should be 1
instead of 0

Error 3: the print semiprimes called k=i%j, when it should've called i/j
according to the algorithm. k=i%j is redundant. In addition it needed a break
and another loop to handle the return for the main.c funtion.

These errors were in addition, to the return errors present in main.c, that were
given in the instructions for the mp4.
*/

/*
 * is_prime: determines whether the provided number is prime or not
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
    int i;
    if (number < 2) {return 0;}
    for (i = 2; i < number; i++) { //for each number smaller than it
        if (number % i == 0) { //check if the remainder is 0
            return 0; // return 0 instead of 1, because its not prime
        }
    }
    return 1; // made it through all test cases so it's prime
}


/*
 * print_semiprimes: prints all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
    int i, j, k;
    int ret = 0;
    for (i = a; i <=b; i++) { //for each item in interval
        //check if semiprime
        for (j = 2; j < i-1; j++) { // k=i/j, so j has to be < i
            if (i%j == 0) {
                if (is_prime(j)) {
                    k = i/j; //instead of mod, divide i and j
                    if (is_prime(k)) {
                        printf("%d ", i);

                        break; // semiprime found, leave loop
                    }
                }
            }
        }

    }
    for (i = a; i <=b; i++) { //for each item in interval
        //check if semiprime
        for (j = 2; j < i; j++) { // k=i/j, so j has to be < i
            if (i%j == 0) {
                if (is_prime(j)) {
                    k = i/j; //instead of mod, divide i and j
                    if (is_prime(k)) {
                        return 1; // to tell main.c, return is 1
                    }
                }
            }
        }

    }
    printf("\n");
    return ret;

}