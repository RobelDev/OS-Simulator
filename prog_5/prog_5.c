//header files
#include <stdio.h>
#include "StringUtils.h"
/*
function name: main
Algorithm: driver function to test getStringLength function
precondition: none
postcondition: return s zero(0) on success
Exception: none
Note: demonstrates development and use of string length function

*/

int main()
    {
      // initialize function/variables
	 // create test string
	char testStr[] = "Every good Boy Does Fine";
	 // declare other variables
	int strLen;
     // display title
       // function: printf
	printf("\nString Length Test Program\n");
	printf("============================\n");
     // conduct string length test
	// function: getStringLength
	strLen = getStringLength( testStr );
	
     // display result to user
	//function: printf
	printf("The length of the string \'%s\' is %d\n\n", testStr, strLen);
  
     // shutdown program

         //return program success
	return 0;



    }

