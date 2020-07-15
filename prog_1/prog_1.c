#include <stdio.h>

/* 
Function name: main
Algorithm: accept the integer values, add them to a double sum,
	then display results
precondition: none
Postcondition: return 0 on success
Exceptions: none
Note: Demonstarate input, outputand simple math
*/
int main()
   {
    // initialize function/variables
    int augend, addend;
    double sum;
    // display title
       // function: printf
    printf("\nAdditionm Program\n");
    printf("==================\n");
    // get input from user

       //get augend
           // function: printf, scanf
       printf("\nEnter augend: ");
       scanf("%d", &augend);
       //get addend
          // function: printf, scanf
       printf("\nEnter addend: ");
       scanf("%d", &addend);
    // add values
    sum = augend + addend;
    // display result to the user
        // function: printf
    printf("\nThe sum of %d and %d is %4.2f\n\n", addend, augend, sum);
    // shut down

       // return success
    return 0;
   }

