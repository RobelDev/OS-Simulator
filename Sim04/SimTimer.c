#ifndef SIMTIMER_C
#define SIMTIMER_C

// Header files ///////////////////////////////////////////////////////////////

#include "SimTimer.h"
#include <pthread.h>

const char RADIX_POINT = '.';

/**
function name: runTimer
Algorithm: calculating the runtime difference 
    math operations and while loops.
precondition: integer parameter milliseconds
postcondition: get timeDifference 
Exception: none
Note: use this for config
*/

void runTimer(int milliSeconds)
    {
         // initialize and decalreition
        struct timeval startTime, endTime;
        int startSec, startUSec, endSec, endUSec;
        int uSecDiff, mSecDiff, secDiff, timeDiff;

        //get time of day
        //function: gettimeofday
        gettimeofday(&startTime, NULL);

        // get startSec and startUsec
        startSec = startTime.tv_sec;
        startUSec = startTime.tv_usec;

        // initialize timeDif
        timeDiff = 0;

        // use while looopto iterate through
        while (timeDiff < milliSeconds)
        {
            //get time of day
                //function: gettimeofday
            gettimeofday(&endTime, NULL);

            // calculate endSec, end Usec, uSecDiff
            endSec = endTime.tv_sec;
            endUSec = endTime.tv_usec;
            uSecDiff = endUSec - startUSec;

            // conditional statemtn if uSecDiff is less than 0
            if (uSecDiff < 0)
            {
                // calculate uSecDiff
                uSecDiff = uSecDiff + 1000000;

                //calculare endSEC
                endSec = endSec - 1;
            }
            // update mSecDiff, secDiff, timeDiff
            mSecDiff = uSecDiff / 1000;
            secDiff = (endSec - startSec) * 1000;
            timeDiff = secDiff + mSecDiff;
        }

    }

//for pthread
/**
function name: runTimer
Algorithm: calculating the runtime difference 
    math operations and while loops. 
precondition: can accept any pointer
postcondition: get timeDifference 
Exception: none
Note: use this for config
*/
void* runTimerT(void* timerT)
{
    // initialize and decalreition
    // change the pointer back to int
    int* intParam = (int*)timerT;
    int milliSeconds = *intParam;
    struct timeval startTime, endTime;
    int startSec, startUSec, endSec, endUSec;
    int uSecDiff, mSecDiff, secDiff, timeDiff;

    //get time of day
        //function: gettimeofday
    gettimeofday(&startTime, NULL);

    // get startSec and startUsec
    startSec = startTime.tv_sec;
    startUSec = startTime.tv_usec;

    // initialize timeDif
    timeDiff = 0;

    // use while looopto iterate through
    while (timeDiff < milliSeconds)
    {
        // get time of day
            // function: gettimeofday
        gettimeofday(&endTime, NULL);

        // calculate endSec, end Usec, uSecDiff
        endSec = endTime.tv_sec;
        endUSec = endTime.tv_usec;
        uSecDiff = endUSec - startUSec;

        // conditional statemtn if uSecDiff is less than 0
        if (uSecDiff < 0)
        {
            // calculate uSecDiff
            uSecDiff = uSecDiff + 1000000;

            //calculare endSEC
            endSec = endSec - 1;
        }

        // update mSecDiff, secDiff, timeDiff
        mSecDiff = uSecDiff / 1000;
        secDiff = (endSec - startSec) * 1000;
        timeDiff = secDiff + mSecDiff;
    }
    return  NULL;

}
/**
function name: accessTimer
Algorithm: using swich case to go through different cases and conditional 
        statements 
precondition: two arguements integer controlCode and character timeStr
postcondition: return fpTime which is a time kinda of stop watch
Exception: none
Note: none
*/

double accessTimer(int controlCode, char* timeStr)
{
    // initialaization and declaration
    static Boolean running = False;
    static int startSec = 0, endSec = 0, startUSec = 0, endUSec = 0;
    static int lapSec = 0, lapUSec = 0;
    struct timeval startData, lapData, endData;
    double fpTime = 0.0;

    // use switch to test controlCode
    switch (controlCode)
    {

    // case 1 if timer is zero
    case ZERO_TIMER:

        //get time of day
        //function: gettimeofday
        gettimeofday(&startData, NULL);
        //set running to true
        running = True;

        // get startSec and startUsec
        startSec = startData.tv_sec;
        startUSec = startData.tv_usec;

        //initialize fpTime, lapSec, lapUSec
        fpTime = 0.000000000;
        lapSec = 0.000000000;
        lapUSec = 0.000000000;

        //change time to strng
            //function: timeToString
        timeToString(lapSec, lapUSec, timeStr);
        break;
    //case lap-timer
    case LAP_TIMER:

        // conditionmal statement
        if (running == True)
        {
            //get time of day
        //function: gettimeofday
            gettimeofday(&lapData, NULL);

            // calculate lapSec and lapUSec
            lapSec = lapData.tv_sec;
            lapUSec = lapData.tv_usec;

            //calculate fpTime
            //function processTime
            fpTime = processTime(startSec, lapSec,
                startUSec, lapUSec, timeStr);
        }

        else
        {
            //set fpTime to 0
            fpTime = 0.000000000;
        }
        break;

        // case 3 STOP_TIMER
    case STOP_TIMER:
        //COnditional statement
        if (running == True)
        {
            //get time of day
        //function: gettimeofday
            gettimeofday(&endData, NULL);
            //set running to false
            running = False;

            //calculate endSec and endUSec
            endSec = endData.tv_sec;
            endUSec = endData.tv_usec;

            //calculate fpTime
            //function processTime
            fpTime = processTime(startSec, endSec,
                startUSec, endUSec, timeStr);
        }

        // assume timer not running
        else
        {
            fpTime = 0.000000000;
        }
        break;
    }

    //return fpTime
    return fpTime;
}

/**
function name: processTime
Algorithm: calculate proccessTime
precondition: five parameters double startSec, double endSec
    double startUSec, double endUsec and character pointer timeStr
postcondition: return process fpTime
Exception: none
Note: none
*/

double processTime(double startSec, double endSec,
    double startUSec, double endUSec, char* timeStr)
{
    //Initialize secDiff, uSecDiff, fpTime
    double secDiff = endSec - startSec;
    double uSecDiff = endUSec - startUSec;
    double fpTime;

    // calculate fpTime
    fpTime = (double)secDiff + (double)uSecDiff / 1000000;

    //conditional statement
    if (uSecDiff < 0)
    {
        // calculate uSecDiff, secDiff
        uSecDiff = uSecDiff + 1000000;
        secDiff = secDiff - 1;
    }
    // change time to string
        //function:timeToString
    timeToString(secDiff, uSecDiff, timeStr);
    //return fpTime
    return fpTime;
}


/**
function name: timrToString
Algorithm: change time to a string 
precondition: three parameters integer secTime, integer uSecTime
        and character pointer timeStr
postcondition: change time to a string
Exception: none
Note: none
*/
/* This is a bit of a drawn-out function, but it is written
   to force the time result to always be in the form x.xxxxxxx
   when printed as a string; this will not always be the case
   if the time is presented as a floating point number
*/
void timeToString(int secTime, int uSecTime, char* timeStr)
{
    //initialize
    int low, high, index = 0;
    char temp;

    //while loop to iterate 
    while (uSecTime > 0)
    {
        //calculate time at given index
        timeStr[index] = (char)((uSecTime % 10) + '0');
        uSecTime /= 10;

        //update index
        index++;

    }

    //while loop to iterate
    while (index < 6)
    {
        //set time at given index
        timeStr[index] = '0';
        //update index
        index++;
    }
    //set time at given index to constant
    timeStr[index] = RADIX_POINT;
    //update index
    index++;

    //conditional statement
    if (secTime < 10) // single digit in display
    {
        //calculate time at given index
        timeStr[index] = (char)(secTime % 10 + '0');
        //update index
        index++;
        //set time at given index to empty
        timeStr[index] = ' ';
        //update index
        index++;

        secTime = 0;
    }
    /*
        if( secTime == 0 )
           {
            timeStr[ index ] = '0';

            index++;
           }
    */
    // while loop to iterate 
    while (secTime > 0)
    {
        //calculate time at given index
        timeStr[index] = (char)(secTime % 10 + '0');

        secTime /= 10;
        ////update index
        index++;
    }
    // set timeStr
    timeStr[index] = '\0';

    low = 0; high = index - 1;

    // do while loop
    while (low < high)
    {
        //swap strings
        temp = timeStr[low];
        timeStr[low] = timeStr[high];
        timeStr[high] = temp;

        // update counter
        low++; high--;
    }
}

#endif // ifndef SIMTIMER_C