#include "SPBPriorityQueue.h"
#include "SPList.h"
#include <stdlib.h>

typedef struct sp_bp_queue_t{
	SPList elementList;
	int maxSize;
};

SPBPQueue spBPQueueCreate(int maxSize){
	// Function variables
	SPBPQueue BPQueue;
	SPList elemList;
	if (maxSize < 0)
		return NULL; // Invalid parameters
	BPQueue = (SPBPQueue) malloc(sizeof(SPBPQueue));
	if (BPQueue == NULL){ //Allocation Fails
		return NULL;
	}
	elemList = spListCreate();
	if (elemList == NULL){ //Allocation Fails
		free(BPQueue);
		return NULL;
	}
	BPQueue->maxSize = maxSize;
	BPQueue->elementList = elemList;
	return BPQueue;
}

SPBPQueue spBPQueueCopy(SPBPQueue source){
	// Function variables
	SPBPQueue newBPQueue;
	if (source == NULL)
		return NULL; // Invalid source queue
	newBPQueue = spBPQueueCreate(source->maxSize);
	if (newBPQueue != NULL){ // Creation Succeeded
		spListDestroy(newBPQueue->elementList); // free the empty list
		newBPQueue->elementList = spListCopy(source->elementList); // copy source's list
	}
	return newBPQueue;
}

void spBPQueueDestroy(SPBPQueue source){
	if (source != NULL){
		spListDestroy(source->elementList);
		free(source);
	}
}

void spBPQueueClear(SPBPQueue source){
	if (source != NULL){
		spListClear(source->elementList);
	}
}

int spBPQueueSize(SPBPQueue source){
	if (source == NULL){
		return 0; //TODO check return value in the case of source = null
	}
	return spListGetSize(source->elementList);
}

int spBPQueueGetMaxSize(SPBPQueue source){
	if (source == NULL){
		return 0; //TODO check return value in the case of source = null
	}
	return source->maxSize;
}

SP_BPQUEUE_MSG spBPQueueEnqueue(SPBPQueue source, SPListElement element){
	// Function variables
	SPListElement iter;
	int i; // Generic loop variable
	if (source == NULL || element == NULL){
		return SP_BPQUEUE_INVALID_ARGUMENT;
	}
	iter = spListGetFirst(source->elementList);
	if (iter == NULL){ // The list is empty
		spListInsertFirst(source->elementList,element);
		return SP_BPQUEUE_SUCCESS;
	}
	while (iter != NULL && spListElementCompare(iter,element) < 0){ // Find insertion point
		iter = spListGetNext(source->elementList);
	}
	// Insert the element
	if (iter == NULL){ // insert to the end of the queue
		spListInsertLast(source->elementList,element);
	}
	else {
		spListInsertBeforeCurrent(source->elementList,element);
	}
	if (spBPQueueSize(source) > spBPQueueGetMaxSize(source)){ // queue overflow
		spListGetFirst(source->elementList);
		for(i=0;i<source->maxSize;i++){ // Find the last element
			spListGetNext(source->elementList);
		}
		spListRemoveCurrent(source->elementList); // Remove the last element
	}
	if (spBPQueueSize(source) == spBPQueueGetMaxSize(source)){
		return SP_BPQUEUE_FULL;
	}
	return SP_BPQUEUE_SUCCESS;

}

SP_BPQUEUE_MSG spBPQueueDequeue(SPBPQueue source){
	if (source == NULL){
		return SP_BPQUEUE_INVALID_ARGUMENT;
	}
	spListGetFirst(source->elementList);
	spListRemoveCurrent(source->elementList);
	return SP_BPQUEUE_SUCCESS;
}

SPListElement spBPQueuePeek(SPBPQueue source){
	if (source == NULL){
		return NULL;
	}
	return spListElementCopy(spListGetFirst(source->elementList));
}

SPListElement spBPQueuePeekLast(SPBPQueue source){
	int i; // Generic loop variable
	if (source == NULL || spBPQueueIsEmpty(source)){
		return NULL;
	}
	spListGetFirst(source->elementList);
	for(i=0;i<spBPQueueSize(source)-1;i++){ // Find the last element
		spListGetNext(source->elementList);
	}
	return spListElementCopy(spListGetCurrent(source->elementList));
}

double spBPQueueMinValue(SPBPQueue source){

	if (source == NULL || spBPQueueIsEmpty(source)){
		return 0.0;
	}
	return spListElementGetValue(spBPQueuePeek(source));
}


double spBPQueueMaxValue(SPBPQueue source){
	if (source == NULL || spBPQueueIsEmpty(source)){
		return 0.0;
	}
	return spListElementGetValue(spBPQueuePeekLast(source));
}

bool spBPQueueIsEmpty(SPBPQueue source){
	if (source == NULL){
		return false; //TODO check what to write here
	}
	if (spBPQueueSize(source) == 0){
		return true;
	}
	return false;
}

bool spBPQueueIsFull(SPBPQueue source){
	if (source == NULL){
		return false; //TODO check what to write here
	}
	if (spBPQueueSize(source) == source->maxSize){
		return true;
	}
	return false;
}
