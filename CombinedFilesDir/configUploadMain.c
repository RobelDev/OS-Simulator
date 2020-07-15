//header files
#include <stdio.h>
#include "configAccess.h"

/*
function name: main
Algorithm: driver function to test getStringLength function
precondition: none
postcondition: return s zero(0) on success
Exception: none
Note: demonstrates development and use of string length function

*/

int main( int argc, char **argv )
    {
     //initialize function/variables
       int configAccessResult;
       char configFileName[ MAX_STR_LEN ];
       ConfigDataType *configDataPtr;

      // display titles
      //function: printf
       printf("\nConfig File Upload Program\n" );
       printf("==========================\n\n" );

     // check for not correct number of command line arguements (2)
       if( argc < 2 )
           {

          // print missing command line arguement error
            printf("Error: program requires file name for config file" );
            printf("as command line arguement\n" );
            printf("Program Terminated\n" );

          // return non-normal program result
            return 1;
           }
        // get data from configuration file
             //function: copyString, getConfigData
        copyString( configFileName, argv[ 1 ] );
        configAccessResult = getConfigData( configFileName, &configDataPtr );

        // check for succesful upload
        if( configAccessResult == NO_ERR )
           {
 
         // display config file
             //function: printf
            displayConfigData( configDataPtr );
           }

        // otherwise, assume failed upload
        else 
          {
         // display configuration upload error
            // function: displayConfigE
            displayConfigError( configAccessResult );

          }

          // shutdown program
       
         // clear configuration data
             //function: clearConfigData
           clearConfigData( &configDataPtr );

         // add endline for vertical spacing
             // function: printf
           printf( "\n");

         //return program success
	return 0;



    }























