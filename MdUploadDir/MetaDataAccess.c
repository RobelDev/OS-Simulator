//header files
#include "MetaDataAccess.h"


/*
function name: getOpCodes
Algorithm: opens file,acquires op code data,
	returns pointer to head of linked list
precondition: for correct operation, returns pointer to head
		of op code linked list
postcondition: return s zero(0) on success
Exception: correctly and appropriately (no failure)
	responds to file access falure
	incorrectly formatted lead or end descriptors
	incorrectly op code nameor incorrect op code letter
	and incomplete file conditions
Note: noone

*/

int getOpCodes( char *fileName, OpCodeType **opCodeDataHead )
    {
	// initialize function/variables
	const char READ_ONLY_FLAG[] = "r";
	// initialize read only constant
	int startCount = 0, endCount =0;
	// initialize start and end counts
	OpCodeType *localHeadPtr = NULL;
	// initialize local head pointer to null
	int accessResult;
	char dataBuffer[ MAX_STR_LEN ];
	OpCodeType *newNodePtr;
	FILE *fileAccessPtr;
	// initialize variables
	
     // initialize op code data pointer
       *opCodeDataHead = NULL;
       //open file for reading
	  //function:fopen
	fileAccessPtr = fopen( fileName, READ_ONLY_FLAG );
	// check for file open failure
       if( fileAccessPtr == NULL )
      {

	    //return file access error
		return MD_FILE_ACCESS_ERR;
	}

	// check first line for correct leader
           //function:getLineTo, compareString

 	if(  getLineTo( fileAccessPtr, MAX_STR_LEN, COLON,
                   dataBuffer, IGNORE_LEADING_WS ) != NO_ERR
      		|| compareString( dataBuffer, "Start Program Meta-Data Code" )
               != STR_EQ )
	{

         // close file access
         // function: fclose
        fclose( fileAccessPtr );
   
	    //return corrupt descriptor error
	return MD_CORRUPT_DESCRIPTOR_ERR;
	}
	//allocate memory for temporary data structure
	  //function:malloc
	newNodePtr = (OpCodeType *) malloc( sizeof( OpCodeType ) );
	// get the first opc omand
	  //function: getOpCommand
	accessResult = getOpCommand( fileAccessPtr, newNodePtr );
	// get the start and endecounts
	  //function: updateStartCount, updateEndCount
       startCount = updateStartCount( startCount, newNodePtr->opName );
       endCount = updateEndCount( endCount, newNodePtr->opName );
	// check for failure of first compelet command
	if( accessResult != COMPLETE_OPCMD_FOUND_MSG )
	{
		// close file
                 //function:fclose
		fclose( fileAccessPtr );
		//clear data from structure list
		  //function: clearMetaDataList
  		*opCodeDataHead = clearMetaDataList( localHeadPtr );

	         // fee temp
                 //function:free
	         free( newNodePtr );


	        // report result operation fo
	         return accessResult;
	}

      //loop accross all remaining
	//while
	while( accessResult == COMPLETE_OPCMD_FOUND_MSG )
	{

	//add new command
	//function: addNode
	localHeadPtr = addNode( localHeadPtr, newNodePtr );

	// get new comand
	//function: getOpComand
	accessResult = getOpCommand( fileAccessPtr, newNodePtr);

	//update start and end counts
	// function:updateStartCount, UpdateEndcount
       startCount = updateStartCount( startCount, newNodePtr->opName );
       endCount = updateEndCount( endCount, newNodePtr->opName );
	}
     //loop complete
	if( accessResult == LAST_OPCMD_FOUND_MSG )
	{
	// check start and end op
	 if( startCount == endCount )
	{
	//add another last command
	//function: addNode	
         localHeadPtr = addNode( localHeadPtr, newNodePtr );
       //set access result no error
	accessResult = NO_ERR;
        //otherwise start count not equal
		// set unbalanced start
	   if(  getLineTo( fileAccessPtr, MAX_STR_LEN, PERIOD,
                   dataBuffer, IGNORE_LEADING_WS ) != NO_ERR
      		|| compareString( dataBuffer, "End Program Meta-Data Code" )
               != STR_EQ )
	     {
	   //check for any errrors
            accessResult = MD_CORRUPT_DESCRIPTOR_ERR;
              }
          }
	  else 
	{
		//check for any errrors
           accessResult = UNBALANCED_START_END_ERR;
	}
      }

    // check for any errors found
    if ( accessResult != NO_ERR )
	{
	//clear the op command
	//function:clerMetaDataLis
	localHeadPtr = clearMetaDataList( localHeadPtr );
	}
       //close all file
       fclose( fileAccessPtr );

       //release temp structure
       //function: free
       free( newNodePtr );

       //assign temp local head pointer
       *opCodeDataHead = localHeadPtr;

	// retrun accessResult 
     return accessResult ; 
    }



/*
function name: getOpCommand
Algorithm: raccquires one op command verifies and returns
precondition: lfile is openand file cursor is at begining
postcondition: correct operation finds, test, and returns op command
		returns integer complete or last
Exception: no failure compte
	responds to incorrrctly formated coomand lltter, name ,value
Note: noone

*/
int getOpCommand( FILE *filePtr, OpCodeType *inData ) 
    {

      // initialize function/variables
	const int MAX_OP_NAME_LENGTH = 10;
	const int MAX_OP_VALUE_LENGTH = 9;

	// initialize read only constant
	int intBuffer =0;

	// initialize start and end counts
	int sourceIndex = 0, destIndex = 0;

	// initialize local head pointer to null
	int accessResult;
	char strBuffer[ STD_STR_LEN ];

	// initialize variables
	accessResult = getLineTo( filePtr, STD_STR_LEN, SEMICOLON,
			strBuffer, IGNORE_LEADING_WS );
     // initialize op code data pointer
       if ( accessResult == NO_ERR )
	{
	  inData->opLtr = strBuffer[ sourceIndex ];
         }

         else 
	{
	// SET POINTER TO NULL	
	  inData = NULL;
	
	// RETURN
	return OPCMD_ACCESS_ERR;
	}

	//VERIFY the op command
	switch( inData->opLtr )
	{
      // check
	case 'S':
	case 'A':
	case 'P':
	case 'M':
	case 'I':
	case 'O':
	break;
	
	// other wise not corect case
	default:

	// set op coomand pointer to null
	  inData = NULL;

	// RETURN
	  return CORRUPT_OPCMD_LETTER_ERR;
	}

      // while loop till parent found
      while( sourceIndex < STD_STR_LEN && strBuffer[ sourceIndex ]
				!= LEFT_PAREN )
	{
	//increment
	sourceIndex++;
	}
	//skip 
	sourceIndex++;

	   // while loop till parent found
      while( sourceIndex < STD_STR_LEN && 
		destIndex < MAX_OP_NAME_LENGTH 
            && strBuffer[ sourceIndex ] != RIGHT_PAREN )
	{
	//ACQUIRE
	inData->opName[ destIndex ] = strBuffer[ sourceIndex ];

	//increment
	destIndex++; sourceIndex++; 

	// set end null char
	inData->opName[ destIndex ] = NULL_CHAR; 
	}

	// LOOP
	if( checkOpString( inData->opName ) == False )
	{
	// set struct to null
	inData = NULL;

	// RETURN
	return CORRUPT_OPCMD_NAME_ERR;
     }
   

   sourceIndex++;
   destIndex = 0; 
   
     // WHILE
     while( sourceIndex < STD_STR_LEN && destIndex <
		MAX_OP_VALUE_LENGTH && 
	isDigit( strBuffer[ sourceIndex ]) == True )

	{ 
	// multiply
	   intBuffer *= 10;

	// add next integer
	intBuffer += (int) (strBuffer[ sourceIndex ] - '0' );

	//increment
      destIndex++; 
      sourceIndex++;
    
	}
   
       // check overrun failure
	if( sourceIndex == STD_STR_LEN || destIndex == MAX_OP_VALUE_LENGTH )
	{
	//SET STRUCT TO NULL
	inData = NULL;

	// RETURN corrupt op command value
	return CORRUPT_OPCMD_VALUE_ERR;
	}

	// SET VALUE TO DATA 
	inData->opValue = intBuffer;

	// check for last op command
		//function: compareString
	if(( inData->opLtr == 'S' )
		&&  ( compareString( inData->opName, "end" ) == STR_EQ ))
	{
	// return last op command found message
	return LAST_OPCMD_FOUND_MSG;
	}

	// RETURN COMPLETE OP COMMAND FOUND MESSAGE
	return COMPLETE_OPCMD_FOUND_MSG;
       
    }

/*
function name: updateStartCount
Algorithm: pdate number of "start"
precondition: count >= 0 "start"
postcondition: if op starting has "start", input count+1 returned
	otherwise input count reruned no change
Exception:none
Note: noone

*/

int updateStartCount( int count, char *opString ) 
   {
	// CHECK FOR "START"
	//function: compareString
	if( compareString( opString, "start" ) == STR_EQ )
	{
		// RETURN
	     return count + 1;
	}
	
	//return unchanged start count

        return count;
   }


/*
function name: updateEndCount
Algorithm: pdate number of "end"
precondition: count >= 0 "start"
postcondition: if op starting has "end", input count+1 returned
	otherwise input count reruned no change
Exception:none
Note: noone

*/

int updateEndCount( int count, char *opString ) 
   {
    // CHECK FOR "end"
	//function: compareString
	if( compareString( opString, "end" )==STR_EQ )
	{
		// RETURN
	return count + 1;
	}
	
	//return unchanged start count

    return count;
   }

/*
function name: addNode
Algorithm: adds node to command structure
precondition: limked list pointer
postcondition: assign new node
Exception:none
Note: assume memory access availbale

*/

OpCodeType *addNode( OpCodeType *localPtr, OpCodeType *newNode ) 
   {
	//check local pointer
	if ( localPtr == NULL )
	{
	localPtr = (OpCodeType * )malloc(sizeof( OpCodeType ) );

	// assign all three values
	// assign next pointer to null
		//function: copyString
	localPtr->opLtr = newNode->opLtr;
	copyString( localPtr->opName, newNode->opName );
	localPtr->opValue = newNode->opValue;
	localPtr->next = NULL;

	//RETURN CURRENTLOCAL POINTER

 	 return localPtr;
         }
   
     //assume recurseive vurrent next link
	//function: addNode
     localPtr->next = addNode( localPtr->next, newNode );

    //return current local pointer
    return localPtr;
   }
//
/*
function name: checkOpString
Algorithm: iterates display
precondition: testStr of strings
postcondition: return true or false
	otherwise input count reruned no change
Exception:none
Note: noone

*/

Boolean checkOpString( char *testStr ) 
   {
	//check for all posible op names
	  //function: compareString
       if( compareString( testStr, "access" )     == STR_EQ
	|| compareString( testStr, "allocate" )   == STR_EQ
	|| compareString( testStr, "end" )        == STR_EQ
	|| compareString( testStr, "hard drive" ) == STR_EQ
	|| compareString( testStr, "keyboard" )   == STR_EQ
	|| compareString( testStr, "printer" )    == STR_EQ
	|| compareString( testStr, "monitor" )    == STR_EQ
	|| compareString( testStr, "run" )        == STR_EQ
	|| compareString( testStr, "start" )      == STR_EQ )
	{
		//return found -true
		return True;
	}
    // return failure
    return False; 
   
   }

/*
function name: isDigit
Algorithm: characters 0<v , 9 
precondition: chjhrt"
postcondition: returns true or false is its digit or not
Exception:none
Note: noone

*/

Boolean isDigit( char testChar ) 
   {
	// check for test character between characters '0' - '9'
	if( testChar >= '0' && testChar <= '9' )
	{
	//return true
	return True;
	}
	//otherwise not digit
      return False;
   
   }

/*
function name: displayMetadata
Algorithm: iuses constant value as index to display string
	then display success
precondition: a local pointer
postcondition: display characters, strings, integers 
Exception:none
Note: noone

*/

void displayMetaData( OpCodeType *localPtr ) 
   {
	//display title
	  //function: printf
	printf( "\nMeta-Data file Display\n" );
	printf( "=========================\n" );

	//while
	while( localPtr != NULL )
	{
	
	//print op code letter
		//function: printf
	printf( "Op code letter: %c\n", localPtr->opLtr );

	// print op code letter
		//function: printf
	printf( "Op code name: %s\n", localPtr->opName );

	//print op code letter
		//function: printf
	printf( "Op code value: %d\n\n", localPtr->opValue );

	// assign local pointer to next node
	localPtr = localPtr->next ;
       }
     
   
   }

/*
function name: displayMetaDataError
Algorithm: iuses constant value as index to display string
	then display error message
precondition: integer input
postcondition: error message
Exception: none
Note: noone

*/

void displayMetaDataError( int code )
    {
	// create string errors list, 10 items max 35 letters
	char errList[ 10 ][ 35 ] =
			{"No Error",
			"Incomplete File Error",
			"Input Buffer Overrun",
			"MD File Access Error",
			"MD Corrupt Descriptor Error",
			"Op Command Access Error",
			"Corrupt Op Command letter Error",
			"Corrupt Op Command Name Error",
			"Command Op Command value Error",
			"Unbalanced Start-End Code Error"};
	// display error to monitor
		//function: printf
	printf( "\nFATAL ERROR: %s, Program aborted\n", errList[ code ] );
     // no return no data strig
    }


/*
function name: clearMetaDataList
Algorithm: recursively iterates through op code linked list
	returns memory to OS from bottom
precondition: linked list with ot with out data
postcondition: all node memory, if any is returned to OS 
	RETURN POINTER
Exception: none
Note: noone

*/

OpCodeType *clearMetaDataList( OpCodeType *localPtr ) 
   {
	// check for local pointer not set to null
	if( localPtr != NULL )
	{
	//CHECK NEXT NODE
	   if( localPtr->next != NULL )
	   {
	  // call recursive
		// function: clearMetaDataList
	     clearMetaDataList( localPtr->next );
	    }
	// after recurvsive release memory
	  // function: free
	   free( localPtr );
	   }

	// report null to calling function

        return NULL;
   }






















