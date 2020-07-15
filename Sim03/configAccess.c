//header file
#include "configAccess.h"

/*
Function Name: getConfigData
Algoorithm: opens file, acquires configuration data,
           returns pointer to data structure
precondition: for correct operation, file is avalable, is formatted correctly,
        and has all configuration lines and data although the configuration
         lines are not required to be in a specific order
postcondition: in correct operation, returns ponter to correct
              configuration data structure
exceptions: correct and appropriately with out program failure responds to
        and reports file access failure, incorrectly formatted lead or
        end descriptors, incorrectly formatted prompt, data out of range
        and incomplete file condition
NOtes: none    
*/

int getConfigData( char *fileName, ConfigDataType **configData)
    {
    //initialize function variables

    // set constant number of data lines to 9
    const int NUM_DATA_LINES = 9;

    // set line counter to zero
    int lineCtr = 0;

    // set read only constant to "r"
    const char READ_ONLY_FLAG[] = "r";

   // create pointer for data input
    ConfigDataType *tempData;

    // declare other variables
    FILE *fileAccessPtr;
    char dataBuffer[ MAX_STR_LEN ];
    int intData, dataLineCode;
    double doubleData;

    //initialiaze config data ponter  in case of return errot
    *configData = NULL;

    // open file
      // function: open
    fileAccessPtr = fopen( fileName, READ_ONLY_FLAG );

    // check for file open failure
    if( fileAccessPtr == NULL )
        {
        // return file access error
		return CFG_FILE_ACCESS_ERR;
        }

    // get first line, check for failure
    // function: getLineTo
    if( getLineTo( fileAccessPtr, MAX_STR_LEN, COLON,
            dataBuffer, IGNORE_LEADING_WS ) != NO_ERR
      		|| compareString( dataBuffer, "Start Simulator Configuration File" )
            != STR_EQ )
      	{
      	// close file access
        // function: fclose
        fclose( fileAccessPtr );

        // return corrupt file data
        return CFG_CORRUPT_DESCRIPTOR_ERR;
	    }
    // create temporary pointer to configuration data structure
    // function: malloc
    tempData = ( ConfigDataType *) malloc( sizeof( ConfigDataType ) );

    // loop to end of config data items
    while( lineCtr < NUM_DATA_LINES )
        {
        // get line reader, check for failure
           // function: getLineTo
        if( getLineTo( fileAccessPtr, MAX_STR_LEN, COLON, 
                dataBuffer, IGNORE_LEADING_WS ) != NO_ERR )
           {

            //  free temp struct memory
            //function: free 
            free( tempData );

        	//close file access
        	  //function: fclose
        	fclose( fileAccessPtr );

        	// return incomplete file error
        	return INCOMPLETE_FILE_ERR;
       		}

     	// find correct data line by number
        //function: getDataLineCode
        dataLineCode = getDataLineCode( dataBuffer );

        // check for data line found
        if( dataLineCode != CFG_CORRUPT_PROMPT_ERR )
			{
        	//get data value
    
            // check for version number (double value)
            if( dataLineCode == CFG_VERSION_CODE )
              {  
               //get version number
                   //function: fscanf
               fscanf( fileAccessPtr, "%lf", &doubleData );
             }

          	//otherwise, check for metadata or logTo file names
           // or CPU scheduling names (strings)
            else if( dataLineCode == CFG_MD_FILE_NAME_CODE 
                   || dataLineCode == CFG_LOG_FILE_NAME_CODE
		   		|| dataLineCode == CFG_CPU_SCHED_CODE
		   		|| dataLineCode == CFG_LOG_TO_CODE )
            {
            //get  string input
                // function: fscanf
             fscanf( fileAccessPtr, "%s", dataBuffer );
			}

           // otherwise, assume integer data
           else
            {
             //get  string input
                // function: fscanf
            fscanf( fileAccessPtr, "%d", &intData ); 
            
            }
          
         	// check for data value in range
                // function: valueInRange
	    	if( valueInRange( dataLineCode,intData, doubleData, dataBuffer )
                    == True )
            {   
            // assign to data pointer depending on config item
             switch( dataLineCode )
            	{
                // case version code
				case CFG_VERSION_CODE:

                   // assign version to double data
		   		tempData->version = doubleData;
		   		break;

                // case meta data file name code
				case CFG_MD_FILE_NAME_CODE:

                 // assign version to double data
                       // function: copyString
		   		copyString( tempData->metaDataFileName, dataBuffer );
		   		break;

               // case cpu schedulecode
				case CFG_CPU_SCHED_CODE:

                   // assign version to double data
                       // function: getCpuSchedCode
		   		tempData->cpuSchedCode = getCpuSchedCode( dataBuffer );
		   		break;
	    
               // case quantum cycles code
				case CFG_QUANT_CYCLES_CODE:

                   // assign quantum cycles to int data
		   		tempData->quantumCycles = intData;
		   		break;

               // case memory available code
				case CFG_MEM_AVAILABLE_CODE:

                   // assign memory available to int data
		   		tempData->memAvailable = intData;
		   		break;

             // case processor cycles code
				case CFG_PROC_CYCLES_CODE:
                   // assign processor cycles rate to int data
		   		tempData->procCycleRate = intData;
		   		break;

               // case IO cycles code
				case CFG_IO_CYCLES_CODE:

                // assign IO cycles rate to int data
		   		tempData->ioCycleRate = intData;
		   		break;

               // case Log to code
				case CFG_LOG_TO_CODE:
                  // assign log to rate to int data
		   		tempData->logToCode = getLogToCode( dataBuffer );
		   		break;

				// case log to file name code
				case CFG_LOG_FILE_NAME_CODE:

            	// assign log to file name using string data
				//function: copyString
		   		copyString( tempData->logToFileName, dataBuffer );
		   		break;
			}
		}

           // otherwise, assume data value not in range
 	     else
		{
               // free temp struct memory
		   //function: free
		free( tempData );

               // close file access
		   //function: fclose
		fclose( fileAccessPtr );

              // return data out of range
		return CFG_DATA_OUT_OF_RANGE_ERR;
		}
	    }
         // otherwise, assume data line not found
   	    else
		{
            // free temp struct memory
               //function: free
		free( tempData );

            // close file access
               //function: fclose
		fclose( fileAccessPtr );

             // return corrupt config file code
		return CFG_CORRUPT_PROMPT_ERR;
		}

           // increment line counter
	   lineCtr++;
	}

      // end master loop

     // acquire end of sim config string
          // function: getLineTo
	if( getLineTo( fileAccessPtr, MAX_STR_LEN, PERIOD, dataBuffer, 
			IGNORE_LEADING_WS ) != NO_ERR ||
			compareString( dataBuffer, "End Simulator Configuration File" )
						!= STR_EQ )
		{
          	// free temp struct memory
               //function: free
  			free( tempData ); 
      
          	// close file access
               //function: fclose
			fclose( fileAccessPtr );

	        //return corrupt file data
			return CFG_CORRUPT_DESCRIPTOR_ERR;
		}

      // assign temporary pointer to parameter return pointer
	*configData = tempData;

    // close file access
               //function: fclose
	fclose( fileAccessPtr );

     // return no error code
     return NO_ERR;  
    }

/*
Function Name: getDataLineCode
Algoorithm: tests string for one of unknown leader strings, return line number
	  if string is correct, returns CFG_CORRUPT_DATA_ERR
           if string is not found
precondition: dataBuffer is valid C-Style string
postcondition: returns line number of data item in terms of a constant
          (e.g. CFG_VERSION_CODE, CFG_CPU_SCHED_CODE, etc)
exceptions: returns CFG_CORRUPT_DATA_ERR if string is not identified
NOtes: none    
*/

int getDataLineCode( char *dataBuffer )
    {
    // return appropriate code depending on prompt string provided

   // check for version/phase string
	// function:compareString
	if( compareString( dataBuffer, "Version/Phase" ) == STR_EQ )
	{
        //return configuration version code
 	 	return CFG_VERSION_CODE;
	}

       // check for file path string
	// function:compareString
	if( compareString( dataBuffer, "File Path" ) == STR_EQ )
		{
	  	//return meta data file path code
	 	return CFG_MD_FILE_NAME_CODE;
		}

       // check for cpu scheduling code string
		// function:compareString
	if( compareString( dataBuffer, "CPU Scheduling Code" ) == STR_EQ )
	{

	  	//return cpu schedule code
	 	return CFG_CPU_SCHED_CODE;
	}

    // check for quantum time string
	// function:compareString
	if( compareString( dataBuffer, "Quantum Time (cycles)" ) == STR_EQ )
	{
	 	 //return quantum cycles code
	 	return CFG_QUANT_CYCLES_CODE;
	}

       // check for memory available string
	// function:compareString
	if( compareString( dataBuffer, "Memory Available (KB)" ) == STR_EQ )
	{
	  //return memory available code
	 		return CFG_MEM_AVAILABLE_CODE;
	}

       // check for processor cycle time string
	// function:compareString
	if( compareString( dataBuffer, "Processor Cycle Time (msec)" ) == STR_EQ )
	{
	  	//return processor cycle time code
	 	return CFG_PROC_CYCLES_CODE;
	}

       // check for I/O cycle time string
	// function:compareString
	if( compareString( dataBuffer, "I/O Cycle Time (msec)" ) == STR_EQ )
	{
	  //return I/O cycle time code
	 return CFG_IO_CYCLES_CODE;
	}

       // check for log to string
	// function:compareString
	if( compareString( dataBuffer, "Log To" ) == STR_EQ )
	{
	  //return log to code
	 return CFG_LOG_TO_CODE;
	}

       // check for log file path string
	// function:compareString
	if( compareString( dataBuffer, "Log File Path" ) == STR_EQ )
	{
	  //return log file path code
	 return CFG_LOG_FILE_NAME_CODE;
	}

    //at this point, assumefailed string access, return corrupt error
     return CFG_CORRUPT_PROMPT_ERR; // temporary stub retun
    }

/*
Function Name: getCpuSchedCode
Algoorithm: converts string data( e.g., "SJF-N", "SRTF-P")
	   TO CONSTANT CODE NUMBER TO BE STORES AS INTEGER
precondition: codeStr is a C-Style string with one of the
		specified cpu scheduling operations
postcondition: returns code representing scheduling actions
exceptions: defaults to FCFS-N code
NOtes: none    
*/

ConfigDataCodes getCpuSchedCode( char *codeStr )
    {

     // initialize function/variables

    // set up temporary string for testing
	//function: getStringLength, malloc
      int strLen = getStringLength( codeStr );
      char *tempStr = (char *) malloc( strLen + 1 );

      // set default return to FCFS-N
	int returnVal = CPU_SCHED_FCFS_N_CODE;

   // SET STRING TO LOWER CASE FOR TESTING
	//function: setStrToLowerCase
	setStrToLowerCase( tempStr, codeStr );

   //check for SJF-N
     //FUNCTION: compareString
     if( compareString( tempStr, "sjf-n" ) == STR_EQ )
	{
     //set return to SJF-N code
	returnVal = CPU_SCHED_SJF_N_CODE;
	}
   //check for SRTF-P
     //FUNCTION: compareString
     else if( compareString( tempStr, "srtf-p" ) == STR_EQ )
	{
     //set return to SRTF-P code
	returnVal = CPU_SCHED_SRTF_P_CODE;
	}

   //check for FCFS-P
     //FUNCTION: compareString
     else if( compareString( tempStr, "fcfs-p" ) == STR_EQ )
	{
     //set return to FCFS-P code
	returnVal = CPU_SCHED_FCFS_P_CODE;
	}

   //check for RR-P
     //FUNCTION: compareString
     else if( compareString( tempStr, "rr-p" ) == STR_EQ )
	{
     //set return to RR-P code
	returnVal = CPU_SCHED_RR_P_CODE;
	}
   //FREE temp string memory
       //function: free
	free( tempStr );
   // return code found
      return returnVal; 
    }


/*
Function Name: valueInRange
Algoorithm: tests one of three values(int, double, string) for being in 
	      specified range, depending on data code
		(i.e specified config value)
precondition: one of the three data values is valid
postcondition: returns true if data is within specified parameters,
	       False otherwise
exceptions: metadata or logfile names are ignored and return True
NOtes: none    
*/

Boolean valueInRange( int lineCode, int intVal,
			double doubleVal, char *stringVal )
    {
     // initialize function/variables

	// set output result to true
	Boolean result = True;

	//declare other variables
	char *tempStr;
	int strLen;

     // use line code to identify prompt line 
	switch( lineCode )
	{
	// for version code
	 case CFG_VERSION_CODE:

	   // check if limits of version code are exceeded
		if( doubleVal < 0.00 || doubleVal > 10.00 )
		{
		// set boolean result to false
		result = False;
		}
	        break;

        // for cpu scheduling code
	case CFG_CPU_SCHED_CODE:

	// create temporary string and set to lower case
	   // function: getStringLength, malloc, setStrToLowerCase
		strLen = getStringLength( stringVal );
		tempStr = (char *) malloc( strLen + 1 );
		setStrToLowerCase( tempStr, stringVal );

	// check for not finding one of the scheduling strings
	   // function: compareString
	       if( compareString( tempStr, "none" ) != STR_EQ
		&& compareString( tempStr, "fcfs-n" ) != STR_EQ
		&& compareString( tempStr, "sjf-n" ) != STR_EQ
		&& compareString( tempStr, "srtf-p" ) != STR_EQ
		&& compareString( tempStr, "fcfs-p" ) != STR_EQ
		&& compareString( tempStr, "rr-p" ) != STR_EQ )
	     {
		
	    //set Boolean result to false
		result = False;
	      }
         // free temp string memory
	    //function: free
	free( tempStr );
	break;

         // for quantum cycles
	 case CFG_QUANT_CYCLES_CODE:
		// check for quantum cycles limits exceeded
		if( intVal < 0 || intVal > 100 )
		{
		    // set Boolean result to false
			result = False;
		}
		break;

         // for memory available
	 case CFG_MEM_AVAILABLE_CODE:
		// check for quantum cycles limits exceeded
		if( intVal < 1 || intVal > 102400 )
		{
		    // set Boolean result to false
			result = False;
		}
		break;

         // Check for process cycles
	 case CFG_PROC_CYCLES_CODE:
		// check for process cycles limits exceeded
		if( intVal < 1 || intVal > 1000 )
		{
		    // set Boolean result to false
			result = False;
		}
		break;

         // check for I/O cycles
	 case CFG_IO_CYCLES_CODE:
		// check for I/O cycles limits exceeded
		if( intVal < 1 || intVal > 10000 )
		{
		    // set Boolean result to false
			result = False;
		}
		break;

         // check for log to cycles
	 case CFG_LOG_TO_CODE:

                // create temporary string and set to lower case
	            // function: getStringLength, malloc, setStrToLowerCas
		strLen = getStringLength( stringVal );
		tempStr = (char *) malloc( strLen + 1 );
		setStrToLowerCase( tempStr, stringVal );

	       // check for not finding one of the scheduling strings
	         // function: compareString
	       if( compareString( tempStr, "both" ) != STR_EQ
		&& compareString( tempStr, "monitor" ) != STR_EQ
		&& compareString( tempStr, "file" ) != STR_EQ )
		{

	         //set Boolean result to false
			result = False;
		}

           // free temp string memory
	      //function: free
	    free( tempStr );

	    break;
	}
     //return result of limit anaylsis
     return result; 
    }

/*
Function Name: getLogToCode
Algoorithm: converts string data( e.g., "FILE", "Monitor")
	   TO CONSTANT CODE NUMBER TO BE STORES AS INTEGER
precondition: codeStr is a C-Style string with one of the
		specified log to operations
postcondition: returns code representing log to actions
exceptions: defaults to monitor code
NOtes: none    
*/

ConfigDataCodes getLogToCode( char *logToStr )
    {
     // initialize function/variables

      // create temporary string
          //function: getStringLength, malloc
	int strLen = getStringLength( logToStr );
	char *tempStr = (char *) malloc( strLen +1 );

	// set default return value to log to monitor
	int returnVal = LOGTO_MONITOR_CODE;

	//set temp string to lower case
            //function: setStrToLowerCase
	setStrToLowerCase( tempStr, logToStr);
	//check for BOTH
          //function: compareString
	   if( compareString( tempStr, "both" ) == STR_EQ )
	   {
	     // set return value to both code
	    returnVal = LOGTO_BOTH_CODE;
	   }

	//check for FILE
          //function: compareString
	   if( compareString( tempStr, "both" ) == STR_EQ )
	   {
 	   // set return value to both code
	    returnVal = LOGTO_FILE_CODE;
	   }

           // free temp string memory
	      //function: free
	    free( tempStr );
	// return code found
     return returnVal; // temporary stub retun
    }


/*
Function Name: displayConfigData
Algoorithm: diagnostic function to show config data output
precondition: parameter has pointer to allocated data set
postcondition:  configuration data is displayed to the screen
exceptions: none
NOtes: none    
*/


void displayConfigData( ConfigDataType *configData )
    {
     // initialize function/variables
	char displayString[ STD_STR_LEN ];

     // print lines of display
	// function: printf, configCodeToString (translates coded items)
	printf( "\nConfig File Display\n" );
	printf( "====================\n" );
	printf( "Version                  : %3.2f\n", configData->version );
	printf( "Program File Name        : %s\n", configData->metaDataFileName );
	configCodeToString( configData->cpuSchedCode, displayString );
	printf( "CPU schedule selection   : %s\n", displayString );
	printf( "Quantum time             : %d\n", configData->quantumCycles );
	printf( "Memory Available         : %ld\n", configData->memAvailable );
	printf( "Process cycle rate       : %d\n", configData->procCycleRate );
	printf( "I/O cycle rate           : %d\n", configData->ioCycleRate );
	configCodeToString( configData->logToCode, displayString );
	printf( "log to selection         : %s\n", displayString );
	printf( "Log file name            : %s\n", configData->logToFileName );

    }

/*
Function Name: configCodeToString
Algoorithm: utility function to support display of CPU
	   scheduling or Log to Code strings
precondition: code variable holds constant value from configDataCodes
	    for item(e.g CPU_SCHED_SRTF_P, LOGTO_FILE_CODE, etc.)
postcondition:  string parameter holds correct string asscoiated with
		the given constant
exceptions: none
NOtes: none    
*/

void configCodeToString( int code, char *outString )
    {

	//define array with eight items, and short (10) lengths
	char displayStrings[ 8 ][ 10 ] = { "SJF-P", "SRTF-P", "FCFS-P",
	                                  "RR-P", "FCFS-N", "Monitor",   
						"File", "Both" };
	// copy string to return parameter
	   //function: copyString
	copyString( outString, displayStrings[ code ] );

    }

/*
Function Name: displayConfigError
Algoorithm: utility function to support display of error code strings
precondition: parameter holds constant value from error code list for
		item ( e.g, CFG_FILE_ACCESS_ERR, etc)
postcondition:  correct errot string (related to integer error code) is 
            displayed
exceptions: none
NOtes: none    
*/

void displayConfigError( int errCode )
    {
	//define array with eight items, and short (40) lengths
	//INCLUDE THREE POTENTIAL ERRORS from StringManipErrors
	char displayStrings[ 7 ][ 40 ] = 
				     { "No Error",
				       "Incompelter File Error",		
				       "Input Buffer Overrun",
				       "Configuration File Access Error",
				       "Corrupt Configuration Descriptor Error",
				       "Data Out Of Range Configuration Error",
				       "Corrupt Configuration Prompt Error" };

	//print error message
	   //function: printf
    printf( "\nFATAL ERROR: %s, Program aborted\n", displayStrings[ errCode ] );
 
    }

/*
Function Name: clearConfigData
Algoorithm: frees all allocated memory for config data
precondition: pointer to config data linked list passed in as
		a parameter
postcondition:  config data memory is freed, ponter 
		is set to null
exceptions: none
NOtes: none    
*/

void clearConfigData( ConfigDataType **configDataPtr )
   {
	// check that config data pointer is not null
	if( *configDataPtr != NULL )
	{
           // free temp structure memory
	      //function: free
	   free( *configDataPtr );
	}
	// set config data pointer to null (returned as parameter)
	 *configDataPtr = NULL; 
    
   }
























