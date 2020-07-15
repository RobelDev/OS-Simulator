//precompiler directive
#ifndef SIMULATOR_H
#define SIMULATOR_H

//header files
#include <stdio.h>
#include "StringUtils.h"
#include "MetaDataAccess.h"
#include "configAccess.h"
#include <pthread.h>

typedef enum state{
		NEW,
		READY,
		WAITING,
		RUNNING,
		EXIT}state;


typedef struct PCB 
{


int Pid;
int state;
//int runTime;
struct PCB *next;
//struct PCB *PCBCurrent;
int timeRemaining;
struct OpCodeType *OpCodeCurrent;
struct OpCodeType *OpCodeHead;
struct OpCodeType *OpCodeEnd;
}PCB;

PCB* runSim(ConfigDataType* config, OpCodeType* metaData);
PCB* LinkedListMaker(ConfigDataType* config, OpCodeType* metaData);
PCB* nodeMaker(OpCodeType* MDCurrent, int Pid, 
					int Pmultiplier, int IOMultiplier);

PCB* GetProcess(PCB* PCBHead);


//typedef enum state{}


#endif