#include <stdio.h>

/* 
Function name: addValues
Algorithm: accept the integer values ass parameters,
	returns a double sum
precondition: two values are integers
Postcondition: return souble sum as specified
Exceptions: none
Note: Demonstarate creation of supporting function
*/
double addValues( int oneVal, int anotherVal)
   {
    
     return (double) (oneVal + anotherVal);
   }
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
    double sum = 0;
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
        //addvalues
        sum = addValues( augend, addend);
    // display result to the user
        // function: printf
    printf("\nThe sum of %d and %d is %4.2f\n\n", addend, augend, sum);
    // shut down

       // return success
    return 0;
   }

