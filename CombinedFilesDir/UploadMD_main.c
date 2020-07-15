#include <stdio.h>
#include "MetaDataAccess.h"

/*
function name: main
Algorithm: driver function to test metadata file upload function
precondition: none
postcondition: return s zero(0) on success
Exception: none
Note: demonstrates development and use of metadata file upload function

*/

int main( int argc, char **argv )
    {
      //initialize function/variables
	   int mdAccessResult;
	   char mdFileName[ MAX_STR_LEN ];
	   OpCodeType *mdData;

     // display titles
         //function: printf
	   printf("\nMeta Data File Upload Program\n" );
     printf("============================\n" );

     // check for command line arguements
  	if( argc < 2 )
           {
          // display missing command line arguement error
	         //function: printf
            printf("\nERROR: Program requires file name for meta data file" );
            printf("as command line arguement\n" );
            printf("Program terminated\n" );

          // return non-normal program exit status
            return 1;
           }
      // get data from cmetadta file
             //function: copyString, getOpCodes
      copyString( mdFileName, argv[ 1 ] );
      mdAccessResult = getOpCodes( mdFileName, &mdData);

     // check for succesful upload
    if( mdAccessResult == NO_ERR )
      {
 
        // display meta data file
          //function: displayMetaData
        displayMetaData( mdData );
           }

        // otherwise, assume failed upload
        else 
          {
         // display configuration upload error
            // function: displayMetaDataError
          displayMetaDataError( mdAccessResult );

          }

        // shutdown program clean up program
       
         // clear meta data
             //function: clearMetaDataList
        mdData = clearMetaDataList( mdData );

         // add endline for vertical spacing
             // function: printf
        printf( "\n");
     // return success
     return 0;
    }
    







