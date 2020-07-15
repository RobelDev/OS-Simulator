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
