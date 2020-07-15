//header files
#include "StringUtils.h"

//global constants
const int MAX_STR_LEN = 200;
const int  STD_STR_LEN = 80;
const int SUBSTRING_NOT_FOUND = -101;
const char NULL_CHAR = '\0';
const char SPACE = ' ';
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
    int index = 0;

    while( index<MAX_STR_LEN && source[ index] != NULL_CHAR )
     {
       destination[ index ] = source[ index ]; 
       index++;

    destination[ index ] = NULL_CHAR; 
      }
     
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
    int destIndex = getStringLength( destination );
    int sourceIndex = 0;

    while( sourceIndex < MAX_STR_LEN && source[ sourceIndex] != NULL_CHAR )
     {
       destination[ destIndex ] = source[ sourceIndex ]; 
       sourceIndex++; destIndex++;

    destination[ destIndex ] = NULL_CHAR; 
      }
     

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
    int index = 0;
    int difference;

    while( index<MAX_STR_LEN && oneStr[ index] != NULL_CHAR 
            && otherStr[ index ] != NULL_CHAR)
     {
       difference = oneStr[ index ] - otherStr[ index ];
       if ( difference != 0 )
      {
       return difference;
      }
      index++;
        
      }

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
    int sourceStrLen = getStringLength( sourceStr );
    int destIndex = 0;
    int sourceIndex = startIndex;
    char *tempSourceStr;
    // temproray

    if (startIndex >= 0 && startIndex <= endIndex && endIndex < sourceStrLen )
    {
     tempSourceStr = (char * ) malloc( sourceStrLen + 1 );
     copyString( tempSourceStr, sourceStr );
     
    while( sourceIndex <= endIndex )
     {
     destStr[destIndex ] = tempSourceStr[ sourceIndex ];
    
    destIndex++, sourceIndex++;

    destStr[ destIndex ] = NULL_CHAR; 
    }
     //end loop
      free( tempSourceStr );
   }
     else 
       {
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

    int testStrLen = getStringLength( testStr );
    int masterIndex = 0;
     
    int searchIndex, internalIndex;

    while( masterIndex < testStrLen )
    {
    internalIndex = masterIndex;
    searchIndex = 0;
    
    while( internalIndex <= testStrLen 
    && testStr[ internalIndex ] == searchSubStr[ searchIndex ])
      {
         internalIndex++; searchIndex++;
        if (searchSubStr[searchIndex] == NULL_CHAR )
          {
            return masterIndex;

          }
       }
     masterIndex++;
     }
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
     int strLen = getStringLength( sourceStr );
     char *tempStr = (char *) malloc( strLen + 1);

     int index = 0;

     copyString( tempStr, sourceStr );
    while( index < MAX_STR_LEN && tempStr[ index ] != NULL_CHAR )
    {
    destStr[ index ] = setCharToLowerCase( tempStr[ index ] );
    index++;
     
    destStr[ index ] = NULL_CHAR; 

   }
    free( tempStr);

   }

/*
function name: setCharToLowerCase

--
---
--
*/

char setCharToLowerCase( char testChar )
   {
   if( testChar >= 'A' && testChar <= 'Z')
     
    {
      testChar = (char) (testChar - 'A' + 'a');
    }

   return testChar;
   }

/*
function name: getLineTo 

*/
int getLineTo( FILE *filePtr, int bufferSize, char stopChar,
      char *buffer, Boolean omitLeadingWhiteSpace )

   {
    int charIndex = 0;
    int statusReturn = NO_ERR;

    Boolean bufferSizeAvailable = True;
    int charAsInt;

    charAsInt = fgetc( filePtr );

    while( omitLeadingWhiteSpace == True &&
    charAsInt != (int) stopChar && charIndex < bufferSize
     && charAsInt <= (int) SPACE )

    {
     charAsInt = fgetc( filePtr );
    }
    
    while( charAsInt != (int) stopChar && bufferSizeAvailable == True )
   
    {
    if( isEndOfFile( filePtr ) == True )
     {
      return INCOMPLETE_FILE_ERR;
      }
     if ( charAsInt >= (int) SPACE )
       {
        buffer[ charIndex ] = (char) charAsInt;

     charIndex++;
        }
       buffer[ charIndex ] = NULL_CHAR;

       if( charIndex < bufferSize -1 )
     {
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
function name: isEndOf
*/

Boolean isEndOfFile( FILE *filePtr )
{

  if ( feof( filePtr ) != 0 )
   {
    return True; 
    }

  return False;
  }

















































