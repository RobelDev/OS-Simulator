//precompiler directive
#ifndef SIMULATOR_563951_H
#define SIMULATOR_563951_H

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

PCB* runSimulator(ConfigDataType* config, OpCodeType* metaData);
PCB* LinkedListMaker(ConfigDataType* config, OpCodeType* metaData);
PCB* nodeMaker(OpCodeType* MDCurrent, int Pid, 
					int Pmultiplier, int IOMultiplier);

PCB* GetProcess(PCB* PCBHead, ConfigDataType* config, OpCodeType* metaData);

PCB* MemoryManagementUnit(ConfigDataType* config, OpCodeType* metaData);


//typedef enum state{}


#endif