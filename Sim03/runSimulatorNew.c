
#ifndef SIMULATOR_563951_C
#define SIMULATOR_563951_C

// Header files ///////////////////////////////////////////////////////////////
#include <stdio.h>
#include "Simulator_563951.h"
#include <pthread.h>
#include "SimTimer.h"
#include <math.h>
#include "nodeMaker.h"


/*

PCB* GetProcess(PCB* PCBHead)
{
	PCB* PCBptr = PCBHead;
	PCB* meanTimePtr;
	int time;

	while (PCBptr != NULL && PCBptr->state != READY)
	{
		PCBptr = PCBptr->next;
		meanTimePtr = PCBptr;

	}

	time = PCBptr->timeRemaining;

	while (PCBptr != NULL)
	{

		if(PCBptr->state == READY && PCBptr->timeRemaining < time)
		{

			
			time = PCBptr->timeRemaining;
			meanTimePtr = PCBptr;
			printf("%d\n", time );

		}

		PCBptr = PCBptr->next;
	}



	return NULL;
	
}

*/
////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


/*
PCB* MemoryManagementUnit(PCB* PCBHead, ConfigDataType* config, OpCodeType* metaData)
{
	MemoryManagementUnit

	access granted denied conditions 
	take care over LAP

	print out in 

	if()

		else 

			esle if 
}
*/
////////
/*
PCB* (ConfigDataType* config, OpCodeType* metaData)
{
	PCB* PCBCurrent;
	PCBCurrent = setProcess(config, metaData);

	while(PCBCurrent != NULL)
	{
		if (PCBCurrent->state == READY) != NULL))
		{
			time = timeCompute

			timeCompute = PCBCurrent->timeRemaining;
			 PCBCurrent->timeRemaining; = ;
		}
	}

	//////////////////////////////////////////////////////////////////

	if (config->cpuSchedCode  == CPU_SCHED_FCFS_N_CODE)
	{
		return PCBCurrent;
	}

	{
		return PCBCurrent = setProcess(config, metaData);

	}
		PCBCurrent = GetProcess(PCBHead)
	//SELECT 
	//COMPARE THE READY PCBCurrentTHE SHORTEST TIME 

	//PCBREAD BY SPORT 
	//SORT
		.
}

PCBCurrent=sort(PCBCurrent->timeRemaining)

function = a function that finds the shortest time.

if()
	pcbready = shortest time pcb

MDCurrent

}

*/
///////CORECT ONEEEEE ////////////////////
/*

PCB* MemoryManagementUnit(PCB* PCBHead, ConfigDataType* config, OpCodeType* metaData)
{

	PCB* PCBptr;
	PCB* meanPtr

	
	//if( PCBCurrent-> OpCodeCurrent->opLtr == 'M' )
	//	{
			
		
		//int base1 = base;

		while (PCBptr != NULL && PCBptr->OpCodeCurrent->opLtr != 'M')
			{
				PCBptr = PCBptr->next;
			}

			meanPtr = PCBptr;

			if(meanPtr == NULL)
			{
				return NULL;
			}

			int vInteger = PCBCurrent->OpCodeCurrent->opValue;
		
		//int nDigits = floor(log10(abs(vInteger))) + 1;
			// inititalizze
		int div = 10000;
		//AAAABBBB

		int off = vInteger % div;     //BBBB
		int base = vInteger / div;   //AAAA
		int offsetBase = base + off;
		int mmuSpace = (config->memAvailable);
			PCBptr = PCBHead;

			while (PCBptr != NULL)
			{
		
		//base1 = offset;
		//PCBCurrent->OpCodeCurrent->opLtr = PCBCurrent->OpCodeCurrent->next;
			if(PCBCurrent->OpCodeCurrent->opName = 'allocate')
			{
					if (offsetBase < mmuSpace && prevAllocated && overlap )
					{
						int* memAllocate = (int*) malloc(offsetBase * sizeof (int));

						meanPtr = PCBptr;






						if(){  // access

						}

					}
		}

			
		else if
			{
				

				return false; // return error

			}

*/

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
PCB* runSimulator(ConfigDataType* config, OpCodeType* metaData)
{
	
	char *timeStr;
	
	//initialize and create a PCBCurrent
	PCB* PCBCurrent;
	accessTimer(ZERO_TIMER, timeStr);
	printf("%s, OS: System Start\n", timeStr );
	accessTimer(LAP_TIMER, timeStr);
	printf("%s OS: Create Process Control Blocks\n", timeStr );

	//MMU
	PCBCurrent = LinkedListMaker(config, metaData);
	//printf(PCBCurrent);
	accessTimer(LAP_TIMER, timeStr);

	printf("%s OS: All Processes initialized in New state\n", timeStr );
	//printf("huh\n");
	int runTime;
	pthread_t tid;
	
	//int pidcounter;


	// PCB initialization Add somethin
	PCB* PCBHead = PCBCurrent;
	PCBCurrent->state = READY;


	char buffer[50];
	//printf(getCpuSchedCode( timeStr ));
	//getCpuSchedCode( char *codeStr )

	//memor manager


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
		PCBCurrent = GetProcess(PCBHead, config, metaData);

		// while loop iterate if PCBCurrent  not null
		while (PCBCurrent != NULL)
		{
			
			//printing out selection process etc
			accessTimer(LAP_TIMER, timeStr);
			//runTime = 9842;
			sprintf(buffer," %s, OS: processes %d selected with %d ms remaining  \n",timeStr, PCBCurrent->Pid, PCBCurrent->timeRemaining);
			printf("%s", buffer);

			printf("PIDDDDDDDDDDDDDDDDD %d\n", PCBCurrent->Pid);
				//get pid counter
			// set current state to running
			PCBCurrent -> state = RUNNING;

			

			accessTimer(LAP_TIMER, timeStr);	
			sprintf(buffer,"%s, OS: Process %d set in RUNNING state \n ", timeStr, PCBCurrent->Pid);	
			printf("%s", buffer);
			printf("\n");
			// move to the next node
			PCBCurrent->OpCodeCurrent = PCBCurrent->OpCodeCurrent->next;
			
			// while loop to iterate if the pcb not at the end
		//printf("f, OS: All processes now set in %s state", PCBCurrent->state);
			while (PCBCurrent->OpCodeCurrent != PCBCurrent->OpCodeEnd)
			{
				
					
				if( PCBCurrent-> OpCodeCurrent->opLtr == 'M' )
					{
						int vInteger = PCBCurrent->OpCodeCurrent->opValue;
					
					//int nDigits = floor(log10(abs(vInteger))) + 1;
						// inititalizze
					int div = 10000;

					int off = vInteger % div;
					int base = vInteger / div;
					int offsetBase = base + off;
					int mmuSpace = (config->memAvailable);
					
					//int base1 = base;
					accessTimer(LAP_TIMER, timeStr);
					//string = PCBCurrent->OpCodeCurrent->opName;
						sprintf(buffer, "%s, Process %d, MMU attempt to %s %d/%d\n ", timeStr, PCBCurrent->Pid,
							PCBCurrent->OpCodeCurrent->opName, base, off);
					printf("%s", buffer);
					//base1 = offset;
					//PCBCurrent->OpCodeCurrent->opLtr = PCBCurrent->OpCodeCurrent->next;
					if (offsetBase < mmuSpace )
						{
							
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

					//, 
					//PCBCurrent->OpCodeCurrent->opName, PCBCurrent->OpCodeCurrent->opLtr)

					else if (PCBCurrent->OpCodeCurrent->opLtr == 'P')
					{
						accessTimer(LAP_TIMER, timeStr);
					sprintf(buffer, "%s, Process %d, %s %c started \n ", timeStr, PCBCurrent->Pid, 
					PCBCurrent->OpCodeCurrent->opName, PCBCurrent->OpCodeCurrent->opLtr);

					
					printf("%s", buffer);
						
						runTime = config->procCycleRate * PCBCurrent->OpCodeCurrent->opValue;
						runTimer(runTime);

						accessTimer(LAP_TIMER, timeStr);
					sprintf(buffer, "%s, Process %d, %s, %c ended \n ", timeStr, PCBCurrent->Pid, 
						PCBCurrent->OpCodeCurrent->opName, PCBCurrent->OpCodeCurrent->opLtr);

					
					printf("%s", buffer);

						
					}


					//if the coomand lettr is I or O
					else if (PCBCurrent->OpCodeCurrent->opLtr == 'I' || PCBCurrent->OpCodeCurrent->opLtr == 'O')
					{
						//calculate runtime
						accessTimer(LAP_TIMER, timeStr);
					sprintf(buffer, "%s, Process %d, %s %c started \n ", timeStr, PCBCurrent->Pid, 
					PCBCurrent->OpCodeCurrent->opName, PCBCurrent->OpCodeCurrent->opLtr);

					
					    printf("%s", buffer);
						runTime = (config->ioCycleRate ) * (PCBCurrent->OpCodeCurrent->opValue);
						//access the adress
						int* intParam = &runTime;
						void* dartParam = (void*) intParam;
						// call pthread_create
						pthread_create(&tid, NULL, runTimerT, dartParam);
						//call thread_join
						pthread_join(tid, NULL);

						//printf("%s, OS: Process %d, %s \n ", timeStr, PCBCurrent->Pid, PCBCurrent->OpCodeCurrent->opName);
						accessTimer(LAP_TIMER, timeStr);
					sprintf(buffer, "%s, Process %d, %s, %c ended \n ", timeStr, PCBCurrent->Pid, 
						PCBCurrent->OpCodeCurrent->opName, PCBCurrent->OpCodeCurrent->opLtr);

					
					printf("%s", buffer);

					
					//printf("%s", buffer);

					}

				// calculate PCBCurrent time remaining 
				PCBCurrent->timeRemaining -= runTime;
				
				//printf("%d\n", runTime );
				//printf("%d\n", timeRemaining );
				PCBCurrent->OpCodeCurrent = PCBCurrent->OpCodeCurrent->next;
				//printf("THEEEEEEEEEEEEEEEEE pid count isssssssss once again %d", pidcount);

				//PCBCurrent->timeRemaining -= runTime;
			
			}
				//pexit state;
				
				PCBCurrent->state = EXIT;

				printf("\n");
				accessTimer(LAP_TIMER, timeStr);
	 			sprintf(buffer,"%s, OS: Process %d ended and set in EXIT (%d) state \n ", timeStr, PCBCurrent->Pid, PCBCurrent->state);
				
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
	//int Mmultiplier = config->memAvailable;
	//int cycleTime = Pmultiplier + IOMultiplier;
	//memAvailable 

	// while loop iterate if command letter no S
	while (MDCurrent->opLtr != 'S')
	{
		// if condition
		if (MDCurrent->opLtr == 'A' && (compareString(MDCurrent->opName,"start") == STR_EQ))
		{
			
			// CReate a node
			newPCB = nodeMaker(MDCurrent, PidCounter, Pmultiplier, IOMultiplier) ;
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
	while ( (compareString(MDCurrent->opName,"end") != STR_EQ) || MDCurrent->opLtr != 'A'  )
	{
		//conditional if
		if (MDCurrent->opLtr == 'P' )
		{
			indvPCB->timeRemaining += MDCurrent->opValue * Pmultiplier;
		}

		//conditional if 
		
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

///////////////////////////work bottom

PCB* GetProcess(PCB* PCBHead, ConfigDataType* config, OpCodeType* metaData)
{
	PCB* PCBptr = PCBHead;
	PCB* meanTimePtr;
	int time;


			while (PCBptr != NULL && PCBptr->state != READY)
			{
				PCBptr = PCBptr->next;
			//meanTimePtr = PCBptr;


			}

			printf("testtttttttttttttttttt \n" );
			printf("The pid number issssssssss%d\n ", PCBptr->Pid );
			meanTimePtr = PCBptr;
			printf("uuuuuuuuuuuuuuuuuuuuuuuuuuuu \n" );

			if(meanTimePtr == NULL)
			{
				return NULL;
			}

			time = meanTimePtr->timeRemaining;
			PCBptr = PCBHead;

			while (PCBptr != NULL)
			{
				if(config->cpuSchedCode  == CPU_SCHED_FCFS_N_CODE)
				{
					if(PCBptr->state == READY)
					{
					return PCBptr;
					}
				}

				else if (config->cpuSchedCode  == CPU_SCHED_SJF_N_CODE)
				{
					if(PCBptr->state == READY && PCBptr->timeRemaining < time)
					{

				
					time = PCBptr->timeRemaining;
					meanTimePtr = PCBptr;

					printf("%d\n the mean time remaiming is", time );
					return meanTimePtr;
					}

				}
				//meanTimePtr = meanTimePtr->next;
			PCBptr = PCBptr->next;
			}
		
	
	return meanTimePtr;
	
}


#endif




