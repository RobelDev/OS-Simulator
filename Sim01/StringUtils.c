//header files
#include "StringUtils.h"

//global constants
const int MAX_STR_LEN = 200;
const int  STD_STR_LEN = 80;
const int SUBSTRING_NOT_FOUND = -101;
const int STR_EQ = 0;
const char NULL_CHAR = '\0';
const char SPACE = ' ';
const char COLON = ':';
const char PERIOD = '.';
const char SEMICOLON = ';';
const char LEFT_PAREN = '(';
const char RIGHT_PAREN = ')';

const Boolean IGNORE_LEADING_WS = True;
const Boolean ACCEPT_LEADING_WS = False;
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
  	int index =0;
  	// loop up to null character or limit
  	while(index<MAX_STR_LEN && testStr[ index ] != NULL_CHAR )
  	{
    	//INCREMENT THE COUNTER index
    	index++;
  	}
  	//end loop
  	//return the counter index value
  	return index;

    }

/*
function name: copySTring
Algorithm: copies contents of one string into another
precondition: given C-style source string, having a null character ('\0')
	     at the end of string; destination string is passed in as a 
	     parameter with enough memory to accept the source string
postcondition: destination string contains an exact copy of the source string
Exception: none
Note: limit test loop to maximum characters for safety

*/

void copyString( char *destination, char *source )
   {
      // initialize function.variables
      int index = 0;

      // loop up to null character or limit
    while( index<MAX_STR_LEN && source[ index] != NULL_CHAR )
     {
      //asign source to destination element
       destination[ index ] = source[ index ];

       //INCREMENT THE COUNTER index 
       index++;

    destination[ index ] = NULL_CHAR; 
      }
    //end loop
     
   }

/*
fnction name: concatenateString
Algorithm: concatenates or appends content of one string onto the end of another
precondition: given C-style source string, having a null character ('\0')
             at the end of string; destination string is passed in as a 
	     parameter with enough memory to accept the source string
postcondition: destination string contains its original string with the
              source appended or concatenated to the end of it
Exception: none
Note: limit test loop to maximum characters for safety
*/
void concatenateString( char *destination, char *source)
   {
      // initialize function.variables
        //function: getStringLength
      int destIndex = getStringLength( destination );
      int sourceIndex = 0;

      // loop up to null character or limit
    while( sourceIndex < MAX_STR_LEN && source[ sourceIndex] != NULL_CHAR )
     {
        //asign source to destination element
       destination[ destIndex ] = source[ sourceIndex ]; 

       //INCREMENT THE COUNTER index
       sourceIndex++; destIndex++;
       //asign source to destination element
      destination[ destIndex ] = NULL_CHAR; 
      }
     
    //end loop
   }

/*
fnction name: compareString
Algorithm: compares two strings alphabetically such that:
	  if oneStr < othertr, the function returns a value < 0
	  if oneStr > othertr, the function returns a value > 0
	  if oneStr = othertr, the function returns a value 0
	  if the two strings are identical up to the point that one
            is longer, the difference in lengths will be returned
precondition: given C-style source string, having a null character ('\0')
             at the end of each string
postcondition: integer value returned as specified
Exception: none
Note: limit test loop to maximum characters for safety
*/
int compareString( char *oneStr, char *otherStr)
   {
    // initialize function.variables
    int index = 0;
    int difference;

    // loop up to null character or limit
    while( index<MAX_STR_LEN && oneStr[ index] != NULL_CHAR 
            && otherStr[ index ] != NULL_CHAR)
     {
      // find the difference between the currently aligned characters
       difference = oneStr[ index ] - otherStr[ index ];

       // check for non-zero
       if ( difference != 0 )
      {
        //return non zero difference
        return difference;
      }
      //increment index
      index++;
        
      }
      // rerun difference
    return getStringLength( oneStr ) - getStringLength( otherStr );
   }

/*
fnction name: getSubString
Algorithm: captures sub string with in larger string between two
		inclusive indices
precondition: given C-style source string, having a null character ('\0')
             at the end of each string parameter with enough memory to accept the source string
postcondition: string value returned as parameter
Exception: empty string returned if any of the index parameters are out of range
Note: copy of source string is made internally to protect from aliasing
*/
void getSubString( char *destStr, char *sourceStr, 
                      int startIndex, int endIndex)
   {
    // initialize function.variables
    int sourceStrLen = getStringLength( sourceStr );
    int destIndex = 0;
    int sourceIndex = startIndex;
    char *tempSourceStr;
    // temproray

    // check for indices with in limoits
    if (startIndex >= 0 && startIndex <= endIndex && endIndex < sourceStrLen )
    {
      //create temporary 
        // function: malloc
     tempSourceStr = (char * ) malloc( sourceStrLen + 1 );
     copyString( tempSourceStr, sourceStr );
     
     //loop across requested
    while( sourceIndex <= endIndex )
     {
      //assign source character to destination
      destStr[destIndex ] = tempSourceStr[ sourceIndex ];
    
      //increment indices
      destIndex++, sourceIndex++;

      // add null character
    destStr[ destIndex ] = NULL_CHAR; 
    }

     //end loop
    // free temporary string
        //function: free
      free( tempSourceStr );
   }

   //otherwise
     else 
       {

        //assign to null
       destStr[ 0 ] =NULL_CHAR;

      }
   
    
   }


/*
fnction name: findSubString
Algorithm: linear search for given substring with in a given test string
precondition: given C-style test string, having a null character ('\0')
             at the end string parameter and given serach string with a null character
          ('\n') at the end of that string 
postcondition: index of substring location returned, or SUBSTRING_NOT_FOUND constant is required
Exception: none
NOte: none
*/
int findSubString( char *testStr, char *searchSubStr )
   {
    // initialize function.variables
    int testStrLen = getStringLength( testStr );
    int masterIndex = 0;
     
    int searchIndex, internalIndex;

    // loop limits
    while( masterIndex < testStrLen )
    {
      //assign internal to master index
    internalIndex = masterIndex;

    // search index to zero
    searchIndex = 0;
    
    // loop characters are same
    while( internalIndex <= testStrLen 
    && testStr[ internalIndex ] == searchSubStr[ searchIndex ])
      {
        //increment index
         internalIndex++; searchIndex++;

         // check for null character
        if (searchSubStr[searchIndex] == NULL_CHAR )
          {
            //return success
            return masterIndex;

          }
       }

       //increment
     masterIndex++;
     }
     //return failure
     return SUBSTRING_NOT_FOUND;
   }

/*
fnction name: setStrToLowerCase
Algorithm: iterates through string, set all upper case letters to lower
          case without changing any other characters
precondition: given C-style test string, having a null character ('\0')
             at the end string parameter and given serach string with a null character
          ('\n') at the lower string that string 
postcondition: all upper case letters in given string are sert to lower case;
           no change to any other characters
Exception: limit on string loop in case incorrect string format
NOte: copy of source string is made internally to protect from aliasing
*/
void setStrToLowerCase( char *destStr, char *sourceStr )
   {
    //initialize function.variables
     int strLen = getStringLength( sourceStr );
     char *tempStr = (char *) malloc( strLen + 1);

     int index = 0;

     //copyString 
       //function: copyString
     copyString( tempStr, sourceStr );

     // loop not null character
    while( index < MAX_STR_LEN && tempStr[ index ] != NULL_CHAR )
    {
      // assign to temp
      destStr[ index ] = setCharToLowerCase( tempStr[ index ] );

      //increment
      index++;
       
       // assign tonull chara
      destStr[ index ] = NULL_CHAR; 

   }

   // free temp
      //function: free
    free( tempStr);

   }

/*
function name: setCharToLowerCase
Algorith: find charcters
precondition: testcchar
postcondition: return string with lower case
Exception:
Note:
*/

char setCharToLowerCase( char testChar )
   {
    // check 
   if( testChar >= 'A' && testChar <= 'Z')
     
    {
      // assign 
      testChar = (char) (testChar - 'A' + 'a');
    }

   return testChar;
   }

/*
function name: getLineTo
Algorith: finds given text in file, skipping white space if specified
        stops search at given charceter
precondition: file pointer, adequete memort, stop character and length
postcondition: ignores leading
Exception: return INCOMPELET_FILE_ERR IF NO VALID FOUND
      returns NO_ERR 
Note: none
*/
int getLineTo( FILE *filePtr, int bufferSize, char stopChar,
      char *buffer, Boolean omitLeadingWhiteSpace )

   {
    //initialize variables
    int charIndex = 0;
    int statusReturn = NO_ERR;

    Boolean bufferSizeAvailable = True;
    int charAsInt;

    //get first character/
      //function: charAsInt
    charAsInt = fgetc( filePtr );

    //loop till firue , find space not stop chjar
    while( omitLeadingWhiteSpace == True &&
    charAsInt != (int) stopChar && charIndex < bufferSize
     && charAsInt <= (int) SPACE )

    {
      // get next character
          // function; charAsInt
     charAsInt = fgetc( filePtr );
    }
    
    //loop
    while( charAsInt != (int) stopChar && bufferSizeAvailable == True )
   
    {
      //check is end is true
      // function: isEndOffile
    if( isEndOfFile( filePtr ) == True )
     {

      // return incomplete error
      return INCOMPLETE_FILE_ERR;
      }
      //check greter tha n
     if ( charAsInt >= (int) SPACE )
       {
        buffer[ charIndex ] = (char) charAsInt;

        //increment
     charIndex++;
        }

        // assign to null character
       buffer[ charIndex ] = NULL_CHAR;

       // check beffer size
       if( charIndex < bufferSize -1 )
     {
        //  get next character
        charAsInt = fgetc( filePtr );
     }
    
     else
       {
      bufferSizeAvailable =False;
      statusReturn = INPUT_BUFFER_OVERRUN_ERR;
      }
    }

    return statusReturn;
  }


/*
function name: isEndOfFile
Algorith: finds giv
precondition: file 
postcondition: iretun success failureg
Exception:  none
Note: none
*/

Boolean isEndOfFile( FILE *filePtr )
{

  // open file if nor equal zero
  if ( feof( filePtr ) != 0 )
   {
    // return true
    return True; 
    }

    // return failure
  return False;
  }

















































