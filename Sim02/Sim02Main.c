#include <stdio.h>
#include "configAccess.h"
#include "MetaDataAccess.h"
#include "SimTimer.h"
#include "Simulator.h"
#include <pthread.h>

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
		int configAccessResult, mdAccessResult;
		char configFileName[ MAX_STR_LEN ];
		char mdFileName[ MAX_STR_LEN ];
		ConfigDataType *configDataPtr;
		OpCodeType *mdData;

    	// display titles
    	  //function: printf
    	printf("\nConfig File Upload Program\n" );
        printf("============================\n" );

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
           // displayConfigData( configDataPtr );
            
        }

     	// otherwise, assume failed upload
        else 
        {
        
        	// display configuration upload error
              // function: displayConfigE
           // displayConfigError( configAccessResult );
          
         }

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
        copyString( mdFileName, configDataPtr->metaDataFileName );
        mdAccessResult = getOpCodes( mdFileName, &mdData);

        printf("\nSimulator Program\n" );
        printf("==========================\n\n" );
        // check for succesful upload
        if(configAccessResult == NO_ERR && mdAccessResult == NO_ERR  )
        {
 
        // display meta data file
          //function: displayMetaData
       // displayMetaData( mdData );
            runSim(configDataPtr, mdData);

           
        
        }

        // otherwise, assume failed upload
      

        

       
       
        //runSim(runTime);

        // shutdown program clean up program
       
        // clear meta data
          //function: clearMetaDataList
        mdData = clearMetaDataList( mdData );
       
	    clearConfigData( &configDataPtr );

        // add endline for vertical spacing
        // function: printf
    // return success
////////////////////////////////


    return 0;
    }
    







