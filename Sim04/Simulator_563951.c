
#ifndef RUN_SIMULATOR_NEW_C
#define RUN_SIMULATOR_NEW_C

// Header files ///////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdbool.h>
#include "Simulator_563951.h"
#include <pthread.h>
#include "SimTimer.h"
#include <math.h>

/**
function name: runSim
Algorithm: calculating the runSim difference 
    math operations and while loops.
    working with pounters 
precondition: ConfigDataType* pointer and OpCodeType* poiter 
	from configAcces andmetaData
postcondition: change state and print the proccess and state 
Exception: none
Note: use this for config
*/
PCB *runSimulator(ConfigDataType *config, OpCodeType *metaData)
{
    //initialize and create a PCBCurrent
    char *timeStr = (char *)(malloc(sizeof(char)));
    PCB *PCBCurrent;
    int runTime;
    pthread_t tid;

    //access timer and print out system starts
    accessTimer(ZERO_TIMER, timeStr);
    printf("%s, OS: System Start\n", timeStr);
    accessTimer(LAP_TIMER, timeStr);
    printf("%s OS: Create Process Control Blocks\n", timeStr);
    //Initialize process
    PCBCurrent = LinkedListMaker(config, metaData);
    // access timer and print new state
    accessTimer(LAP_TIMER, timeStr);
    printf("%s OS: All Processes initialized in New state\n", timeStr);

    // PCB initialization Add somethin
    PCB *PCBHead = PCBCurrent;
    // initialized buffer for sprintf usesage to store data
    char buffer[50];

    //checking ready state or not loop
    while (PCBCurrent->next != NULL)
    {
        // set PCBCurrent state to READY
        PCBCurrent->state = READY;
        // go to next node
        PCBCurrent = PCBCurrent->next;
    }
    // set the state to Ready
    PCBCurrent->state = READY;
    // set the PCBCurrent to PCBHead for another usage
    PCBCurrent = PCBHead;
    //get the next process
    //function: GetProcess
    PCBCurrent = GetProcess(PCBHead, config, metaData);
    //print out the Ready state
    accessTimer(LAP_TIMER, timeStr);
    printf("%s OS: All Processes now set in Ready state\n", timeStr);

    // while loop iterate if PCBCurrent  not null
    while (PCBCurrent != NULL)
    {
        //printing out selection process etc
        accessTimer(LAP_TIMER, timeStr);
        sprintf(buffer, " %s, OS: processes %d selected with %d ms remaining  \n", timeStr, PCBCurrent->Pid, PCBCurrent->timeRemaining);
        printf("%s", buffer);
        // set current state to running
        PCBCurrent->state = RUNNING;

        accessTimer(LAP_TIMER, timeStr);
        sprintf(buffer, "%s, OS: Process %d set in RUNNING state \n ", timeStr, PCBCurrent->Pid);
        printf("%s", buffer);
        printf("\n");

        // move to the next node
        PCBCurrent->OpCodeCurrent = PCBCurrent->OpCodeCurrent->next;

        // while loop to iterate if the pcb not at the end
        while (PCBCurrent->OpCodeCurrent != PCBCurrent->OpCodeEnd)
        {
            // switch cases for each opLetter
            char codeLetter = PCBCurrent->OpCodeCurrent->opLtr;

            //Switch case to test each opLtr
            switch (codeLetter)
            {

            case 'I':
            case 'O':

                //print out the starting of the opLtr
                accessTimer(LAP_TIMER, timeStr);
                sprintf(buffer, "%s, Process %d, %s %c started \n ", timeStr, PCBCurrent->Pid,
                        PCBCurrent->OpCodeCurrent->opName, codeLetter);
                printf("%s", buffer);
                //access the adress
                int *spiner = &runTime;
                void *spinParam = (void *)spiner;

                // calculate the run time
                runTime = (config->ioCycleRate) * (PCBCurrent->OpCodeCurrent->opValue);

                ///runTimer(runTime);
                //call the thread pthread_create
                pthread_create(&tid, NULL, runTimerT, spinParam);

                //check for NON-Preemptive
                if (config->cpuSchedCode == CPU_SCHED_SJF_N_CODE ||
                    config->cpuSchedCode == CPU_SCHED_FCFS_N_CODE)
                {
                    //join the thread thread_join
                    pthread_join(tid, NULL);
                    // display action complete
                    accessTimer(LAP_TIMER, timeStr);
                    sprintf(buffer, "%s, Process %d, %s, %c ended \n ", timeStr, PCBCurrent->Pid,
                            PCBCurrent->OpCodeCurrent->opName, codeLetter);
                    printf("%s", buffer);
                }
                break;

            case 'M':

                //call access manager
                //accessMemoryMgr(config, metaData);

                break;

            case 'P':

                //display starting
                accessTimer(LAP_TIMER, timeStr);
                sprintf(buffer, "%s, Process %d, %s %c started \n ", timeStr, PCBCurrent->Pid,
                        PCBCurrent->OpCodeCurrent->opName, PCBCurrent->OpCodeCurrent->opLtr);
                printf("%s", buffer);

                // set premptive flag boolean
                bool pFlag, interupt;

                //check for premptive
                switch (config->cpuSchedCode)
                {

                case CPU_SCHED_SRTF_P_CODE:
                case CPU_SCHED_FCFS_P_CODE:
                case CPU_SCHED_RR_P_CODE:

                    //call interrupt manager
                    printf("\n");
                    pFlag = true;
                    //PCBCurrent = PCBCurrent->next;
                    //return pFlag;
                    break;
                }
                //calculate runtime
                runTime = config->procCycleRate * PCBCurrent->OpCodeCurrent->opValue;
                //spin timer
                runTimer(runTime);

                //check if premptive and cycle time greater than 0
                while (pFlag && (config->quantumCycles > 0))
                {
                    //call interuptManager();
                    accessTimer(LAP_TIMER, timeStr);
                    sprintf(buffer, "%s, Process %d, %s %c ended \n ", timeStr, PCBCurrent->Pid,
                            PCBCurrent->OpCodeCurrent->opName, PCBCurrent->OpCodeCurrent->opLtr);
                    printf("%s", buffer);
                    //

                    interupt = true;
                    pFlag = false;

                    //PCBCurrent = PCBCurrent->next;
                }

                //check for interupt if i was true
                if (interupt)
                {
                    accessTimer(LAP_TIMER, timeStr);
                    sprintf(buffer, "%s, Process %d,is set BLOCKED state \n ", timeStr, PCBCurrent->Pid);
                    printf("%s", buffer);

                    //PCBCurrent = GetProcess(PCBHead, config, metaData);
                }

                // check for interrupt called
                //check for not np flag

                if (!pFlag)
                {
                    //PCBCurrent->OpCodeCurrent->opName
                    // retrun remaining cycletime to process

                    accessTimer(LAP_TIMER, timeStr);
                    sprintf(buffer, "%s, Process %d, %s %c ended \n ", timeStr, PCBCurrent->Pid,
                            PCBCurrent->OpCodeCurrent->opName, PCBCurrent->OpCodeCurrent->opLtr);
                    printf("%s", buffer);
                    //runTime -= config->procCycleRate * PCBCurrent->OpCodeCurrent->opValue;;
                }

                break;

            case 'W':
                //call idle function

                break;
            }

            // calculate PCBCurrent time remaining
            PCBCurrent->timeRemaining -= runTime;
            // fo to next opCode
            PCBCurrent->OpCodeCurrent = PCBCurrent->OpCodeCurrent->next;
        }
        //go to EXIT state
        PCBCurrent->state = EXIT;
        printf("\n");
        //display exit information
        accessTimer(LAP_TIMER, timeStr);
        sprintf(buffer, "%s, OS: Process %d ended and set in EXIT (%d) state \n ", timeStr, PCBCurrent->Pid, PCBCurrent->state);

        printf("%s", buffer);
        //PCBCurrent = PCBCurrent->next;
        PCBCurrent = GetProcess(PCBHead, config, metaData);
    }

    accessTimer(LAP_TIMER, timeStr);
    sprintf(buffer, "%s, System stop\n ", timeStr);
    printf("%s", buffer);
    sprintf(buffer, "End simulation - complete\n ");
    printf("%s", buffer);
    sprintf(buffer, "==========================\n ");

    printf("%s", buffer);

    // clear memory
    //free(PCBCurrent);

    return NULL;
}

/**
function name: LinkedListMaker
Algorithm: calculating the LinkedListMaker difference 
    math operations and while loops.
    working with pounters 
precondition: ConfigDataType* pointer and OpCodeType* poiter 
	from configAcces andmetaData
postcondition: make adn return linkedlist  
Exception: none
Note: use this for config
*/

//MDCurrent
//pid, = int
PCB *LinkedListMaker(ConfigDataType *config, OpCodeType *metaData)
{

    // md is a start
    // initialize LLHEAD
    PCB *LLhead = NULL;
    //INITIALIZE newPCB
    PCB *newPCB = NULL;
    // INItialize CurrentPCB
    PCB *CurrentPCB = NULL;
    // CREATE A LINKEDLIST
    //PCB* Head = LinkedListMaker(config, metaData);
    //initialize pidcounter
    int PidCounter = 0;

    // move form current to next node
    OpCodeType *MDCurrent = metaData;
    MDCurrent = MDCurrent->next; // skip down s(stat)

    // calculate Pmultiplier and IOMultiplier
    int Pmultiplier = config->procCycleRate;
    int IOMultiplier = config->ioCycleRate;
    //int Mmultiplier = config->memAvailable;
    //int cycleTime = Pmultiplier + IOMultiplier;
    //memAvailable

    // while loop iterate if command letter no S
    while (MDCurrent->opLtr != 'S')
    {
        // if condition
        if (MDCurrent->opLtr == 'A' && (compareString(MDCurrent->opName, "start") == STR_EQ))
        {

            // CReate a node
            newPCB = nodeMaker(MDCurrent, PidCounter, Pmultiplier, IOMultiplier);
            // if condition the head is empty
            if (LLhead == NULL)
            {

                //set LLhead to newPCB
                LLhead = newPCB;
            }

            else
            {
                // CurrentPCB
                CurrentPCB = LLhead;

                // next is ot null
                while (CurrentPCB->next != NULL)
                {
                    CurrentPCB = CurrentPCB->next;
                }
                //update the CurrentPCB
                CurrentPCB->next = newPCB;
            }
            //update the counter
            PidCounter++;
            //update newPCB
            newPCB = NULL;
            //update MDCurrent
        }
        MDCurrent = MDCurrent->next;
    }
    //return LLhead
    return LLhead;
}

/**
function name: nodeMaker
Algorithm: calculating the nodeMaker difference 
    math operations and while loops.
    working with pounters and integers 
precondition: integer Pid, integer pmultiplier and IOMultiplier
		 and OpCodeType* poiter 
	from configAcces andmetaData
postcondition: make adn return node  
Exception: none
Note: use this for config
*/

PCB *nodeMaker(OpCodeType *MDCurrent, int Pid, int Pmultiplier, int IOMultiplier)
{

    // create a PCB
    PCB *indvPCB = (PCB *)malloc(sizeof(PCB));
    // indvPCB pid, next and
    indvPCB->Pid = Pid;
    indvPCB->OpCodeHead = MDCurrent;
    indvPCB->OpCodeCurrent = MDCurrent;
    indvPCB->OpCodeEnd = NULL;
    indvPCB->timeRemaining = 0;
    indvPCB->next = NULL;
    //change state
    indvPCB->state = NEW;

    //while loop iterating through
    while ((compareString(MDCurrent->opName, "end") != STR_EQ) || MDCurrent->opLtr != 'A')
    {
        //conditional if P
        if (MDCurrent->opLtr == 'P')
        {
            indvPCB->timeRemaining += MDCurrent->opValue * Pmultiplier;
        }

        //conditional if

        //conditional if for IO
        else if (MDCurrent->opLtr == 'I' || MDCurrent->opLtr == 'O')
        {
            indvPCB->timeRemaining += MDCurrent->opValue * IOMultiplier;
        }

        //go to the next
        MDCurrent = MDCurrent->next;
    }
    //update MDCurrent
    indvPCB->OpCodeEnd = MDCurrent;
    //return
    return indvPCB;
}

/**
function name: GetProcess
Algorithm: calculating the process for cases of premptive and non-premptive 
precondition: config file and metadata file
postcondition: make adn return of curent PCP 
Exception: none
Note: calling this function will give us the current PCB
*/

PCB *GetProcess(PCB *PCBHead, ConfigDataType *config, OpCodeType *metaData)
{
    //initialize VARIABLES
    PCB *PCBptr = PCBHead;
    PCB *meanTimePtr;
    int time;

    // check if pointer is not null or it is not on rady state
    while (PCBptr != NULL && PCBptr->state != READY)
    {
        //go to next pointer
        PCBptr = PCBptr->next;
    }
    // another pointer we work on.to compare both.
    meanTimePtr = PCBptr;
    static int workingPid = 0;
    // check if the second pointer in null
    if (meanTimePtr == NULL)
    {
        return NULL;
    }

    // set the time
    time = meanTimePtr->timeRemaining;
    PCBptr = PCBHead;

    //workingPid = PCBptr->Pid;
    // master loop
    while (PCBptr != NULL)
    {
        // switch CPU Schedule
        // check for FCFS-N
        switch (config->cpuSchedCode)
        {

        case CPU_SCHED_FCFS_N_CODE:

            if (PCBptr->state == READY)
            {
                //meanTimePtr = PCBptr;
                return PCBptr;
            }

            break;

        case CPU_SCHED_SJF_N_CODE:
        case CPU_SCHED_SRTF_P_CODE:
            //CHECK FOR SJF-N
            if (PCBptr->state != EXIT && PCBptr->timeRemaining < time)
            {
                //GET THE LOWEST TIME REMAINING
                time = PCBptr->timeRemaining;
                meanTimePtr = PCBptr;

                return meanTimePtr;
            }

            // CHECK IF THE pointer is null
            if (PCBptr->next == NULL)
            {
                PCBptr = meanTimePtr;
                return PCBptr;
            }

            break;

            //case for rrp
        case CPU_SCHED_RR_P_CODE:

            if (PCBptr->state == READY && PCBptr->Pid >= workingPid)
            {
                //meanTimePtr = PCBptr;
                workingPid = PCBptr->Pid;
                return PCBptr;
                //PCBptr = PCBptr->next;
            }
            if (PCBptr == NULL)
            {
                workingPid = 0;
                PCBptr = PCBHead;
                return PCBHead;
            }

            break;

            //case for FCFSP

        case CPU_SCHED_FCFS_P_CODE:

            // take the next process with the next pID
            while (PCBptr->Pid <= workingPid)
            {
                PCBptr->state = EXIT;
                PCBptr = PCBptr->next;
            }

            workingPid = PCBptr->Pid;
            return PCBptr;
            //meanTimePtr = PCBptr;
            //return meanTimePtr;

            break;
        }

        //meanTimePtr = meanTimePtr->next;
        //meanTimePtr = meanTimePtr->next;
        PCBptr = PCBptr->next;
    }

    return NULL;
}

/**
Function name: accessMemoryMgr
This one is commented out because it does not work completely
precondion: config and metadata
postcondition: it will do for 'm' how memory allocates and handles for
        error
algorithm: use modulo and math to caluclate
*/

/*
PCP* accessMemoryMgr(ConfigDataType *config, OpCodeType *metaData)
{
    //initialize
    PCB *PCBCurrent;
    char *timeStr;
    char buffer[50];

    accessTimer(ZERO_TIMER, timeStr);

    int vInteger, div, off, base, offsetBase, mmuSpace;
    // initialize a linked list
    //PCBCurrent = LinkedListMaker(config, metaData);
    //PCB *PCBCurrent = (PCP *)malloc(sizeof(PCB));
    //do some math to calculate the memory space and offset, base
    vInteger = PCBCurrent->OpCodeCurrent->opValue;
    div = 10000;
    off = vInteger % div;  //BBBB
    base = vInteger / div; //AAAA
    offsetBase = base + off;
    mmuSpace = (config->memAvailable);

   // PCB *linkedlist = (PCB *)malloc(sizeof(PCB));

    //call accesstimer and print
    accessTimer(LAP_TIMER, timeStr);
    sprintf(buffer, "%s, Process %d, MMU attempt to %s %d/%d\n ", timeStr, PCBCurrent->Pid,
            PCBCurrent->OpCodeCurrent->opName, base, off);
    printf("%s", buffer);

    // call memeroy mangement unit
    if (PCBCurrent->OpCodeCurrent->opName == 'allocate')
    {
        // NOT WORKING 100%
        if (offsetBase < mmuSpace)
        {
            //ADD TO MEMORY

            accessTimer(LAP_TIMER, timeStr);
            sprintf(buffer, "%s, Process %d, MMU success to %s\n ", timeStr, PCBCurrent->Pid,
                    PCBCurrent->OpCodeCurrent->opName);
            printf("%s", buffer);
        }
        else
        {
            //PCBCurrent = PCBCurrent -> next;
            accessTimer(LAP_TIMER, timeStr);
            sprintf(buffer, "%s, Process %d, MMU failed %s\n ", timeStr, PCBCurrent->Pid,
                    PCBCurrent->OpCodeCurrent->opName);
            printf("%s", buffer);
            //Process 0 e
            accessTimer(LAP_TIMER, timeStr);
            sprintf(buffer, "%s, Process %d, experiences segmentation fault\n ", timeStr, PCBCurrent->Pid);
            printf("%s", buffer);
        }
    }

    else if (compareString(PCBCurrent->OpCodeCurrent->opName, "access") == STR_EQ)
    {
        // NOT WORKING 100%
        int allocateMem = 0;
        if (offsetBase < allocateMem)
        {
            //ADD TO MEMORY
            accessTimer(LAP_TIMER, timeStr);
            sprintf(buffer, "%s, Process %d, MMU success to %s\n ", timeStr, PCBCurrent->Pid,
                    PCBCurrent->OpCodeCurrent->opName);
            printf("%s", buffer);
        }
        else
        {
            //PCBCurrent = PCBCurrent -> next;
            accessTimer(LAP_TIMER, timeStr);
            sprintf(buffer, "%s, Process %d, MMU failed %s\n ", timeStr, PCBCurrent->Pid,
                    PCBCurrent->OpCodeCurrent->opName);
            printf("%s", buffer);
            //Process 0 e
            accessTimer(LAP_TIMER, timeStr);
            sprintf(buffer, "%s, Process %d, experiences segmentation fault\n ", timeStr, PCBCurrent->Pid);
            printf("%s", buffer);
        }
    }
    return NULL;
}
*/
#endif