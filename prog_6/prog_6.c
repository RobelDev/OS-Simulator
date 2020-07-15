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
	int strLen, compareResult, subStrIndex ;
        char destStr[ STD_STR_LEN ];
     // display title
       // function: printf
	printf("\nString Utilities Test Program\n");
	printf("===============================\n");
     // conduct string length test
	// function: getStringLength
	strLen = getStringLength( testStr );
	
     // display result to user
	//function: printf 
	printf("The length of the string \'%s\' is %d\n\n", testStr,strLen);
     // test copy string function
         // function: copyString
       copyString( destStr, testStr);
     //display the result to the user
	// function: printf
       printf("\n the string \'%s\' was corectly copied\n", destStr);
     // test concatenate string function
        //function: concatenateString
       concatenateString( destStr, " In Major keys" );
     // display concatenate test string result to the user
        //function: printf
      printf("\n the string \'%s\' was corectly concatenated\n", destStr);
     // test compare string function for greater than function
	//function: compareString
     compareResult = compareString( "Susan", "Bill" );
     // display compareString test string result to the user
        //function: printf
     printf("\n the difference between susan and bill is %d\n", compareResult);
     // test compare string function for less than function
	//function: compareString
      compareResult = compareString( "Anya", "Meghan" );
     // display compareString test string result to the user
        //function: printf
         printf("\n the difference between Anya and MEghan %d\n", compareResult);
      // test compare string function for equal name 
       // but one is longer than the otehr
	//function: compareString
           compareResult = compareString( "will", "william" );
     // display compareString test string result to the user
        //function: printf
          printf("\n the difference between will and williuam is %d\n", compareResult);
     // test get substring function (magic numbers used for indices never do this outside testing
       // function: getSubString
      getSubString( destStr, destStr, 20, 32 );
     // display getSubString test result to the user
        //function: printf
       printf("\n the substring \'%s\' was generated\n", destStr);
       
     // test find sub string
        // function: findSubString
       subStrIndex = findSubString( destStr, "ne In Ma" );
     // display findsubstring test result to the user
       //function: printf
        printf("\n the substring \'ne In Ma\' starts at index %d\n", subStrIndex);
     // test for subtring failure - not found
        // function: findSubString
         subStrIndex = findSubString( destStr, "In Major Keys" );
         if ( subStrIndex == SUBSTRING_NOT_FOUND )
         {
           // output not found
           printf("\n the substring \'In major keys\' not found\n");
          }
         // otherwise, assume that is found
        else
          {
          // output found
           printf("\n the substring \'In major keys\' start at index %d\n", subStrIndex);
          }
     // test doe string with any upper case letter or lower case
         // function: copyString, setStrToLowerCase
      copyString( testStr, destStr );
      setStrToLowerCase( destStr, testStr );
     // display lower case string result to the user
        //function: printf
           printf("\n the string \'%s\' as lower case is %s\n", testStr, destStr);
     // shutdown program

         //return program success
	return 0;



    }























