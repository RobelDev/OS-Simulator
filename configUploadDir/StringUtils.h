//header files
#include <stdio.h>
#include <stdlib.h>

typedef enum { False, True} Boolean;
typedef enum { NO_ERR, INCOMPLETE_FILE_ERR,
     INPUT_BUFFER_OVERRUN_ERR } StringManipCode;
// create global constant - accross file

extern const int MAX_STR_LEN;
extern const int STD_STR_LEN;
extern const int SUBSTRING_NOT_FOUND ;
extern const int STR_EQ;
extern const char SPACE;
extern const char NULL_CHAR;
extern const char SPACE;
extern const char COLON;
extern const char PERIOD;
extern const Boolean IGNORE_LEADING_WS;
extern const Boolean ACCEPT_LEADING_WS;

//function prototypes
int getStringLength( char *testStr );
void copyString( char *destination,  char *source );
void concatenateString( char *destination, char *source);
int compareString( char *oneSTr, char *otherStr);
void getSubString( char *desStr, char *sourceStr, int startIndex, int endIndex);

int findSubString( char *testStr, char *searchSubStr );
void setStrToLowerCase( char *destStr, char *sourceStr );


char setCharToLowerCase( char testChar );
int getLineTo( FILE *fileptr, int bufferSize, char stopChar,
      char *buffer, Boolean omitLeadingWhiteSpace );
Boolean isEndOfFile( FILE *filePtr );

