
#ifndef SIMILATOR_C
#define SIMILATOR_C

// Header files ///////////////////////////////////////////////////////////////

#include "Simulator.h"
#include <pthread.h>
#include "SimTimer.h"

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
PCB* runSim(ConfigDataType* config, OpCodeType* metaData)
{
	char* timeStr;
	accessTimer(ZERO_TIMER, timeStr);
	//initialize and create a PCBCurrent
	PCB* PCBCurrent;
	
	printf("%s, OS: System Start\n", timeStr );
	accessTimer(LAP_TIMER, timeStr);
	printf("%s OS: Create Process Control Blocks\n", timeStr );
	PCBCurrent = LinkedListMaker(config, metaData);
	accessTimer(LAP_TIMER, timeStr);

	printf("%s OS: All Processes initialized in New state\n", timeStr );
	//printf("huh\n");
	pthread_t tid;
	int runTime;
	// PCB initialization Add somethin
	PCB* PCBHead = PCBCurrent;
	PCBCurrent->state = READY;


	char buffer[50];
	

	//printf("Meme\n");
	// use while loop to iterate through the nodes
	while (PCBCurrent->next != NULL)
	{
		
		// set PCBCurrent state to READY
		PCBCurrent->state = READY;
		
		// go to next node
		PCBCurrent = PCBCurrent->next;
		// print out the state
		
	
		}

	
	
	//accessTimer(LAP_TIMER, timeStr);
	
	//accessTimer(LAP_TIMER, timeStr);
	accessTimer(LAP_TIMER, timeStr);
	printf("%s OS: All Processes now set in Ready state\n", timeStr );
	PCBCurrent = PCBHead;

	//get the process
	//function: GetProcess
	//PCBCurrent = GetProcess(PCBHead);
	// while loop iterate if PCBCurrent  not null
	while (PCBCurrent != NULL)
	{
		//printing out selection process etc
		accessTimer(LAP_TIMER, timeStr);
		sprintf(buffer," %s, OS: processes %d selected with %d ms remaining  \n",timeStr, PCBCurrent->Pid, runTime);
		
		printf("%s", buffer);
			//======
		
		PCBCurrent -> state = RUNNING;

		accessTimer(LAP_TIMER, timeStr);	
		sprintf(buffer,"%s, OS: Process %d set in RUNNING (%d) state \n ", timeStr, PCBCurrent->Pid, PCBCurrent->state);
			
		printf("%s", buffer);
		//printf("%s, OS: All processes now set in %d state\n",timeStr, PCBCurrent->state);
		//accessTimer(LAP_TIMER, timeStr);
		

		printf("\n");
		// set current state to running
		
		// move to the next node

		PCBCurrent->OpCodeCurrent = PCBCurrent->OpCodeCurrent->next;
		
		// while loop to iterate if the pcb not at the end
	//printf("f, OS: All processes now set in %s state", PCBCurrent->state);
		while (PCBCurrent->OpCodeCurrent != PCBCurrent->OpCodeEnd)
		{
			accessTimer(LAP_TIMER, timeStr);
			sprintf(buffer, "%s, Process %d, %s, %c started \n ", timeStr, PCBCurrent->Pid, 
				PCBCurrent->OpCodeCurrent->opName, PCBCurrent->OpCodeCurrent->opLtr);

			
			printf("%s", buffer);

			//if the coomand lettr is P
			if (PCBCurrent->OpCodeCurrent->opLtr == 'P')
			{
				

				runTime = config->procCycleRate * PCBCurrent->OpCodeCurrent->opValue;
				runTimer(runTime);
			}

			//if the coomand lettr is I or O
			else if (PCBCurrent->OpCodeCurrent->opLtr == 'I' || PCBCurrent->OpCodeCurrent->opLtr == 'O')
			{
				//calculate runtime
				
				runTime = (config->ioCycleRate ) * (PCBCurrent->OpCodeCurrent->opValue);
				//access the adress
				int* intParam = &runTime;
				void* dartParam = (void*) intParam;
				// call pthread_create
				pthread_create(&tid, NULL, runTimerT, dartParam);
				//call thread_join
				pthread_join(tid, NULL);

				//printf("%s, OS: Process %d, %s \n ", timeStr, PCBCurrent->Pid, PCBCurrent->OpCodeCurrent->opName);

				//accessTimer(LAP_TIMER, timeStr);

			}
			accessTimer(LAP_TIMER, timeStr);
			sprintf(buffer, "%s, Process %d, %s, %c ended \n ", timeStr, PCBCurrent->Pid, 
				PCBCurrent->OpCodeCurrent->opName, PCBCurrent->OpCodeCurrent->opLtr);

			
			printf("%s", buffer);
					
			// calculate PCBCurrent time remaining 
			PCBCurrent->timeRemaining -= runTime;
			PCBCurrent->OpCodeCurrent = PCBCurrent->OpCodeCurrent->next;

			}
			/*
			accessTimer(LAP_TIMER, timeStr);
			sprintf(buffer,"%s, Process %d, %s  \n ", timeStr, PCBCurrent->Pid, PCBCurrent->OpCodeCurrent->opName);
			
			printf("%s", buffer);
			//printf("99999\n");
			//printf("\n");
			*/
			PCBCurrent->state = EXIT;

			printf("\n");
			accessTimer(LAP_TIMER, timeStr);
 			sprintf(buffer,"%s, OS: Process %d ended and set in EXIT (%d) state \n ", timeStr, PCBCurrent->Pid, PCBCurrent->state);
			
			printf("%s", buffer);
			PCBCurrent = PCBCurrent->next;
		
	}
	accessTimer(LAP_TIMER, timeStr);
			sprintf(buffer, "%s, System stop\n ", timeStr);
			printf("%s", buffer);
			sprintf(buffer, "End simulation - complete\n ");
			printf("%s", buffer);
			sprintf(buffer, "==========================\n ");
			printf("%s", buffer);


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
PCB* LinkedListMaker(ConfigDataType* config, OpCodeType* metaData)
{
	
	// md is a start
	// initialize LLHEAD
	PCB* LLhead = NULL;
	//INITIALIZE newPCB
	PCB* newPCB = NULL;
	// INItialize CurrentPCB
	PCB* CurrentPCB = NULL;
	// CREATE A LINKEDLIST
	//PCB* Head = LinkedListMaker(config, metaData);
	//initialize pidcounter
	int PidCounter = 0;

	// move form current to next node
	OpCodeType* MDCurrent = metaData;
	MDCurrent = MDCurrent->next; // skip down s(stat)

	// calculate Pmultiplier and IOMultiplier
	int Pmultiplier = config->procCycleRate;
	int IOMultiplier = config->ioCycleRate;

	// while loop iterate if command letter no S
	while (MDCurrent->opLtr != 'S')
	{
		// if condition
		if (MDCurrent->opLtr == 'A' && (compareString(MDCurrent->opName,"start") == STR_EQ))
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
	
	//return NULL;
	
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

PCB* nodeMaker(OpCodeType* MDCurrent, int Pid, int Pmultiplier, int IOMultiplier)
{
	// create a PCB
	PCB* indvPCB = (PCB*) malloc(sizeof (PCB));
	// indvPCB pid, next and
	indvPCB -> Pid = Pid;
	indvPCB -> OpCodeHead = MDCurrent;
	indvPCB -> OpCodeCurrent = MDCurrent;
	indvPCB -> OpCodeEnd = NULL;
	indvPCB -> timeRemaining = 0;
	indvPCB -> next = NULL;
	//change state
	indvPCB -> state = NEW;

	//while loop iterating through
	while ( (compareString(MDCurrent->opName,"end") != STR_EQ) || MDCurrent->opLtr != 'A' )
	{
		//conditional if
		if (MDCurrent->opLtr == 'P' )
		{
			indvPCB->timeRemaining += MDCurrent->opValue * Pmultiplier;
		}

		//conditional if 
		else if (MDCurrent->opLtr == 'I' || MDCurrent->opLtr == 'O' )
		{
			indvPCB->timeRemaining += MDCurrent -> opValue * IOMultiplier;
		}

		//conditional if
		MDCurrent = MDCurrent->next;
	}
	//update MDCurrent
	indvPCB-> OpCodeEnd = MDCurrent;
	//return 
	return indvPCB;
}

PCB* GetProcess(PCB* PCBHead)
{
	PCB* PCBptr = PCBHead;

	while (PCBptr != NULL)
	{
		if(PCBptr->state == READY)
		{
			return PCBptr;
		}
		PCBptr = PCBptr->next;
	}
	return NULL;
	
}


#endif
