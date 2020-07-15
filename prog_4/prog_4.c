//header files
#include <stdio.h>

//global constants
const int MAX_STR_LEN = 200;
const char NULL_CHAR = '\0';
/*
function name: getStringLength
Algorithm: find the length of the string, up tothe null character
precondition: given C-style with null character at end
postcondition: return the number of characters (int) from the begining 
		to the null character
Exception: none
Note: limit test loop to maximum characters for safety

*/
int getStringLength( char *testStr )
    {
	// initialize function.variables
	int index = 0;
	// loop up to null character or limit
	while(index < MAX_STR_LEN && testStr[ index ] != NULL_CHAR )
	{
	//INCREMENT THE COUNTER index
	index++;
	}
	//end loop
	//return the counter index value
	return index;
    }

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

